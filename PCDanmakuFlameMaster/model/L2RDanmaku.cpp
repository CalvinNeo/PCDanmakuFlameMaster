/**
 * @file    L2RDanmaku.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#include <cstdint>
#include <stdexcept>
#include "IDisplayer.hpp"
#include "L2RDanmaku.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    L2RDanmaku::L2RDanmaku(Duration& duration) : R2LDanmaku(duration) {
        return;
    }

    void L2RDanmaku::layout(IDisplayer& displayer, float x, float y) {
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

    float L2RDanmaku::getAccurateLeft(IDisplayer& displayer, time_t currTime) const {
        time_t elapsedTime = currTime - time;

        if (elapsedTime >= duration.value) {
            return static_cast<float>(displayer.getWidth());
        }

        return mStepX * elapsedTime - paintWidth;
    }

    Rect<float> L2RDanmaku::getRectAtTime(IDisplayer& displayer, time_t time) const {
        if (!isMeasured())
            throw std::exception("not measured");

        float left = getAccurateLeft(displayer, time);

        mRect.left = left;
        mRect.top = y;
        mRect.right = left + paintWidth;
        mRect.bottom = y + paintHeight;

        return mRect;
    }

    float L2RDanmaku::getLeft() const {
        return x;
    }

    float L2RDanmaku::getTop() const {
        return y;
    }

    float L2RDanmaku::getRight() const {
        return x + paintWidth;
    }

    float L2RDanmaku::getBottom() const {
        return y + paintHeight;
    }

    DanmakuType L2RDanmaku::getType() const {
        return DanmakuType_Scroll_LR;
    }

}
}