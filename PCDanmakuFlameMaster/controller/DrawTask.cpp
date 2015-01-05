/**
 * @file    DrawTask.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-01
 */

#include <mutex>
#include "../SkiaAssembly.hpp"
#include <skia/core/SkCanvas.h>
#include "../model/GlobalFlagValues.hpp"
#include "../parser/DanmakuFactory.hpp"
#include "DrawHelper.hpp"
#include "DrawTask.hpp"

using PCDanmakuFlameMaster::model::GlobalFlagValues;
using PCDanmakuFlameMaster::parser::DanmakuFactory;

namespace PCDanmakuFlameMaster {
namespace controller {

    DrawTask::DrawTask(DanmakuTimer& timer, AbsDisplayer<SkCanvas>& disp, TaskListener& taskListener) : 
        mTimer(timer), mDisp(disp), mTaskListener(taskListener) {
        // do nothing
    }

    void DrawTask::initTimer(DanmakuTimer& timer) {
        mTimer = timer;
    }

    void DrawTask::addDanmaku(BaseDanmaku& item) {
        if (danmakuList.isEmpty())
            return;
        bool added = false;
        danmakuList.mutex.lock(); {
            item.setTimer(mTimer);
            if (item.isLive) {
                item.time = mTimer.currMillisecond;
            }
            item.index = danmakuList.size();
            if (mLastBeginMills <= item.time && item.time <= mLastEndMills) {
                danmakus.mutex.lock(); {
                    added = danmakus.addItem(item);
                } danmakus.mutex.unlock();
            } else if (item.isLive) {
                mLastBeginMills = mLastEndMills = 0;
            }
            added = danmakuList.addItem(item);
        } danmakuList.mutex.unlock();

        if (added) {
            mTaskListener.onDanmakuAdd(item);
        }
    }

    void DrawTask::removeAllDanmakus() {
        if (danmakuList.isEmpty())
            return;
        danmakuList.mutex.lock(); {
            danmakuList.clear();
        } danmakuList.mutex.unlock();
    }

    void DrawTask::removeAllLiveDanmakus() {
        if (danmakus.isEmpty())
            return;
        danmakus.mutex.lock(); {
            auto iter = danmakus.iterator();
            while (iter.hasNext()) {
                if (iter.next().isLive) {
                    iter.remove();
                }
            }
        } danmakus.mutex.unlock();
    }

    void DrawTask::removeUnusedDanmakusIn(int msec) {
        if (danmakuList.isEmpty())
            return;

        danmakuList.mutex.lock(); {
            time_t startTime = HighResolutionClock::getCurrentMillis();
            auto iter = danmakuList.iterator();
            while (iter.hasNext()) {
                BaseDanmaku& danmaku = iter.next();
                bool isTimeOut = danmaku.isTimeOut();
                if (isTimeOut) {
                    iter.remove();
                }
                if (!isTimeOut || HighResolutionClock::getCurrentMillis() - startTime > msec) {
                    break;
                }
            }
        } danmakuList.mutex.unlock();
    }

    IRenderer::RenderingState DrawTask::draw(AbsDisplayer<SkCanvas>& displayer) {
        return drawDanmakus(displayer, mTimer);
    }

    void DrawTask::reset() {
        danmakus.clear();
        mRenderer.clear();
    }

    void DrawTask::seek(time_t mills) {
        reset();
        requestClear();
        GlobalFlagValues::updateVisibleFlag();
        mStartRenderTime = (mills < 1000) ? 0 : mills;
    }

    void DrawTask::start() {
        // do nothing
    }

    void DrawTask::quit() {
        mRenderer.release();
    }

    void DrawTask::prepare() {
        loadDanmakus(*mParser);
        mTaskListener.ready();
        mReadyState = true;
    }

    void DrawTask::loadDanmakus(BaseDanmakuParser& parser) {
        danmakuList = parser.setDisplayer(mDisp).setTimer(mTimer).getDanmakus();
        GlobalFlagValues::resetAll();
    }

    void DrawTask::setParser(BaseDanmakuParser& parser) {
        mParser = &parser;
        mReadyState = false;
    }

    IRenderer::RenderingState DrawTask::drawDanmakus(AbsDisplayer<SkCanvas>& disp, DanmakuTimer& timer) {
        SkCanvas& canvas = disp.getExtraData();
        DrawHelper::clearCanvas(canvas);
        
        time_t beginMills = timer.currMillisecond - DanmakuFactory::MAX_DANMAKU_DURATION - 100;
        time_t endMills = timer.currMillisecond + DanmakuFactory::MAX_DANMAKU_DURATION;
        
        if (mLastBeginMills > beginMills || timer.currMillisecond > mLastEndMills) {
            Danmakus& subDanmakus = danmakuList.sub(beginMills, endMills);
            if (!subDanmakus.isEmpty()) {
                danmakus = subDanmakus;
            } else {
                danmakus.clear();
                removeUnusedDanmakusIn(15);
            }
            mLastBeginMills = beginMills;
            mLastEndMills = endMills;
        } else {
            beginMills = mLastBeginMills;
            endMills = mLastEndMills;
        }

        if (!danmakus.isEmpty()) {
            IRenderer::RenderingState renderingState = mRenderer.draw(mDisp, danmakus, mStartRenderTime);
            if (renderingState.nothingRendered) {
                if (renderingState.beginTime == renderingState.UNKNOWN_TIME) {
                    renderingState.beginTime = beginMills;
                }
                if (renderingState.endTime == renderingState.UNKNOWN_TIME) {
                    renderingState.endTime = endMills;
                }
            }
            return renderingState;
        } else {
            mRenderingState.nothingRendered = true;
            mRenderingState.beginTime = beginMills;
            mRenderingState.endTime = endMills;
            return mRenderingState;
        }
    }

    void DrawTask::requestClear() {
        clearFlag = 5;
        mLastBeginMills = mLastEndMills = 0;
    }


}
}
