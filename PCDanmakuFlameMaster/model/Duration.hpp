/**
 * @file    Duration.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-27
 */

#ifndef _PCDFM_MODEL_DURATION_HPP
#define _PCDFM_MODEL_DURATION_HPP

#include <cstdint>

namespace PCDanmakuFlameMaster {
namespace model {

    class Duration {
    public:
        inline Duration() { }

        inline Duration(time_t initialDuration) :
            mInitialDuration(initialDuration), value(initialDuration) { }

        inline void setValue(time_t initialDuration) {
            mInitialDuration = initialDuration;
            value = static_cast<time_t>(mInitialDuration * factor);
        }

        inline void setFactor(float f) {
            if (factor != f) {
                factor = f;
                value = static_cast<time_t>(mInitialDuration * f);
            }
        }

        inline void reset() {
            value = 0;
            mInitialDuration = 0;
            factor = 1.0f;
        }
    public:
        time_t value = 0;
    private:
        time_t mInitialDuration = 0;
        float factor = 1.0F;
    };

}
}

#endif // _PCDFM_MODEL_DURATION_HPP
