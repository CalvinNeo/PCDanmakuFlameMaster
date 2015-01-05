/**
 * @file    DanmakuGlobalConfig.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-02
 */

#include <algorithm>
#include "../SkiaAssembly.hpp"
#include <skia/core/SkTypeface.h>
#include "../model/AlphaValue.hpp"
#include "BaseDanmaku.hpp"
#include "SkDisplayer.hpp"
#include "DanmakuGlobalConfig.hpp"
#include "GlobalFlagValues.hpp"
#include "../parser/DanmakuFactory.hpp"

using PCDanmakuFlameMaster::parser::DanmakuFactory;

namespace PCDanmakuFlameMaster {
namespace model {

    DanmakuGlobalConfig& DanmakuGlobalConfig::setTypeface(SkTypeface& font) {
        if (mFont != &font) {
            mFont = &font;
            SkDisplayer::clearTextHeightCache();
            SkDisplayer::setTypeface(font);
            notifyConfigChanged(DanmakuConfigTag::TYPEFACE);
        }
        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setDanmakuTransparency(float p) {
        int newTransparency = static_cast<int>(p * AlphaValue::MAX);
        if (newTransparency != transparency) {
            transparency = newTransparency;
            isTranslucent = (newTransparency != AlphaValue::MAX);
            notifyConfigChanged(DanmakuConfigTag::TRANSPARENCY, p);
        }
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setScaleTextSize(float p) {
        if (scaleTextSize != p) {
            scaleTextSize = p;
            SkDisplayer::clearTextHeightCache();
            GlobalFlagValues::updateMeasureFlag();
            notifyConfigChanged(DanmakuConfigTag::SCALE_TEXTSIZE, p);
        }
        return *this;
    }

    bool DanmakuGlobalConfig::getFTDanmakuVisibility() {
        return FTDanmakuVisibility;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setFTDanmakuVisibility(bool visible) {
        setDanmakuVisible(visible, DanmakuType::DanmakuType_Fix_Top);
        setFilterData(std::string(""), mFilterTypes); // TODO
        if (FTDanmakuVisibility != visible) {
            FTDanmakuVisibility = visible;
            notifyConfigChanged(DanmakuConfigTag::FT_DANMAKU_VISIBILITY, visible);
        }
        return *this;
    }

    template <typename T>
    void DanmakuGlobalConfig::setFilterData(std::string& tag, T data) {

    }

    void DanmakuGlobalConfig::setDanmakuVisible(bool visible, DanmakuType type) {
        if (visible) {
            mFilterTypes.remove(type);
        } else if (std::find(mFilterTypes.begin(), mFilterTypes.end(), type) != mFilterTypes.end()) {
            mFilterTypes.push_back(type);
        }
    }

    bool DanmakuGlobalConfig::getFBDanmakuVisibility() {
        return FBDanmakuVisibility;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setFBDanmakuVisibility(bool visible) {
        setDanmakuVisible(visible, DanmakuType::DanmakuType_Fix_Bottom);
        setFilterData(std::string(""), mFilterTypes); // TODO
        if (FBDanmakuVisibility != visible) {
            FBDanmakuVisibility = visible;
            notifyConfigChanged(DanmakuConfigTag::FB_DANMAKU_VISIBILITY, visible);
        }
        return *this;
    }

    bool DanmakuGlobalConfig::getL2RDanmakuVisibility() {
        return L2RDanmakuVisibility;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setL2RDanmakuVisibility(bool visible) {
        setDanmakuVisible(visible, DanmakuType::DanmakuType_Scroll_LR);
        setFilterData(std::string(""), mFilterTypes);
        if (L2RDanmakuVisibility != visible) {
            L2RDanmakuVisibility = visible;
            notifyConfigChanged(DanmakuConfigTag::L2R_DANMAKU_VISIBILITY, visible);
        }
        return *this;
    }

    bool DanmakuGlobalConfig::getR2LDanmakuVisibility() {
        return R2LDanmakuVisibility;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setR2LDanmakuVisibility(bool visible) {
        setDanmakuVisible(visible, DanmakuType::DanmakuType_Scroll_RL);
        setFilterData(std::string(""), mFilterTypes);
        if (R2LDanmakuVisibility != visible){
            R2LDanmakuVisibility = visible;
            notifyConfigChanged(DanmakuConfigTag::R2L_DANMAKU_VISIBILIY, visible);
        }
        return *this;
    }

    bool DanmakuGlobalConfig::getSpecialDanmakuVisibility() {
        return SpecialDanmakuVisibility;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setSpecialDanmakuVisibility(bool visible) {
        setDanmakuVisible(visible, DanmakuType::DanmakuType_Special);
        setFilterData(std::string(""), mFilterTypes);
        if (SpecialDanmakuVisibility != visible) {
            SpecialDanmakuVisibility = visible;
            notifyConfigChanged(DanmakuConfigTag::SPECIAL_DANMAKU_VISIBILITY, visible);
        }
        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setMaximumVisibleSizeInScreen(int maxSize) {
        maximumNumsInScreen = maxSize;

        if (maxSize == 0) {
            // TODO
            notifyConfigChanged(DanmakuConfigTag::MAXIMUM_NUMS_IN_SCREEN, maxSize);
            return *this;
        }

        if (maxSize == -1) {
            // TODO
            notifyConfigChanged(DanmakuConfigTag::MAXIMUM_NUMS_IN_SCREEN, maxSize);
            return *this;
        }
        setFilterData(std::string(""), maxSize);
        notifyConfigChanged(DanmakuConfigTag::MAXIMUM_NUMS_IN_SCREEN, maxSize);
        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setDanmakuStyle(int style, float size) {
        switch (style) {
        case DANMAKU_STYLE_NONE:
            SkDisplayer::CONFIG_HAS_SHADOW = false;
            SkDisplayer::CONFIG_HAS_STROKE = false;
            break;
        case DANMAKU_STYLE_SHADOW:
            SkDisplayer::CONFIG_HAS_SHADOW = true;
            SkDisplayer::CONFIG_HAS_STROKE = false;
            SkDisplayer::setShadowRadius(size);
            break;
        case DANMAKU_STYLE_DEFAULT:
        case DANMAKU_STYLE_STROKEN:
            SkDisplayer::CONFIG_HAS_SHADOW = false;
            SkDisplayer::CONFIG_HAS_STROKE = true;
            SkDisplayer::setPaintStrokeWidth(size);
            break;
        }
        notifyConfigChanged(DanmakuConfigTag::DANMAKU_STYLE, style, size);
        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setDanmakuBold(bool bold) {
        SkDisplayer::setFakeBoldText(bold);
        notifyConfigChanged(DanmakuConfigTag::DANMAKU_BOLD, bold);
        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setColorValueWhiteList(std::initializer_list<int> colors) {
        mColorValueWhiteList.clear();
        if (colors.size() == 0) {
            // TODO: Danmaku Filters
        } else {
            for (auto iter = colors.begin(); iter != colors.end(); ++iter) {
                mColorValueWhiteList.push_back(*iter);
                setFilterData(std::string(""), mColorValueWhiteList);
            }
        }
        notifyConfigChanged(DanmakuConfigTag::COLOR_VALUE_WHITE_LIST, mColorValueWhiteList);
        return *this;
    }

    std::list<int>& DanmakuGlobalConfig::getColorValueWhiteList() {
        return mColorValueWhiteList;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setUserHashBlackList(std::initializer_list<std::string&> hashes) {
        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::removeUserHashBlackList(std::initializer_list<std::string&> hashes) {

        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::addUserHashBlackList(std::initializer_list<std::string&> hashes) {

        return *this;
    }

    std::list<std::string> DanmakuGlobalConfig::getUserHashBlackList() {

    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setUserIdBlackList(std::initializer_list<int> ids) {

        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::removeUserIdBlackList(std::initializer_list<int> ids) {

        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::addUserIdBlackList(std::initializer_list<int> ids) {

        return *this;
    }

    std::list<int>& DanmakuGlobalConfig::getUserIdBlackList() {
        return mUserIdBlackList;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::blockGuestDanmaku(bool block) {
        mBlockGuestDanmaku = block;
        if (block) {
            setFilterData(std::string(""), block); // TODO
        } else {
            // TODO
        }
        notifyConfigChanged(DanmakuConfigTag::BLOCK_GUEST_DANMAKU, block);
        return *this;
    }

    DanmakuGlobalConfig& DanmakuGlobalConfig::setScrollSpeedFactor(float p) {
        if (scrollSpeedFactor != p) {
            scrollSpeedFactor = p;
            DanmakuFactory::updateDurationFactor(p);
            GlobalFlagValues::updateMeasureFlag();
            notifyConfigChanged(DanmakuConfigTag::SCROLL_SPEED_FACTOR, p);
        }
        return *this;
    }

    void DanmakuGlobalConfig::registerConfigChangedCallback(ConfigChangedCallback& listener) {
        mCallbackList.push_back(listener);
    }

    void DanmakuGlobalConfig::unregisterConfigChangedCallback(ConfigChangedCallback& listener) {
        mCallbackList.remove(listener);
    }

    void DanmakuGlobalConfig::notifyConfigChanged(DanmakuConfigTag tag, ...) {
        if (!mCallbackList.empty()) {
            for (ConfigChangedCallback& cb : mCallbackList) {
                if (cb.callback != nullptr)
                    cb.callback(*this, tag);
            }
        }
    }
    
}
}
