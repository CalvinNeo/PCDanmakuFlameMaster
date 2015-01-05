/**
 * @file    L2RDanmaku.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#ifndef _PCDFM_MODEL_L2RDANMAKU_HPP
#define _PCDFM_MODEL_L2RDANMAKU_HPP

#include <cstdint>
#include "BaseDanmaku.hpp"
#include "R2LDanmaku.hpp"
#include "Duration.hpp"
#include "IDisplayer.hpp"
#include "Rect.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    class L2RDanmaku : public R2LDanmaku {
    public:
        L2RDanmaku(Duration& duration);

        virtual void layout(IDisplayer& displayer, float x, float y) override;
        virtual Rect<float> getRectAtTime(IDisplayer& displayer, time_t time) const override;

        virtual float getLeft() const override;
        virtual float getTop() const override;
        virtual float getRight() const override;
        virtual float getBottom() const override;
        virtual DanmakuType getType() const override;
    protected:
        virtual float getAccurateLeft(IDisplayer& displayer, time_t currTime) const override;
    };

}
}

#endif // _PCDFM_MODEL_L2RDANMAKU_HPP
