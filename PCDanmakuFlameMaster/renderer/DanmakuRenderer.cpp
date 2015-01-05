/**
 * @file    DanmakuRenderer.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-08
 */

#include <cstdint>
#include "../model/BaseDanmaku.hpp"
#include "../model/Danmakus.hpp"
#include "DanmakusRetainer.hpp"
#include "../utilities/HighResolutionClock.hpp"
#include "DanmakuRenderer.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::DanmakuType;
using PCDanmakuFlameMaster::model::Danmakus;

using PCDanmakuFlameMaster::util::HighResolutionClock;

namespace PCDanmakuFlameMaster {
namespace renderer {

    void DanmakuRenderer::clear() {
        DanmakusRetainer::clear();
    }

    void DanmakuRenderer::release() {
        DanmakusRetainer::release();
    }

    DanmakuRenderer::RenderingState DanmakuRenderer::draw(IDisplayer& disp, Danmakus& danmakus, time_t startRenderTime) {
        mRenderingState.reset();
        auto iter = danmakus.iterator();
        int orderInScreen = 0;
        mStartTimer.update(HighResolutionClock::getCurrentMillis());
        int sizeInScreen = danmakus.size();

        BaseDanmaku* drawItem = nullptr;

        while (iter.hasNext()) {
            drawItem = &iter.next();

            if (drawItem->isLate()) {
                break;
            }

            if (drawItem->time < startRenderTime ||
                (drawItem->priority == 0 /* TODO: DanmakuFilters*/)) {
                continue;
            }

            if (drawItem->getType() == DanmakuType::DanmakuType_Scroll_RL) {
                orderInScreen++;
            }

            if (!drawItem->isMeasured()) {
                drawItem->measure(disp);
            }

            DanmakusRetainer::fix(*drawItem, disp);

            if (!drawItem->isOutside() && drawItem->isShown()) {
                drawItem->draw(disp);
                mRenderingState.addCount(drawItem->getType(), 1);
                mRenderingState.addTotalCount(1);
            }
        }

        mRenderingState.nothingRendered = (mRenderingState.totalDanmakuCount == 0);
        if (mRenderingState.nothingRendered) {
            mRenderingState.beginTime = RenderingState::UNKNOWN_TIME;
            mRenderingState.endTime = drawItem != nullptr ? drawItem->time : RenderingState::UNKNOWN_TIME;
        }
        mRenderingState.consumingTime = mStartTimer.update(HighResolutionClock::getCurrentMillis());
        return mRenderingState;
    }

}
}
