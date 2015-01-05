/**
 * @file    SkDisplayer.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-28
 */

#include <map>
#include "../SkiaAssembly.hpp"
#include <skia/utils/SkCamera.h>
#include <skia/core/SkCanvas.h>
#include <skia/core/SkMatrix.h>
#include <skia/core/SkPaint.h>
#include <skia/core/SkTypeface.h>
#include <skia/effects/SkBlurDrawLooper.h>
#include "AlphaValue.hpp"
#include "BaseDanmaku.hpp"
#include "AbsDisplayer.hpp"
#include "DanmakuGlobalConfig.hpp"
#include "DrawingCacheHolder.hpp"
#include "../parser/DanmakuFactory.hpp"
#include "SkDisplayer.hpp"

#define PCDFM_MAX(a,b) (((a)>(b))?(a):(b))

using PCDanmakuFlameMaster::parser::DanmakuFactory;

namespace PCDanmakuFlameMaster {
namespace model {

    SkDisplayer::ClassInitializer::ClassInitializer() {
        sLastScaleTextSize = 0.0f;
        UNDERLINE_HEIGHT = 4;
        SHADOW_RADIUS = 4.0f;
        STROKE_WIDTH = 3.5f;
        HAS_SHADOW = CONFIG_HAS_SHADOW = false;
        HAS_STROKE = CONFIG_HAS_STROKE = true;
        ANTI_ALIAS = CONFIG_ANTI_ALIAS = true;
        
        PAINT.setStrokeWidth(STROKE_WIDTH);
        PAINT_DUPLICATE = PAINT;
        UNDERLINE_PAINT.setStyle(SkPaint::Style::kStroke_Style);
        UNDERLINE_PAINT.setStrokeWidth(static_cast<float>(UNDERLINE_HEIGHT));
        BORDER_PAINT.setStyle(SkPaint::Style::kStroke_Style);
        BORDER_PAINT.setStrokeWidth(static_cast<float>(BORDER_WIDTH));
    }

    void SkDisplayer::setTypeface(SkTypeface& font) {
        PAINT.setTypeface(&font);
    }

    void SkDisplayer::setShadowRadius(float s) {
        SHADOW_RADIUS = s;
    }

    void SkDisplayer::setPaintStrokeWidth(float s) {
        PAINT.setStrokeWidth(s);
        STROKE_WIDTH = s;
    }

    void SkDisplayer::setFakeBoldText(bool fakeBoldText) {
        PAINT.setFakeBoldText(fakeBoldText);
    }

    void SkDisplayer::update(SkCanvas& canvas) {
        this->canvas = &canvas;
        if (this->canvas != nullptr) {
            SkISize size = this->canvas->getBaseLayerSize();
            width = size.width();
            height = size.height();
        }
    }

    int SkDisplayer::getWidth() const {
        return width;
    }

    int SkDisplayer::getHeight() const {
        return height;
    }

    float SkDisplayer::getDensity() const {
        return density;
    }

    int SkDisplayer::getDensityDpi() const {
        return densityDpi;
    }

    void SkDisplayer::draw(const BaseDanmaku& danmaku) {
        float top = danmaku.getTop();
        float left = danmaku.getLeft();
        if (canvas != nullptr) {
            SkPaint* alphaPaint = nullptr;
            bool needRestore = false;

            if (danmaku.getType() == DanmakuType::DanmakuType_Special) {
                if (danmaku.getAlpha() == AlphaValue::TRANSPARENT)
                    return;
                if (danmaku.rotationY != 0 || danmaku.rotationZ != 0) {
                    saveCanvas(danmaku, *canvas, left, top);
                    needRestore = true;
                }
                if (danmaku.getAlpha() != AlphaValue::MAX) {
                    alphaPaint = &ALPHA_PAINT;
                    alphaPaint->setAlpha(static_cast<uint8_t>(danmaku.getAlpha()));
                }
            }

            if (alphaPaint != nullptr && alphaPaint->getAlpha() == AlphaValue::TRANSPARENT)
                return;

            bool cacheDrawn = false;
            if (danmaku.hasDrawingCache()) {
                DrawingCacheHolder holder; // TODO
                if (true /* Has cache */) {
                    canvas->drawBitmap(*holder.bitmap, left, top, alphaPaint);
                    cacheDrawn = true;
                }
            }

            if (!cacheDrawn) {
                if (alphaPaint != nullptr) {
                    PAINT.setAlpha(alphaPaint->getAlpha());
                } else {
                    resetPaintAlpha(PAINT);
                }
                drawDanmaku(danmaku, *canvas, left, top, true);
            }
            
            if (needRestore) {
                restoreCanvas(*canvas);
            }
        }
    }

    void SkDisplayer::resetPaintAlpha(SkPaint& paint) {
        if (paint.getAlpha() != AlphaValue::MAX) {
            paint.setAlpha(AlphaValue::MAX);
        }
    }

    void SkDisplayer::restoreCanvas(SkCanvas& canvas) {
        canvas.restore();
    }

    int SkDisplayer::saveCanvas(const BaseDanmaku& danmaku, SkCanvas& canvas, float left, float top) {
        camera.save();
        camera.rotateY(-danmaku.rotationY);
        camera.rotateZ(-danmaku.rotationZ);
        camera.getMatrix(&matrix);
        matrix.preTranslate(-left, -top);
        matrix.postTranslate(left, top);
        camera.restore();
        int count = canvas.save();
        canvas.concat(matrix);
        return count;
    }

    void SkDisplayer::drawDanmaku(const BaseDanmaku& danmaku, SkCanvas& canvas, float left, float top, bool quick) {
        float _left = left;
        float _top = top;

        left += danmaku.padding;
        top += danmaku.padding;

        if (danmaku.borderColor != 0) {
            left += BORDER_WIDTH;
            top += BORDER_WIDTH;
        }

        HAS_STROKE = CONFIG_HAS_STROKE;
        HAS_SHADOW = CONFIG_HAS_SHADOW;
        ANTI_ALIAS = !quick && CONFIG_ANTI_ALIAS;
        
        SkPaint& paint = getPaint(danmaku, quick);

        SkPaint::FontMetrics fontMetrics;
        paint.getFontMetrics(&fontMetrics);

        if (!danmaku.lines.empty()) {
            auto& lines = danmaku.lines;
            if (lines.size() == 1) {
                if (hasStroke(danmaku)) {
                    applyPaintConfig(danmaku, paint, true);
                    canvas.drawText(lines[0].c_str(), lines[0].length(), left, top - fontMetrics.fAscent, paint);
                }
                applyPaintConfig(danmaku, paint, false);
                canvas.drawText(lines[0].c_str(), lines[0].length(), left, top - fontMetrics.fAscent, paint);
            } else {
                auto count = lines.size();
                float textHeight = danmaku.paintHeight / count;
                for (decltype(count) t = 0; t < count; t++) {
                    if (lines[t].empty())
                        continue;
                    if (hasStroke(danmaku)) {
                        applyPaintConfig(danmaku, paint, true);
                        canvas.drawText(lines[t].c_str(), lines[t].length(), left, top + t * textHeight - fontMetrics.fAscent, paint);
                    }
                    applyPaintConfig(danmaku, paint, false);
                    canvas.drawText(lines[t].c_str(), lines[t].length(), left, top + t * textHeight - fontMetrics.fAscent, paint);
                }
            }
        } else {
            if (hasStroke(danmaku)) {
                applyPaintConfig(danmaku, paint, true);
                canvas.drawText(danmaku.text.c_str(), danmaku.text.length(), left, top - fontMetrics.fAscent, paint);
            }
            applyPaintConfig(danmaku, paint, false);
            canvas.drawText(danmaku.text.c_str(), danmaku.text.length(), left, top - fontMetrics.fAscent, paint);
        }

        if (danmaku.underlineColor != 0) {
            SkPaint& linePaint = getUnderlinePaint(danmaku);
            float bottom = _top + danmaku.paintHeight - UNDERLINE_HEIGHT;
            canvas.drawLine(_left, bottom, left + danmaku.paintWidth, bottom, linePaint);
        }

        if (danmaku.borderColor != 0) {
            SkPaint& borderPaint = getBorderPaint(danmaku);
            SkRect rect;
            rect.set(_left, _top, _left + danmaku.paintWidth, _top + danmaku.paintHeight);
            canvas.drawRect(rect, borderPaint);
        }

    }

    bool SkDisplayer::hasStroke(const BaseDanmaku& danmaku) {
        return (HAS_STROKE && STROKE_WIDTH > 0 && danmaku.textShadowColor != 0);
    }

    SkPaint& SkDisplayer::getBorderPaint(const BaseDanmaku& danmaku) {
        BORDER_PAINT.setColor(danmaku.borderColor);
        return BORDER_PAINT;
    }

    SkPaint& SkDisplayer::getUnderlinePaint(const BaseDanmaku& danmaku) {
        UNDERLINE_PAINT.setColor(danmaku.underlineColor);
        return UNDERLINE_PAINT;
    }

    static const float BLUR_SIGMA_SCALE = 0.57735f;

    float SkDisplayer::convertRadiusToSigma(float radius) {
        return radius > 0 ? BLUR_SIGMA_SCALE * radius + 0.5f : 0.0f;
    }

    float SkDisplayer::convertSigmaToRadius(float sigma) {
        return sigma > 0.5f ? (sigma - 0.5f) / BLUR_SIGMA_SCALE : 0.0f;
    }

    SkPaint& SkDisplayer::getPaint(const BaseDanmaku& danmaku) {
        return getPaint(danmaku, false);
    }

    SkPaint& SkDisplayer::getPaint(const BaseDanmaku& danmaku, bool quick) {
        SkPaint* paint = nullptr;

        if (quick) {
            paint = &PAINT_DUPLICATE;
            *paint = PAINT;
        } else {
            paint = &PAINT;
        }
        paint->setTextSize(danmaku.textSize);
        applyTextScaleConfig(danmaku, *paint);
        
        // ignore the transparent textShadowColor
        if (!HAS_SHADOW || SHADOW_RADIUS <= 0 || danmaku.textShadowColor == 0) {
            paint->setLooper(nullptr);
        } else {
            SkScalar sigma = convertRadiusToSigma(SHADOW_RADIUS);
            paint->setLooper(SkBlurDrawLooper::Create(static_cast<SkColor>(danmaku.textShadowColor), sigma, 0, 0));
        }

        paint->setAntiAlias(ANTI_ALIAS);
        return *paint;
    }

    void SkDisplayer::applyPaintConfig(const BaseDanmaku& danmaku, SkPaint& paint, bool stroke) {
        if (DanmakuGlobalConfig::DEFAULT.isTranslucent) {
            if (stroke) {
                paint.setStyle(SkPaint::kStroke_Style);
                uint32_t color = (danmaku.textShadowColor & 0x00FFFFFF) | (DanmakuGlobalConfig::DEFAULT.transparency << 24);
                paint.setColor(color);
            } else {
                paint.setStyle(SkPaint::kFill_Style);
                uint32_t color = (danmaku.textColor & 0x00FFFFFF) | (DanmakuGlobalConfig::DEFAULT.transparency << 24);
                paint.setColor(color);
            }
            paint.setAlpha(DanmakuGlobalConfig::DEFAULT.transparency);
        } else {
            if (stroke) {
                paint.setStyle(SkPaint::kStroke_Style);
                paint.setColor(danmaku.textShadowColor);
            } else {
                paint.setStyle(SkPaint::kFill_Style);
                paint.setColor(danmaku.textColor);
            }
            paint.setAlpha(AlphaValue::MAX);
        }
    }

    void SkDisplayer::applyTextScaleConfig(const BaseDanmaku& danmaku, SkPaint& paint) {
        if (!DanmakuGlobalConfig::DEFAULT.isTextScaled)
            return;

        auto found = sCachedScaleSize.find(danmaku.textSize);
        float size = (found != sCachedScaleSize.end()) ? found->second : 0.0f;

        if (found == sCachedScaleSize.end() || sLastScaleTextSize != DanmakuGlobalConfig::DEFAULT.scaleTextSize) {
            sLastScaleTextSize = DanmakuGlobalConfig::DEFAULT.scaleTextSize;
            size = danmaku.textSize * DanmakuGlobalConfig::DEFAULT.scaleTextSize;
            sCachedScaleSize.insert({danmaku.textSize, size});
        }

        paint.setTextSize(size);
    }

    void SkDisplayer::measure(BaseDanmaku& danmaku) {
        SkPaint paint = getPaint(danmaku);
        if (HAS_STROKE) {
            applyPaintConfig(danmaku, paint, true);
        }
        calcPaintHW(danmaku, paint);
        if (HAS_STROKE) {
            applyPaintConfig(danmaku, paint, false);
        }
    }

    void SkDisplayer::calcPaintHW(BaseDanmaku& danmaku, SkPaint& textPaint) {
        float width = 0;
        float textHeight = getTextHeight(textPaint);

        if (danmaku.lines.empty()) {
            width = danmaku.text.empty() ? 0 : textPaint.measureText(danmaku.text.c_str(), danmaku.text.length());
            setDanmakuPaintWidthAndHeight(danmaku, width, textHeight);
            return;
        }
        
        for (std::string& str : danmaku.lines) {
            if (str.length() > 0) {
                float tr = textPaint.measureText(str.c_str(), str.length());
                width = PCDFM_MAX(tr, width);
            }
        }

        setDanmakuPaintWidthAndHeight(danmaku, width, danmaku.lines.size() * textHeight);
    }

    void SkDisplayer::setDanmakuPaintWidthAndHeight(BaseDanmaku& danmaku, float width, float height) {
        float pw = width + 2 * danmaku.padding;
        float ph = height + 2 * danmaku.padding;

        if (danmaku.borderColor != 0) {
            pw += 2 * BORDER_WIDTH;
            ph += 2 * BORDER_WIDTH;
        }

        danmaku.paintWidth = pw + getStrokeWidth();
        danmaku.paintHeight = ph;
    }

    float SkDisplayer::getTextHeight(SkPaint& textPaint) {
        float textSize = textPaint.getTextSize();
        auto found = sTextHeightCache.find(textSize);
        float textHeight = (found != sTextHeightCache.end()) ? found->second : 0.0f;

        if (found == sTextHeightCache.end()) {
            SkPaint::FontMetrics fontMetrics;
            textPaint.getFontMetrics(&fontMetrics);
            textHeight = fontMetrics.fDescent - fontMetrics.fAscent + fontMetrics.fLeading;
            sTextHeightCache.insert({textSize, textHeight});
        }
        return textHeight;
    }

    void SkDisplayer::clearTextHeightCache() {
        sTextHeightCache.clear();
        sCachedScaleSize.clear();
    }

    float SkDisplayer::getScaledDensity() const {
        return scaledDensity;
    }

    void SkDisplayer::resetSlopPixel(float factor) {
        float d = PCDFM_MAX(density, scaledDensity);
        float temp = static_cast<float>(getWidth() / DanmakuFactory::BILI_PLAYER_WIDTH);
        d = PCDFM_MAX(factor, temp);
        
        float slop = d * DanmakuFactory::DANMAKU_MEDIUM_TEXTSIZE;
        mSlopPixel = static_cast<int>(slop);

        if (factor > 1.0f) {
            mSlopPixel = static_cast<int>(slop * factor);
        }
    }

    int SkDisplayer::getSlopPixel() const {
        return mSlopPixel;
    }

    void SkDisplayer::setDensities(float density, int densityDpi, float scaledDensity) {
        this->density = density;
        this->densityDpi = densityDpi;
        this->scaledDensity = scaledDensity;
    }

    void SkDisplayer::setSize(int width, int height) {
        this->width = width;
        this->height = height;
    }

    void SkDisplayer::setExtraData(SkCanvas& data) {
        update(data);
    }

    SkCanvas& SkDisplayer::getExtraData() {
        return *this->canvas;
    }

    time_t SkDisplayer::getAverageRenderingTime() const {
        return this->lastAverageRenderingTime;
    }

    void SkDisplayer::setAverageRenderingTime(time_t ms) {
        this->lastAverageRenderingTime = ms;
    }

    float SkDisplayer::getStrokeWidth() const {
        if (HAS_SHADOW && HAS_STROKE) {
            return PCDFM_MAX(SHADOW_RADIUS, STROKE_WIDTH);
        }
        if (HAS_SHADOW) {
            return SHADOW_RADIUS;
        }
        if (HAS_STROKE) {
            return STROKE_WIDTH;
        }
        return 0.0f;
    }

    time_t SkDisplayer::getLastFrameRenderingTime() const {
        return this->lastFrameRenderingTime;
    }

    void SkDisplayer::setLastFrameRenderingTime(time_t ms) {
        this->lastFrameRenderingTime = ms;
    }
}
}
