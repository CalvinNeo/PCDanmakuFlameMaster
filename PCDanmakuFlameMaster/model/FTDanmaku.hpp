/**
 * @file    FTDanmaku.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#ifndef _PCDFM_MODEL_FTDANMAKU_HPP
#define _PCDFM_MODEL_FTDANMAKU_HPP

#include <cstdint>
#include "BaseDanmaku.hpp"
#include "Duration.hpp"
#include "IDisplayer.hpp"
#include "Rect.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    class FTDanmaku : public BaseDanmaku {
    public:
        FTDanmaku(Duration& duration);

        virtual void layout(IDisplayer& displayer, float x, float y) override;
        virtual Rect<float> getRectAtTime(IDisplayer& displayer, time_t time) const override;

        virtual float getLeft() const override;
        virtual float getTop() const override;
        virtual float getRight() const override;
        virtual float getBottom() const override;
        virtual DanmakuType getType() const override;
    protected:
        virtual float getLeft(IDisplayer& displayer) const;
    private:
        float x = 0;
        mutable Rect<float> mRect;
        mutable float mLastLeft = 0.0F;
        mutable float mLastPaintWidth = 0.0F;
        mutable int mLastDispWidth = 0;
    protected:
        float y = -1;        
    };

}
}

#endif // _PCDFM_MODEL_FTDANMAKU_HPP
