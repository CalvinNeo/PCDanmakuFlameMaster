/**
 * @file    DanmakuRetainer.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-03
 */

#include <memory>
#include "../model/BaseDanmaku.hpp"
#include "../model/IDisplayer.hpp"
#include "RLDanmakusRetainer.hpp"
#include "FTDanmakusRetainer.hpp"
#include "FBDanmakusRetainer.hpp"
#include "DanmakusRetainer.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::DanmakuType;
using PCDanmakuFlameMaster::model::IDisplayer;

namespace PCDanmakuFlameMaster {
namespace renderer {
    
    void DanmakusRetainer::fix(BaseDanmaku& danmaku, IDisplayer& disp) {
        DanmakuType type = danmaku.getType();
        switch (type) {
        case DanmakuType::DanmakuType_Scroll_RL:
            if (rldrInstance == nullptr) {
                rldrInstance = std::make_shared<RLDanmakusRetainer>();
            }
            rldrInstance->fix(danmaku, disp);
            break;
        case DanmakuType::DanmakuType_Scroll_LR:
            if (lrdrInstance == nullptr) {
                lrdrInstance = std::make_shared<RLDanmakusRetainer>();
            }
            lrdrInstance->fix(danmaku, disp);
            break;
        case DanmakuType::DanmakuType_Fix_Top:
            if (ftdrInstance == nullptr) {
                ftdrInstance = std::make_shared<FTDanmakusRetainer>();
            }
            ftdrInstance->fix(danmaku, disp);
            break;
        case DanmakuType::DanmakuType_Fix_Bottom:
            if (fbdrInstance == nullptr) {
                fbdrInstance = std::make_shared<FBDanmakusRetainer>();
            }
            fbdrInstance->fix(danmaku, disp);
            break;
        case DanmakuType::DanmakuType_Special:
            danmaku.layout(disp, 0, 0);
            break;
        }
    }

    void DanmakusRetainer::clear() {
        if (rldrInstance)
            rldrInstance->clear();
        if (lrdrInstance)
            lrdrInstance->clear();
        if (ftdrInstance)
            ftdrInstance->clear();
        if (fbdrInstance)
            fbdrInstance->clear();
    }

    void DanmakusRetainer::release() {
        clear();
        rldrInstance.reset();
        lrdrInstance.reset();
        ftdrInstance.reset();
        fbdrInstance.reset();
    }
    
}
}