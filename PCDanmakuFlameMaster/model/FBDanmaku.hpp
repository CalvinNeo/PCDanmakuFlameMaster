/**
 * @file    FBDanmaku.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#ifndef _PCDFM_MODEL_FBDANMAKU_HPP
#define _PCDFM_MODEL_FBDANMAKU_HPP

#include "BaseDanmaku.hpp"
#include "FTDanmaku.hpp"
#include "Duration.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    class FBDanmaku : public FTDanmaku {
    public:
        FBDanmaku(Duration& duration);
        virtual DanmakuType getType() const override;
    };

}
}

#endif // _PCDFM_MODEL_FBDANMAKU_HPP
