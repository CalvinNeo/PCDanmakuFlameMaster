/**
 * @file    FBDanmaku.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#include "Duration.hpp"
#include "FBDanmaku.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    FBDanmaku::FBDanmaku(Duration& duration) : FTDanmaku(duration) {
        return;
    }

    DanmakuType FBDanmaku::getType() const {
        return DanmakuType_Fix_Bottom;
    }

}
}
