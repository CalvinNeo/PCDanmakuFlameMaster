/**
 * @file    IRenderer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-08
 */

#ifndef _PCDFM_RENDERER_IRENDERER_HPP
#define _PCDFM_RENDERER_IRENDERER_HPP

#include <cstdint>
#include "../model/BaseDanmaku.hpp"
#include "../model/Rect.hpp"

namespace PCDanmakuFlameMaster { namespace model { class IDisplayer; class Danmakus; } }

using PCDanmakuFlameMaster::model::DanmakuType;
using PCDanmakuFlameMaster::model::IDisplayer;
using PCDanmakuFlameMaster::model::Danmakus;
using PCDanmakuFlameMaster::model::Rect;

namespace PCDanmakuFlameMaster {
namespace renderer {

    class IRenderer {
    public:
        class Area {
        public:
            void setEdge(int maxWidth, int maxHeight);
            void reset();
            void resizeToMax();
            void set(Rect<float>& rect);
            void set(float left, float top, float right, float bottom);
        public:
            Rect<float> mRefreshRect;
        private:
            int mMaxWidth = 0;
            int mMaxHeight = 0;
        };

        class RenderingState {
        public:
            int addTotalCount(int count);
            int addCount(DanmakuType type, int count);
            void reset();
            void set(RenderingState& other);
        public:
            static const int UNKNOWN_TIME = -1;
        public:
            int r2lDanmakuCount = 0;
            int l2rDanmakuCount = 0;
            int ftDanmakuCount = 0;
            int fbDanmakuCount = 0;
            int specialDanmakuCount = 0;
            int totalDanmakuCount = 0;
            time_t consumingTime = 0;
            time_t beginTime = 0;
            time_t endTime = 0;
            bool nothingRendered = false;
            time_t sysTime = 0;
            bool inWaitingState = false;
        };
    public:
        virtual RenderingState draw(IDisplayer& disp, Danmakus& danmakus, time_t startRenderTime);
        virtual void clear();
        virtual void release();
    };

}
}

#endif // _PCDFM_RENDERER_IRENDERER_HPP
