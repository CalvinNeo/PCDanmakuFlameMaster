/**
 * @file    IDanmakuRetainer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-03
 */

#ifndef _PCDFM_RENDERER_IDANMAKUS_RETAINER_HPP
#define _PCDFM_RENDERER_IDANMAKUS_RETAINER_HPP

#include "../model/BaseDanmaku.hpp"
#include "../model/IDisplayer.hpp"
#include "../utilities/Interface.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::IDisplayer;

namespace PCDanmakuFlameMaster {
namespace renderer {

    __interface_class
    class IDanmakusRetainer {
    public:
        virtual void fix(BaseDanmaku& drawItem, IDisplayer& disp) = 0;
        virtual void clear() = 0;
    };

}
}

#endif // _PCDFM_RENDERER_IDANMAKUS_RETAINER_HPP
