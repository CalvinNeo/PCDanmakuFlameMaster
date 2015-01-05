/**
* @file    BaseDanmakuParser.cpp
* @brief   ...
* @author  zheng qian <xqq@0ginr.com>
* @date    2014-11-28
*/

#include "DanmakuFactory.hpp"
#include "BaseDanmakuParser.hpp"

namespace PCDanmakuFlameMaster {
namespace parser {

    BaseDanmakuParser& BaseDanmakuParser::setDisplayer(IDisplayer& disp) {
        mDisp = &disp;
        mDispWidth = disp.getWidth();
        mDispHeight = disp.getHeight();
        mDispDensity = disp.getDensity();
        mScaledDensity = disp.getScaledDensity();
        DanmakuFactory::updateViewportState(static_cast<float>(mDispWidth), static_cast<float>(mDispHeight), getViewportSizeFactor());
        DanmakuFactory::updateMaxDanmakuDuration();
        return *this;
    }

    float BaseDanmakuParser::getViewportSizeFactor() const {
        return 1 / (mDispDensity - 0.6f);
    }

    IDisplayer& BaseDanmakuParser::getDisplayer() const {
        return *mDisp;  
    }

    BaseDanmakuParser& BaseDanmakuParser::load(void* pDataSource) {
        mDataSource = pDataSource;
        return *this;
    }

    BaseDanmakuParser& BaseDanmakuParser::setTimer(DanmakuTimer& timer) {
        mTimer = timer;
        return *this;
    }

    DanmakuTimer BaseDanmakuParser::getTimer() const {
        return mTimer;
    }

    Danmakus BaseDanmakuParser::getDanmakus() {
        if (mDanmakus != nullptr) {
            return *mDanmakus;
        }
        DanmakuFactory::resetDurationsData();
        mDanmakus = std::make_shared<Danmakus>(parse());
        releaseDataSource();
        DanmakuFactory::updateMaxDanmakuDuration();
        return *mDanmakus;
    }

    void BaseDanmakuParser::releaseDataSource() {
        if (mDataSource != nullptr) {
            // TODO
        }
    }

    void BaseDanmakuParser::release() {
        releaseDataSource();
    }


}
}
