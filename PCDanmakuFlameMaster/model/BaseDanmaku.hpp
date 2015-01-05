/**
 * @file    BaseDanmaku.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-13
 */

#ifndef _PCDFM_BASE_DANMAKU_HPP
#define _PCDFM_BASE_DANMAKU_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "GlobalFlagValues.hpp"
#include "DanmakuTimer.hpp"
#include "AlphaValue.hpp"
#include "Duration.hpp"
#include "IDisplayer.hpp"
#include "Rect.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    enum DanmakuType {
        DanmakuType_Scroll_RL = 1,
        DanmakuType_Scroll_LR = 6,
        DanmakuType_Fix_Top = 5,
        DanmakuType_Fix_Bottom = 4,
        DanmakuType_Special = 7,
        DanmakuType_Code = 8,
    };

    class BaseDanmaku {
    public:
        static const int INVISIBLE = 0;
        static const int VISIBLE = 1;
        static const char* const DANMAKU_BR_CHAR;
    public:
        //inline BaseDanmaku() = default;

        inline time_t getDuration() const {
            return duration.value;
        }

        inline void setDuration(Duration& duration) {
            this->duration = duration;
        }

        inline void draw(IDisplayer& displayer) const {
            displayer.draw(*this);
        }

        inline bool isMeasured() const {
            return (paintWidth >= 0 && paintHeight >= 0) &&
                   (measureResetFlag == GlobalFlagValues::MEASURE_RESET_FLAG);
        }

        virtual void measure(IDisplayer& displayer) {
            displayer.measure(*this);
            this->measureResetFlag = GlobalFlagValues::MEASURE_RESET_FLAG;
        }

        inline bool hasDrawingCache() const {
            return false; // TODO
        }

        virtual bool isShown() const {
            return (this->visibility == VISIBLE) &&
                   (visibleResetFlag == GlobalFlagValues::VISIBLE_RESET_FLAG);
        }

        inline bool isTimeOut() const {
            return isTimeOut(mTimer.currMillisecond);
        }

        inline bool isTimeOut(time_t ctime) const {
            return (ctime - time) >= duration.value;
        }

        inline bool isOutside() const {
            return isOutside(mTimer.currMillisecond);
        }

        inline bool isOutside(time_t ctime) const {
            time_t dTime = ctime - time;
            return (dTime <= 0 || dTime >= duration.value);
        }

        inline bool isLate() const {
            return (mTimer.currMillisecond < time);
        }

        inline void setVisibility(bool b) {
            if (b) {
                this->visibleResetFlag = GlobalFlagValues::VISIBLE_RESET_FLAG;
                this->visibility = VISIBLE;
            } else {
                this->visibility = INVISIBLE;
            }
        }

        inline DanmakuTimer& getTimer() {
            return mTimer;
        }

        inline void setTimer(DanmakuTimer& timer) {
            mTimer = timer;
        }

        inline int getAlpha() const {
            return alpha;
        }

        virtual void layout(IDisplayer& displayer, float x, float y);
        virtual Rect<float> getRectAtTime(IDisplayer& displayer, time_t currTime) const;
        virtual float getLeft() const;
        virtual float getTop() const;
        virtual float getRight() const;
        virtual float getBottom() const;
        virtual DanmakuType getType() const;
    public:
        time_t time = 0;
        std::string text;
        std::vector<std::string> lines;
        int textColor = 0;
        int textShadowColor = 0;
        int underlineColor = 0;
        int borderColor = 0;
        float rotationZ = 0.0F;
        float rotationY = 0.0F;
        float textSize = -1.0F;
        int padding = 0;
        uint8_t priority = 0;
        float paintWidth = -1;
        float paintHeight = -1;
        Duration duration;
        int index = 0;
        int visibility = 0;

        bool isLive = false;
        int userId = 0;
        std::string userHash;
        bool isGuest = false;
    private:
        int visibleResetFlag = 0;
        int measureResetFlag = 0;
    protected:
        DanmakuTimer mTimer;
        int alpha = AlphaValue::MAX;
    };

}
}

#endif // _PCDFM_BASE_DANMAKU_HPP
