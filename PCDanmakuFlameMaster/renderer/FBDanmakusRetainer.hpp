/**
 * @file    FBDanmakuRetainer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-04
 */

#ifndef _PCDFM_RENDERER_FBDANMAKU_RETAINER_HPP
#define _PCDFM_RENDERER_FBDANMAKU_RETAINER_HPP

#include "../model/Danmakus.hpp"
#include "FTDanmakusRetainer.hpp"

using PCDanmakuFlameMaster::model::Danmakus;

namespace PCDanmakuFlameMaster {
namespace renderer {

    class FBDanmakusRetainer : public FTDanmakusRetainer {
    public:
        FBDanmakusRetainer() : mVisibleDanmakus(Danmakus::ST_BY_YPOS_DESC) { }
        void fix(BaseDanmaku& drawItem, IDisplayer& disp) override;
        void clear() override;
    protected:
        float checkVerticalEdge(bool overwriteInsert, const BaseDanmaku& drawItem, IDisplayer& disp, float topPos, const BaseDanmaku& firstItem, const BaseDanmaku& lastItem) override;
    protected:
        Danmakus mVisibleDanmakus;
    };

}
}

#endif // _PCDFM_RENDERER_FBDANMAKU_RETAINER_HPP
