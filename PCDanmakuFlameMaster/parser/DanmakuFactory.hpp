/**
 * @file    DanmakuFactory.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-27
 */

#ifndef _PCDFM_PARSER_DANMAKUFACTORY_HPP
#define _PCDFM_PARSER_DANMAKUFACTORY_HPP

#include <cstdint>
#include <string>
#include "../model/BaseDanmaku.hpp"
#include "../model/IDisplayer.hpp"
#include "../model/Duration.hpp"
#include "../model/Danmakus.hpp"

using PCDanmakuFlameMaster::model::BaseDanmaku;
using PCDanmakuFlameMaster::model::DanmakuType;
using PCDanmakuFlameMaster::model::IDisplayer;
using PCDanmakuFlameMaster::model::Duration;
using PCDanmakuFlameMaster::model::Danmakus;

namespace PCDanmakuFlameMaster {
namespace parser {

    class DanmakuFactory {
    public:
        static void resetDurationsData();
        static void notifyDispSizeChanged(IDisplayer& disp);
        static BaseDanmaku createDanmaku(DanmakuType type);
        static BaseDanmaku createDanmaku(DanmakuType type, IDisplayer& disp);
        static BaseDanmaku createDanmaku(DanmakuType type, IDisplayer& disp, float viewportScale);
        static BaseDanmaku createDanmaku(DanmakuType type, int viewportWidth, int viewportHeight, float viewportScale);
        static BaseDanmaku createDanmaku(DanmakuType type, float viewportWidth, float viewportHeight, float viewportSizeFactor);
        static bool updateViewportState(float viewportWidth, float viewportHeight, float viewportSizeFactor);
        static void updateSpecialDanmakusData(float scaleX, float scaleY);
        static void updateMaxDanmakuDuration();
        static void updateDurationFactor(float f);
        static void fillText(BaseDanmaku& danmaku, std::string& text);
        static void fillTranslationData(BaseDanmaku& item, float beginX, float beginY, float endX, float endY,
                                        time_t translationDuration, time_t translationStartDelay, float scaleX, float scaleY);
        static void fillLinePathData(BaseDanmaku& item, float* points[], float scaleX, float scaleY);
        static void fillAlphaData(BaseDanmaku& item, int beginAlpha, int endAlpha, time_t alphaDuration);
        static void updateSpecialDanmakuDuration(BaseDanmaku& item);
    public:
        static const int OLD_BILI_PLAYER_WIDTH = 539;
        static const int BILI_PLAYER_WIDTH = 682;
        static const int OLD_BILI_PLAYER_HEIGHT = 385;
        static const int BILI_PLAYER_HEIGHT = 438;
        static const time_t COMMON_DANMAKU_DURATION = 3800;   // Bilibili danmaku duration in original resolution
        static const int DANMAKU_MEDIUM_TEXTSIZE = 25;
        static const time_t MIN_DANMAKU_DURATION = 4000;
        static const time_t MAX_DANMAKU_DURATION_HIGH_DENSITY = 9000;
        
        static int CURRENT_DISP_WIDTH, CURRENT_DISP_HEIGHT;
        static time_t REAL_DANMAKU_DURATION;
        static time_t MAX_DANMAKU_DURATION;

        static Duration MAX_Duration_Scroll_Danmaku;
        static Duration MAX_Duration_Fix_Danmaku;
        static Duration MAX_Duration_Special_Danmaku;
        static bool MAX_Duration_Scroll_Danmaku_Inited;
        static bool MAX_Duration_Fix_Danmaku_Inited;
        static bool MAX_Duration_Special_Danmaku_Inited;
        static Danmakus sSpecialDanmakus;
        static IDisplayer* sLastDisp;
    private:
        static float CURRENT_DISP_SIZE_FACTOR;
    };

}
}

#endif // _PCDFM_PARSER_DANMAKUFACTORY_HPP
