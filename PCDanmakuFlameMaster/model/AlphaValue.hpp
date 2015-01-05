/**
 * @file    AlphaValue.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-27
 */

#ifndef _PCDFM_MODEL_ALPHAVALUE_HPP
#define _PCDFM_MODEL_ALPHAVALUE_HPP

#include <cstdint>

#ifdef MAX
    #undef MAX
#endif

#ifdef TRANSPARENT
    #undef TRANSPARENT
#endif

namespace PCDanmakuFlameMaster {
namespace model {

    class AlphaValue {
    public:
        static const uint8_t MAX = 255;
        static const uint8_t TRANSPARENT = 0;
    };

}
}

#endif // _PCDFM_MODEL_ALPHAVALUE_HPP
