/**
 * @file    FTDanmakuRetainer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-03
 */

#ifndef _PCDFM_RENDERER_FTDANMAKUS_RETAINER_HPP
#define _PCDFM_RENDERER_FTDANMAKUS_RETAINER_HPP

#include "../model/BaseDanmaku.hpp"
#include "../model/IDisplayer.hpp"
#include "RLDanmakusRetainer.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::IDisplayer;

namespace PCDanmakuFlameMaster {
namespace renderer {

    class FTDanmakusRetainer : public RLDanmakusRetainer {
    protected:
        float checkVerticalEdge(bool overwriteInsert, const BaseDanmaku& drawItem, IDisplayer& disp, float topPos, const BaseDanmaku& firstItem, const BaseDanmaku& lastItem) override;
    };

}
}

#endif // _PCDFM_RENDERER_FTDANMAKUS_RETAINER_HPP
