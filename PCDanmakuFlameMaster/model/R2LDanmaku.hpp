/**
 * @file    R2LDanmaku.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#ifndef _PCDFM_MODEL_R2LDANMAKU_HPP
#define _PCDFM_MODEL_R2LDANMAKU_HPP

#include <cstdint>
#include "BaseDanmaku.hpp"
#include "Duration.hpp"
#include "IDisplayer.hpp"
#include "Rect.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    class R2LDanmaku : public BaseDanmaku {
    public:
        R2LDanmaku(Duration& duration);

        virtual void layout(IDisplayer& displayer, float x, float y) override;
        virtual Rect<float> getRectAtTime(IDisplayer& displayer, time_t time) const override;
        virtual void measure(IDisplayer& displayer) override;
        
        virtual float getLeft() const override;
        virtual float getTop() const override;
        virtual float getRight() const override;
        virtual float getBottom() const override;
        virtual DanmakuType getType() const override;
    protected:
        virtual float getAccurateLeft(IDisplayer& displayer, time_t currTime) const;
    protected:
        static const int MAX_RENDERING_TIME = 100;
        static const int CORDON_RENDERING_TIME = 40;
        float x = 0;
        float y = -1;
        int mDistance = 0;
        mutable Rect<float> mRect;
        float mStepX = 0.0F;
        time_t mLastTime = 0;
    };

}
}

#endif // _PCDFM_MODEL_R2LDANMAKU_HPP
