/**
 * @file    IRenderer.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-08
 */

#include "../model/BaseDanmaku.hpp"
#include "../model/IDisplayer.hpp"
#include "../model/Danmakus.hpp"
#include "../model/Rect.hpp"
#include "IRenderer.hpp"

using PCDanmakuFlameMaster::model::DanmakuType;
using PCDanmakuFlameMaster::model::IDisplayer;
using PCDanmakuFlameMaster::model::Danmakus;
using PCDanmakuFlameMaster::model::Rect;

namespace PCDanmakuFlameMaster {
namespace renderer {

    using AreaSpace = IRenderer::Area;

    void AreaSpace::setEdge(int maxWidth, int maxHeight) {
        mMaxWidth = maxWidth;
        mMaxHeight = maxHeight;
    }

    void AreaSpace::reset() {
        set(static_cast<float>(mMaxWidth), static_cast<float>(mMaxHeight), 0, 0);
    }

    void AreaSpace::resizeToMax() {
        set(0, 0, static_cast<float>(mMaxWidth), static_cast<float>(mMaxHeight));
    }

    void AreaSpace::set(Rect<float>& rect) {
        mRefreshRect = rect;
    }

    void AreaSpace::set(float left, float top, float right, float bottom) {
        mRefreshRect.left = left;
        mRefreshRect.top = top;
        mRefreshRect.right = right;
        mRefreshRect.bottom = bottom;
    }


    using RenderingStateSpace = IRenderer::RenderingState;

    int RenderingStateSpace::addTotalCount(int count) {
        totalDanmakuCount += count;
        return totalDanmakuCount;
    }

    int RenderingStateSpace::addCount(DanmakuType type, int count) {
        switch (type) {
        case DanmakuType::DanmakuType_Scroll_RL:
            r2lDanmakuCount += count;
            return r2lDanmakuCount;
        case DanmakuType::DanmakuType_Scroll_LR:
            l2rDanmakuCount += count;
            return l2rDanmakuCount;
        case DanmakuType::DanmakuType_Fix_Top:
            ftDanmakuCount += count;
            return ftDanmakuCount;
        case DanmakuType::DanmakuType_Fix_Bottom:
            fbDanmakuCount += count;
            return fbDanmakuCount;
        case DanmakuType::DanmakuType_Special:
            specialDanmakuCount += count;
            return specialDanmakuCount;
        }
        return 0;
    }

    void RenderingStateSpace::reset() {
        r2lDanmakuCount = l2rDanmakuCount = ftDanmakuCount = fbDanmakuCount = specialDanmakuCount = totalDanmakuCount = 0;
        sysTime = beginTime = endTime = consumingTime = 0;
        nothingRendered = false;
    }

    void RenderingStateSpace::set(RenderingState& other) {
        this->r2lDanmakuCount = other.r2lDanmakuCount;
        this->l2rDanmakuCount = other.l2rDanmakuCount;
        this->ftDanmakuCount = other.ftDanmakuCount;
        this->fbDanmakuCount = other.fbDanmakuCount;
        this->specialDanmakuCount = other.specialDanmakuCount;
        this->totalDanmakuCount = other.totalDanmakuCount;
        this->consumingTime = other.consumingTime;
        this->beginTime = other.beginTime;
        this->endTime = other.endTime;
        this->nothingRendered = other.nothingRendered;
        this->sysTime = other.sysTime;
        this->inWaitingState = other.inWaitingState;
    }

}
}
