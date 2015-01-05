/**
 * @file    DrawTask.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-01
 */

#ifndef _PCDFM_CONTROLLER_DRAWTAST_HPP
#define _PCDFM_CONTROLLER_DRAWTAST_HPP

#include <cstdint>
#include <functional>
#include "../model/BaseDanmaku.hpp"
#include "../model/DanmakuTimer.hpp"
#include "../model/Danmakus.hpp"
#include "../model/AbsDisplayer.hpp"
#include "../renderer/IRenderer.hpp"
#include "../parser/BaseDanmakuParser.hpp"
#include "../utilities/HighResolutionClock.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::DanmakuTimer;
using PCDanmakuFlameMaster::model::Danmakus;
using PCDanmakuFlameMaster::model::AbsDisplayer;
using PCDanmakuFlameMaster::renderer::IRenderer;
using PCDanmakuFlameMaster::parser::BaseDanmakuParser;
using PCDanmakuFlameMaster::util::HighResolutionClock;

class SkCanvas;

namespace PCDanmakuFlameMaster {
namespace controller {

    class DrawTask {
    public:
        class TaskListener {
        public:
            TaskListener() = default;
            TaskListener(std::function<void()> readyFunction, std::function<void(BaseDanmaku&)> onDanmakuAddFunction) : 
                ready(readyFunction), onDanmakuAdd(onDanmakuAddFunction) { }
        public:
            std::function<void()> ready = nullptr;
            std::function<void(BaseDanmaku&)> onDanmakuAdd = nullptr;
        };
    public:
        DrawTask(DanmakuTimer& timer, AbsDisplayer<SkCanvas>& disp, TaskListener& taskListener);
        void addDanmaku(BaseDanmaku& item);
        void removeAllDanmakus();
        void removeAllLiveDanmakus();
        IRenderer::RenderingState draw(AbsDisplayer<SkCanvas>& displayer);
        void reset();
        void seek(time_t mills);
        void start();
        void quit();
        void prepare();
        void setParser(BaseDanmakuParser& parser);
        void requestClear();
    protected:
        void initTimer(DanmakuTimer& timer);
        void removeUnusedDanmakusIn(int msec);
        void loadDanmakus(BaseDanmakuParser& parser);
        IRenderer::RenderingState drawDanmakus(AbsDisplayer<SkCanvas>& disp, DanmakuTimer& timer);
    private:
        TaskListener mTaskListener;
        IRenderer mRenderer;
        DanmakuTimer mTimer;
        HighResolutionClock mCounter;
        Danmakus danmakus;
        time_t mStartRenderTime = 0;
        IRenderer::RenderingState mRenderingState;
        time_t mLastBeginMills = 0;
        time_t mLastEndMills = 0;
    protected:
        AbsDisplayer<SkCanvas>& mDisp;
        Danmakus danmakuList;
        BaseDanmakuParser* mParser = nullptr;
        int clearFlag = 0;
        bool mReadyState = false;
    };

}
}

#endif
