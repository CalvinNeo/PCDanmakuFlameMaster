/**
 * @file    DanmakuFactory.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-27
 */

#include <cmath>
#include <vector>
#include <string>
#include "../model/BaseDanmaku.hpp"
#include "../model/R2LDanmaku.hpp"
#include "../model/L2RDanmaku.hpp"
#include "../model/FBDanmaku.hpp"
#include "../model/FTDanmaku.hpp"
#include "../model/SpecialDanmaku.hpp"
#include "../model/DanmakuGlobalConfig.hpp"
#include "DanmakuFactory.hpp"
#include "../utilities/StringUtils.hpp"

#define PCDFM_MAX(a,b) (((a)>(b))?(a):(b))
#define PCDFM_MIN(a,b) (((a)<(b))?(a):(b))

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::R2LDanmaku;
using PCDanmakuFlameMaster::model::L2RDanmaku;
using PCDanmakuFlameMaster::model::FBDanmaku;
using PCDanmakuFlameMaster::model::FTDanmaku;
using namespace PCDanmakuFlameMaster::util::StringUtils;

namespace PCDanmakuFlameMaster {
namespace parser {

    int DanmakuFactory::CURRENT_DISP_WIDTH = 0;
    int DanmakuFactory::CURRENT_DISP_HEIGHT = 0;
    time_t DanmakuFactory::REAL_DANMAKU_DURATION = COMMON_DANMAKU_DURATION;
    time_t DanmakuFactory::MAX_DANMAKU_DURATION = MIN_DANMAKU_DURATION;
    float DanmakuFactory::CURRENT_DISP_SIZE_FACTOR = 1.0F;

    bool DanmakuFactory::MAX_Duration_Scroll_Danmaku_Inited = false;
    bool DanmakuFactory::MAX_Duration_Fix_Danmaku_Inited = false;
    bool DanmakuFactory::MAX_Duration_Special_Danmaku_Inited = false;

    void DanmakuFactory::resetDurationsData() {
        sLastDisp = nullptr;
        CURRENT_DISP_WIDTH = CURRENT_DISP_HEIGHT = 0;
        sSpecialDanmakus.clear();
        MAX_Duration_Scroll_Danmaku.reset();
        MAX_Duration_Fix_Danmaku.reset();
        MAX_Duration_Special_Danmaku.reset();
        MAX_DANMAKU_DURATION = MIN_DANMAKU_DURATION;
    }

    void DanmakuFactory::notifyDispSizeChanged(IDisplayer& disp) {
        sLastDisp = &disp;
        createDanmaku(DanmakuType::DanmakuType_Scroll_RL, disp);
    }

    BaseDanmaku DanmakuFactory::createDanmaku(DanmakuType type) {
        return createDanmaku(type, *sLastDisp);
    }

    BaseDanmaku DanmakuFactory::createDanmaku(DanmakuType type, IDisplayer& disp) {
        sLastDisp = &disp;
        return createDanmaku(type, disp.getWidth(), disp.getHeight(), CURRENT_DISP_SIZE_FACTOR);
    }

    BaseDanmaku DanmakuFactory::createDanmaku(DanmakuType type, IDisplayer& disp, float viewportScale) {
        sLastDisp = &disp;
        return createDanmaku(type, disp.getWidth(), disp.getHeight(), viewportScale);
    }

    BaseDanmaku DanmakuFactory::createDanmaku(DanmakuType type, int viewportWidth, int viewportHeight, float viewportScale) {
        return createDanmaku(type, static_cast<float>(viewportWidth), static_cast<float>(viewportHeight), viewportScale);
    }

    BaseDanmaku DanmakuFactory::createDanmaku(DanmakuType type, float viewportWidth, float viewportHeight, float viewportSizeFactor) {
        bool sizeChanged = updateViewportState(viewportWidth, viewportHeight, viewportSizeFactor);
        if (!MAX_Duration_Scroll_Danmaku_Inited) {
            MAX_Duration_Fix_Danmaku.setValue(REAL_DANMAKU_DURATION);
            MAX_Duration_Fix_Danmaku.setFactor(1.0f /* TODO*/);
        } else if (sizeChanged) {
            MAX_Duration_Fix_Danmaku.setValue(REAL_DANMAKU_DURATION);
        }

        if (!MAX_Duration_Fix_Danmaku_Inited) {
            MAX_Duration_Fix_Danmaku.setValue(COMMON_DANMAKU_DURATION);
        }

        if (sizeChanged && viewportWidth > 0) {
            updateMaxDanmakuDuration();
            float scaleX = 1.0f;
            float scaleY = 1.0f;
            if (CURRENT_DISP_WIDTH > 0 && CURRENT_DISP_HEIGHT > 0) {
                scaleX = viewportWidth / CURRENT_DISP_WIDTH;
                scaleY = viewportHeight / CURRENT_DISP_HEIGHT;
            }
            if (viewportHeight > 0) {
                updateSpecialDanmakusData(scaleX, scaleY);
            }
        }

        switch (type)
        {
        case DanmakuType::DanmakuType_Scroll_RL:
            return R2LDanmaku(MAX_Duration_Scroll_Danmaku);
            break;
        case DanmakuType::DanmakuType_Fix_Bottom:
            return FBDanmaku(MAX_Duration_Fix_Danmaku);
            break;
        case DanmakuType::DanmakuType_Fix_Top:
            return FTDanmaku(MAX_Duration_Fix_Danmaku);
            break;
        case DanmakuType::DanmakuType_Scroll_LR:
            return L2RDanmaku(MAX_Duration_Scroll_Danmaku);
            break;
        case DanmakuType::DanmakuType_Special:
            // TODO
            return R2LDanmaku(MAX_Duration_Scroll_Danmaku);
            break;
        case DanmakuType::DanmakuType_Code:
            // TODO
            return R2LDanmaku(MAX_Duration_Scroll_Danmaku);
            break;
        default:
            throw std::exception("unsupported danmaku type");
            break;
        }
    }

    bool DanmakuFactory::updateViewportState(float viewportWidth, float viewportHeight, float viewportSizeFactor) {
        bool sizeChanged = false;
        if (CURRENT_DISP_WIDTH != static_cast<int>(viewportWidth)
            || CURRENT_DISP_HEIGHT != static_cast<int>(viewportHeight)
            || CURRENT_DISP_SIZE_FACTOR != static_cast<float>(viewportSizeFactor)) {
            sizeChanged = true;
            REAL_DANMAKU_DURATION = static_cast<time_t>(COMMON_DANMAKU_DURATION * (viewportSizeFactor * viewportWidth / BILI_PLAYER_WIDTH));
            REAL_DANMAKU_DURATION = PCDFM_MIN(MAX_DANMAKU_DURATION_HIGH_DENSITY, REAL_DANMAKU_DURATION);
            REAL_DANMAKU_DURATION = PCDFM_MAX(MAX_DANMAKU_DURATION, REAL_DANMAKU_DURATION);

            CURRENT_DISP_WIDTH = static_cast<int>(viewportWidth);
            CURRENT_DISP_HEIGHT = static_cast<int>(viewportHeight);
            CURRENT_DISP_SIZE_FACTOR = static_cast<float>(viewportSizeFactor);
        }
        return sizeChanged;
    }

    void DanmakuFactory::updateSpecialDanmakusData(float scaleX, float scaleY) {
        // TODO
    }

    void DanmakuFactory::updateMaxDanmakuDuration() {
        time_t maxScrollDuration = MAX_Duration_Scroll_Danmaku.value;
        time_t maxFixDuration = MAX_Duration_Fix_Danmaku.value;
        time_t maxSpecialDuration = MAX_Duration_Special_Danmaku.value;

        MAX_DANMAKU_DURATION = PCDFM_MAX(maxScrollDuration, maxFixDuration);
        MAX_DANMAKU_DURATION = PCDFM_MAX(MAX_DANMAKU_DURATION, maxSpecialDuration);
        
        MAX_DANMAKU_DURATION = PCDFM_MAX(COMMON_DANMAKU_DURATION, MAX_DANMAKU_DURATION);
        MAX_DANMAKU_DURATION = PCDFM_MAX(REAL_DANMAKU_DURATION, MAX_DANMAKU_DURATION);
    }

    void DanmakuFactory::updateDurationFactor(float f) {
        MAX_Duration_Scroll_Danmaku.setFactor(f);
        updateMaxDanmakuDuration();
    }

    void DanmakuFactory::fillText(BaseDanmaku& danmaku, std::string& text) {
        danmaku.text = text;
        if (text.length() == 0 || text.find(BaseDanmaku::DANMAKU_BR_CHAR) == std::string::npos)
            return;

        auto lines = splitString(danmaku.text.c_str(), BaseDanmaku::DANMAKU_BR_CHAR);
        if (lines.size() > 1)
            danmaku.lines = lines;        
    }

    void DanmakuFactory::fillTranslationData(BaseDanmaku& item, float beginX, float beginY, float endX, float endY,
        time_t translationDuration, time_t translationStartDelay, float scaleX, float scaleY) {
        if (item.getType() != DanmakuType::DanmakuType_Special)
            return;
        // TODO
    }

    void DanmakuFactory::fillLinePathData(BaseDanmaku& item, float* points[], float scaleX, float scaleY) {
        if (item.getType() != DanmakuType::DanmakuType_Special /* TODO*/)
            return;
        // TODO
    }

    void DanmakuFactory::fillAlphaData(BaseDanmaku& item, int beginAlpha, int endAlpha, time_t alphaDuration) {
        if (item.getType() != DanmakuType::DanmakuType_Special)
            return;
        // TODO
    }

    void DanmakuFactory::updateSpecialDanmakuDuration(BaseDanmaku& item) {
        // TODO
    }

}
}
