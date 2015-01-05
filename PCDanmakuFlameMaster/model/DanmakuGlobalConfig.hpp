/**
 * @file    DanmakuGlobalConfig.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-02
 */

#ifndef _PCDFM_MODEL_DANMAKU_GLOBAL_CONFIG_HPP
#define _PCDFM_MODEL_DANMAKU_GLOBAL_CONFIG_HPP

#include <list>
#include <string>
#include <functional>
//#include <skia/core/SkTypeface.h>
#include "AlphaValue.hpp"

class SkTypeface;

namespace PCDanmakuFlameMaster {
namespace model {
    enum DanmakuType;
    class DanmakuGlobalConfig {
    public:
        enum DanmakuConfigTag {
            FT_DANMAKU_VISIBILITY,
            FB_DANMAKU_VISIBILITY,
            L2R_DANMAKU_VISIBILITY,
            R2L_DANMAKU_VISIBILIY,
            SPECIAL_DANMAKU_VISIBILITY,
            TYPEFACE,
            TRANSPARENCY,
            SCALE_TEXTSIZE,
            MAXIMUM_NUMS_IN_SCREEN,
            DANMAKU_STYLE,
            DANMAKU_BOLD,
            COLOR_VALUE_WHITE_LIST,
            USER_ID_BLACK_LIST,
            USER_HASH_BLACK_LIST,
            SCROLL_SPEED_FACTOR,
            BLOCK_GUEST_DANMAKU
        };
        
        enum BorderType {
            NONE,
            SHADOW,
            STROKEN
        };

        static const int DANMAKU_STYLE_DEFAULT = -1;    // Auto
        static const int DANMAKU_STYLE_NONE = 0;        // None
        static const int DANMAKU_STYLE_SHADOW = 1;      // Shadow
        static const int DANMAKU_STYLE_STROKEN = 2;     // Stroke

        //typedef std::function<void(DanmakuGlobalConfig&, DanmakuConfigTag, ...)> ConfigChangedCallback;
        class ConfigChangedCallback {
            ConfigChangedCallback() = default;
            ConfigChangedCallback(std::function<void(DanmakuGlobalConfig&, DanmakuConfigTag)> callbackFunc) : callback(callbackFunc) { }
        public:
            std::function<void(DanmakuGlobalConfig&, DanmakuConfigTag)> callback = nullptr;
        };
    public:
        static bool isVisibilityRelatedTag(DanmakuConfigTag tag);
    public:
        DanmakuGlobalConfig& setTypeface(SkTypeface& font);
        DanmakuGlobalConfig& setDanmakuTransparency(float p);
        DanmakuGlobalConfig& setScaleTextSize(float p);
        bool getFTDanmakuVisibility();
        DanmakuGlobalConfig& setFTDanmakuVisibility(bool visible);
        template <typename T>
        void setFilterData(std::string& tag, T data);
        void setDanmakuVisible(bool visible, DanmakuType type);
        bool getFBDanmakuVisibility();
        DanmakuGlobalConfig& setFBDanmakuVisibility(bool visible);
        bool getL2RDanmakuVisibility();
        DanmakuGlobalConfig& setL2RDanmakuVisibility(bool visible);
        bool getR2LDanmakuVisibility();
        DanmakuGlobalConfig& setR2LDanmakuVisibility(bool visible);
        bool getSpecialDanmakuVisibility();
        DanmakuGlobalConfig& setSpecialDanmakuVisibility(bool visible);
        DanmakuGlobalConfig& setMaximumVisibleSizeInScreen(int maxSize);
        DanmakuGlobalConfig& setDanmakuStyle(int style, float size);
        DanmakuGlobalConfig& setDanmakuBold(bool bold);
        DanmakuGlobalConfig& setColorValueWhiteList(std::initializer_list<int> colors);
        std::list<int>& getColorValueWhiteList();
        DanmakuGlobalConfig& setUserHashBlackList(std::initializer_list<std::string&> hashes);
        DanmakuGlobalConfig& removeUserHashBlackList(std::initializer_list<std::string&> hashes);
        DanmakuGlobalConfig& addUserHashBlackList(std::initializer_list<std::string&> hashes);
        std::list<std::string> getUserHashBlackList();
        DanmakuGlobalConfig& setUserIdBlackList(std::initializer_list<int> ids);
        DanmakuGlobalConfig& removeUserIdBlackList(std::initializer_list<int> ids);
        DanmakuGlobalConfig& addUserIdBlackList(std::initializer_list<int> ids);
        std::list<int>& getUserIdBlackList();
        DanmakuGlobalConfig& blockGuestDanmaku(bool block);
        DanmakuGlobalConfig& setScrollSpeedFactor(float p);
        void registerConfigChangedCallback(ConfigChangedCallback& listener);
        void unregisterConfigChangedCallback(ConfigChangedCallback& listener);
    private:
        void notifyConfigChanged(DanmakuConfigTag tag, ...);
    public:
        static DanmakuGlobalConfig DEFAULT;
    public:
        SkTypeface* mFont;
        uint32_t transparency = AlphaValue::MAX;
        bool isTranslucent = false;
        float scaleTextSize = 1.0f;
        bool isTextScaled = false;
        bool FTDanmakuVisibility = true;
        bool FBDanmakuVisibility = true;
        bool L2RDanmakuVisibility = true;
        bool R2LDanmakuVisibility = true;
        bool SpecialDanmakuVisibility = true;
        int maximumNumsInScreen = -1;
        float scrollSpeedFactor = 1.0f;
        int refreshRateMS = 15;
        int shadowRadius = 3;
        BorderType shadowType = BorderType::SHADOW;
        std::list<DanmakuType> mFilterTypes;
        std::list<int> mColorValueWhiteList;
        std::list<int> mUserIdBlackList;
        std::list<std::string> mUserHashBlackList;
    private:
        std::list<ConfigChangedCallback> mCallbackList;
        bool mBlockGuestDanmaku = false;
    };

    /*struct DanmakuGlobalConfig::DanmakuConfigTag {
        DanmakuConfigTagEnum value = FT_DANMAKU_VISIBILITY;

        bool isVisibilityRelatedTag() const {
            return (value == FT_DANMAKU_VISIBILITY || value == FB_DANMAKU_VISIBILITY
                 || value == L2R_DANMAKU_VISIBILITY || value == R2L_DANMAKU_VISIBILIY
                 || value == SPECIAL_DANMAKU_VISIBILITY || value == COLOR_VALUE_WHITE_LIST
                 || value == USER_ID_BLACK_LIST);
        }

        DanmakuConfigTag& operator=(const DanmakuConfigTag& rvalue) {
            this->value = rvalue.value;
            return *this;
        }

        DanmakuConfigTag& operator=(DanmakuConfigTagEnum rvalue) {
            this->value = rvalue;
            return *this;
        }

        bool operator==(const DanmakuConfigTag& rightHand) const {
            return (this->value == rightHand.value);
        }

        bool operator==(DanmakuConfigTagEnum rightHand) const {
            return (this->value == rightHand);
        }
    };
    */
}
}

#endif // _PCDFM_MODEL_DANMAKU_GLOBAL_CONFIG_HPP
