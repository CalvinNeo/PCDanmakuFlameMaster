/**
 * @file    DanmakuRenderer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-08
 */

#ifndef _PCDFM_RENDERER_DANMAKU_RENDERER_HPP
#define _PCDFM_RENDERER_DANMAKU_RENDERER_HPP

#include "../model/DanmakuTimer.hpp"
#include "IRenderer.hpp"

using PCDanmakuFlameMaster::model::DanmakuTimer;

namespace PCDanmakuFlameMaster {
namespace renderer {

    class DanmakuRenderer : public IRenderer {
    public:
        void clear() override;
        void release() override;
        RenderingState draw(IDisplayer& disp, Danmakus& danmakus, time_t startRenderTime) override;
    private:
        DanmakuTimer mStartTimer;
        RenderingState mRenderingState;
    };

}
}

#endif // _PCDFM_RENDERER_DANMAKU_RENDERER_HPP
