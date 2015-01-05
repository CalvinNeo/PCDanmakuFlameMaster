/**
 * @file    R2LDanmaku.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#include <cstdint>
#include <stdexcept>
#include "IDisplayer.hpp"
#include "R2LDanmaku.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    R2LDanmaku::R2LDanmaku(Duration& duration) {
        this->duration = duration;
    }

    void R2LDanmaku::layout(IDisplayer& displayer, float x, float y) {
        time_t currMS = mTimer.currMillisecond;
        time_t deltaDuration = currMS - time;

        if (deltaDuration > 0 && deltaDuration < duration.value) {
            this->x = getAccurateLeft(displayer, currMS);
            if (!this->isShown()) {
                this->y = y;
                this->setVisibility(true);
            }
            mLastTime = currMS;
            return;
        }

        mLastTime = currMS;
        this->setVisibility(false);        
    }

    float R2LDanmaku::getAccurateLeft(IDisplayer& displayer, time_t currTime) const {
        time_t elapsedTime = currTime - time;

        if (elapsedTime >= duration.value) {
            return -paintWidth;
        }

        return displayer.getWidth() - elapsedTime * mStepX;
    }

    Rect<float> R2LDanmaku::getRectAtTime(IDisplayer& displayer, time_t time) const {
        if (!isMeasured())
            throw std::exception("not measured");

        float left = getAccurateLeft(displayer, time);

        mRect.left = left;
        mRect.top = y;
        mRect.right = left + paintWidth;
        mRect.bottom = y + paintHeight;

        return mRect;
    }
    
    void R2LDanmaku::measure(IDisplayer& displayer) {
        this->BaseDanmaku::measure(displayer);
        mDistance = static_cast<int>(displayer.getWidth() + paintWidth);
        mStepX = static_cast<float>(mDistance / duration.value);
    }

    float R2LDanmaku::getLeft() const {
        return x;
    }

    float R2LDanmaku::getTop() const {
        return y;
    }

    float R2LDanmaku::getRight() const {
        return x + paintWidth;
    }

    float R2LDanmaku::getBottom() const {
        return y + paintHeight;
    }

    DanmakuType R2LDanmaku::getType() const {
        return DanmakuType_Scroll_RL;
    }

}
}
