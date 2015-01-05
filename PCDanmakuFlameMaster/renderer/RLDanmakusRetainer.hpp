/**
 * @file    RLDanmakuRetainer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-03
 */

#ifndef _PCDFM_RENDER_RLDANMAKU_RETAINER_HPP
#define _PCDFM_RENDER_RLDANMAKU_RETAINER_HPP

#include "../model/BaseDanmaku.hpp"
#include "../model/IDisplayer.hpp"
#include "../model/Danmakus.hpp"
#include "IDanmakusRetainer.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::IDisplayer;
using PCDanmakuFlameMaster::model::Danmakus;

namespace PCDanmakuFlameMaster {
namespace renderer {

    class RLDanmakusRetainer : public IDanmakusRetainer {
    public:
        RLDanmakusRetainer() : mVisibleDanmakus(Danmakus::ST_BY_YPOS) { }
        void fix(BaseDanmaku& drawItem, IDisplayer& disp) override;
        void clear() override;
    protected:
        virtual float checkVerticalEdge(bool overwriteInsert, const BaseDanmaku& drawItem, IDisplayer& disp, float topPos, const BaseDanmaku& firstItem, const BaseDanmaku& lastItem);
    protected:
        Danmakus mVisibleDanmakus;
        bool mCancelFixingFlag = false;
    };

}
}

#endif // _PCDFM_RENDER_RLDANMAKU_RETAINER_HPP
