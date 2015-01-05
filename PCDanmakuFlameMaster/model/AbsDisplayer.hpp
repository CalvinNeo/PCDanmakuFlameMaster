/**
 * @file    AbsDisplayer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-28
 */

#ifndef _PCDFM_MODEL_ABSDISPLAYER_HPP
#define _PCDFM_MODEL_ABSDISPLAYER_HPP

#include <cstdint>
#include "IDisplayer.hpp"

namespace PCDanmakuFlameMaster {
namespace model {
    
    template <typename T>
    class AbsDisplayer : public IDisplayer {
    public:
        virtual T& getExtraData() = 0;
        virtual void setExtraData(T& data) = 0;
    };

}
}

#endif // _PCDFM_MODEL_ABSDISPLAYER_HPP
