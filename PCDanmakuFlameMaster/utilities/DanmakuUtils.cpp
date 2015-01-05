/**
 * @file    DanmakuUtils.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-01
 */

#include <cstdint>
#include <cmath>
#include <../model/BaseDanmaku.hpp>
#include <../model/IDisplayer.hpp>
#include <../model/Rect.hpp>
#include "DanmakuUtils.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::DanmakuType;
using PCDanmakuFlameMaster::model::IDisplayer;
using PCDanmakuFlameMaster::model::Rect;

namespace PCDanmakuFlameMaster {
namespace util {
namespace DanmakuUtils {

    bool willHitInDuration(IDisplayer& disp, const BaseDanmaku& d1, const BaseDanmaku& d2, time_t duration, time_t currTime) {
        DanmakuType type1 = d1.getType();
        DanmakuType type2 = d2.getType();

        if (type1 != type2)
            return false;

        if (d1.isOutside())
            return false;

        time_t dTime = d2.time - d1.time;
        if (dTime < 0)
            return true;
        
        if (abs(dTime) >= duration || d1.isTimeOut() || d2.isTimeOut())
            return false;

        if (type1 == DanmakuType::DanmakuType_Fix_Top || type1 == DanmakuType::DanmakuType_Fix_Bottom)
            return true;

        return checkHitAtTime(disp, d1, d2, currTime)
            || checkHitAtTime(disp, d1, d2, d1.time + d1.getDuration());
    }

    bool checkHitAtTime(IDisplayer& disp, const BaseDanmaku& d1, const BaseDanmaku& d2, time_t time) {
        const Rect<float> rect1 = d1.getRectAtTime(disp, time);
        const Rect<float> rect2 = d2.getRectAtTime(disp, time);

        return checkHit(d1.getType(), d2.getType(), rect1, rect2);
    }

    bool checkHit(const DanmakuType type1, const DanmakuType type2, const Rect<float>& rect1, const Rect<float>& rect2) {
        if (type1 != type2)
            return false;
        if (type1 == DanmakuType::DanmakuType_Scroll_RL) {
            return (rect2.left < rect1.right);
        }
        if (type1 == DanmakuType::DanmakuType_Scroll_LR) {
            return (rect2.right > rect1.left);
        }

        return false;
    }

    int getCacheSize(int width, int height) {
        return width * height * 4;
    }

    int compare(const BaseDanmaku& obj1, const BaseDanmaku& obj2) {
        if (&obj1 == &obj2)
            return 0;

        //if (&obj1 == nullptr)
        //    return -1;
        //
        //if (&obj2 == nullptr)
        //    return 1;

        time_t val = obj1.time - obj2.time;
        if (val > 0) {
            return 1;
        } else if (val < 0) {
            return -1;
        }

        int result = obj1.index - obj2.index;
        if (result > 0) {
            return 1;
        } else if (result < 0) {
            return -1;
        }

        result = static_cast<int>(obj1.getType()) - static_cast<int>(obj2.getType());
        if (result > 0) {
            return 1;
        } else if (result < 0) {
            return -1;
        }

        if (obj1.text.empty()) {
            return -1;
        }

        if (obj2.text.empty()) {
            return 1;
        }

        // TODO

        return 0;
    }

}
}
}
