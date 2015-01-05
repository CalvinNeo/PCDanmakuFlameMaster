/**
 * @file    DanmakuUtils.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-01
 */

#ifndef _PCDFM_UTILS_DANMAKU_UTILS_HPP
#define _PCDFM_UTILS_DANMAKU_UTILS_HPP

#include <cstdint>
#include <../model/BaseDanmaku.hpp>
#include <../model/IDisplayer.hpp>
#include <../model/Rect.hpp>

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::DanmakuType;
using PCDanmakuFlameMaster::model::IDisplayer;
using PCDanmakuFlameMaster::model::Rect;

namespace PCDanmakuFlameMaster {
namespace util {
namespace DanmakuUtils {

    bool willHitInDuration(IDisplayer& disp, const BaseDanmaku& d1, const BaseDanmaku& d2, time_t duration, time_t currTime);
    bool checkHitAtTime(IDisplayer& disp, const BaseDanmaku& d1, const BaseDanmaku& d2, time_t time);
    bool checkHit(const DanmakuType type1, const DanmakuType type2, const Rect<float>& rect1, const Rect<float>& rect2);

    int getCacheSize(int width, int height);
    int compare(const BaseDanmaku& obj1, const BaseDanmaku& obj2);

}
}
}

#endif // _PCDFM_UTILS_DANMAKU_UTILS_HPP
