/**
 * @file    FTDanmaku.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#include <cstdint>
#include "IDisplayer.hpp"
#include "Rect.hpp"
#include "FTDanmaku.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    FTDanmaku::FTDanmaku(Duration& duration) : BaseDanmaku() {
        this->duration = duration;
    }

    void FTDanmaku::layout(IDisplayer& displayer, float x, float y) {
        time_t deltaDuration = mTimer.currMillisecond - time;

        if (deltaDuration > 0 && deltaDuration < duration.value) {
            if (!this->isShown()) {
                this->x = getLeft(displayer);
                this->y = y;
                this->setVisibility(true);
            }
            return;
        }

        this->setVisibility(false);
        this->y = -1;
        this->x = static_cast<float>(displayer.getWidth());
    }

    float FTDanmaku::getLeft(IDisplayer& displayer) const {
        if (mLastDispWidth == displayer.getWidth() && mLastPaintWidth == paintWidth) {
            return mLastLeft;
        }

        float left = (displayer.getWidth() - paintWidth) / 2;
        mLastDispWidth = displayer.getWidth();
        mLastPaintWidth = paintWidth;
        mLastLeft = left;

        return left;
    }

    Rect<float> FTDanmaku::getRectAtTime(IDisplayer& displayer, time_t time) const {
        if (!isMeasured())
            throw std::exception("not measured");

        float left = this->getLeft(displayer);

        mRect.left = left;
        mRect.top = y;
        mRect.right = left + paintWidth;
        mRect.bottom = y + paintHeight;

        return mRect;
    }

    float FTDanmaku::getLeft() const {
        return x;
    }

    float FTDanmaku::getTop() const {
        return y;
    }

    float FTDanmaku::getRight() const {
        return x + paintWidth;
    }

    float FTDanmaku::getBottom() const {
        return y + paintWidth;
    }

    DanmakuType FTDanmaku::getType() const {
        return DanmakuType_Fix_Top;
    }

}
}
