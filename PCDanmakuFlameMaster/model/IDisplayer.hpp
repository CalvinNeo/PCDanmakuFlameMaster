/**
 * @file    IDisplayer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#ifndef _PCDFM_MODEL_IDISPLAYER_HPP
#define _PCDFM_MODEL_IDISPLAYER_HPP

#include <cstdint>
#include "../utilities/Interface.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    class BaseDanmaku;

    __interface_class
    class IDisplayer {
    public:
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual float getDensity() const = 0;
        virtual int getDensityDpi() const = 0;
        virtual void draw(const BaseDanmaku& danmaku) = 0;
        virtual float getScaledDensity() const = 0;
        virtual int getSlopPixel() const = 0;
        virtual void measure(BaseDanmaku& danmaku) = 0;
        virtual time_t getAverageRenderingTime() const = 0;
        virtual time_t getLastFrameRenderingTime() const = 0;
        virtual float getStrokeWidth() const = 0;
        virtual void resetSlopPixel(float factor) = 0;
        virtual void setDensities(float density, int densityDpi, float scaledDensity) = 0;
        virtual void setSize(int width, int height) = 0;
        virtual void setAverageRenderingTime(time_t ms) = 0;
        virtual void setLastFrameRenderingTime(time_t ms) = 0;
    };

}
}

#endif // _PCDFM_MODEL_IDISPLAYER_HPP
