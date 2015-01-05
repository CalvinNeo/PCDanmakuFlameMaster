/**
 * @file    FTDanmakuRetainer.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-03
 */

#include "../model/BaseDanmaku.hpp"
#include "../model/IDisplayer.hpp"
#include "FTDanmakusRetainer.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::IDisplayer;

namespace PCDanmakuFlameMaster {
namespace renderer {

    float FTDanmakusRetainer::checkVerticalEdge(bool overwriteInsert, const BaseDanmaku& drawItem, IDisplayer& disp, float topPos, const BaseDanmaku& firstItem, const BaseDanmaku& lastItem) {
        if (topPos + drawItem.paintHeight > disp.getHeight()) {
            topPos = 0;
            clear();
        }
        return topPos;
    }

}
}
