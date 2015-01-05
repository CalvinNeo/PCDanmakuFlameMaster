/**
 * @file    DanmakuRetainer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-03
 */

#ifndef _PCDFM_RENDERER_DANMAKUS_RETAINER_HPP
#define _PCDFM_RENDERER_DANMAKUS_RETAINER_HPP

#include <memory>
#include "../model/BaseDanmaku.hpp"
#include "../model/IDisplayer.hpp"
#include "IDanmakusRetainer.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::IDisplayer;

namespace PCDanmakuFlameMaster {
namespace renderer {

    class DanmakusRetainer {
    public:
        static void fix(BaseDanmaku& danmaku, IDisplayer& disp);
        static void clear();
        static void release();
    private:
        static std::shared_ptr<IDanmakusRetainer> rldrInstance;
        static std::shared_ptr<IDanmakusRetainer> lrdrInstance;
        static std::shared_ptr<IDanmakusRetainer> ftdrInstance;
        static std::shared_ptr<IDanmakusRetainer> fbdrInstance;
    };

}
}

#endif // _PCDFM_RENDERER_DANMAKUS_RETAINER_HPP
