/**
 * @file    SkDisplayer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-28
 */

#ifndef _PCDFM_MODEL_SKDISPLAYER_HPP
#define _PCDFM_MODEL_SKDISPLAYER_HPP

#include <cstdint>
#include <map>
#include "../SkiaAssembly.hpp"
#include <skia/utils/SkCamera.h>
#include <skia/core/SkCanvas.h>
#include <skia/core/SkMatrix.h>
#include <skia/core/SkPaint.h>
#include <skia/core/SkTypeface.h>
//#include "BaseDanmaku.hpp"
#include "AbsDisplayer.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    class BaseDanmaku;

    class SkDisplayer final : public AbsDisplayer<SkCanvas> {
    public:
        void setExtraData(SkCanvas& data) override;
        SkCanvas& getExtraData() override;
        int getWidth() const override;
        int getHeight() const override;
        float getDensity() const override;
        int getDensityDpi() const override;
        void draw(const BaseDanmaku& danmaku) override;
        float getScaledDensity() const override;
        int getSlopPixel() const override;
        void measure(BaseDanmaku& danmaku) override;
        time_t getAverageRenderingTime() const override;
        time_t getLastFrameRenderingTime() const override;
        float getStrokeWidth() const override;
        void resetSlopPixel(float factor) override;
        void setDensities(float density, int densityDpi, float scaledDensity) override;
        void setSize(int width, int height) override;
        void setAverageRenderingTime(time_t ms) override;
        void setLastFrameRenderingTime(time_t ms) override;
        static void setTypeface(SkTypeface& font);
        static void setShadowRadius(float s);
        static void setPaintStrokeWidth(float s);
        static void setFakeBoldText(bool fakeBoldText);
        static void drawDanmaku(const BaseDanmaku& danmaku, SkCanvas& canvas, float left, float top, bool quick);
        static bool hasStroke(const BaseDanmaku& danmaku);
        static SkPaint& getBorderPaint(const BaseDanmaku& danmaku);
        static SkPaint& getUnderlinePaint(const BaseDanmaku& danmaku);
        static SkPaint& getPaint(const BaseDanmaku& danmaku);
        static SkPaint& getPaint(const BaseDanmaku& danmaku, bool quick);
        static void clearTextHeightCache();
        static float convertRadiusToSigma(float radius);
        static float convertSigmaToRadius(float sigma);
    private:
        void update(SkCanvas& canvas);
        void resetPaintAlpha(SkPaint& paint);
        void restoreCanvas(SkCanvas& canvas);
        int saveCanvas(const BaseDanmaku& danmaku, SkCanvas& canvas, float left, float top);
        void calcPaintHW(BaseDanmaku& danmaku, SkPaint& textPaint);
        void setDanmakuPaintWidthAndHeight(BaseDanmaku& danmaku, float width, float height);
        static void applyPaintConfig(const BaseDanmaku& danmaku, SkPaint& paint, bool stroke);
        static void applyTextScaleConfig(const BaseDanmaku& danmaku, SkPaint& paint);
        static float getTextHeight(SkPaint& textPaint);
    public:
        class ClassInitializer {
        public:
            ClassInitializer();
        };
    public:
        static SkPaint PAINT;
        static SkPaint PAINT_DUPLICATE;
        static int UNDERLINE_HEIGHT;
        static const int BORDER_WIDTH = 4;
        static bool CONFIG_HAS_SHADOW;
        static bool CONFIG_HAS_STROKE;
        static bool CONFIG_ANTI_ALIAS;
    private:
        static std::map<float, float> sTextHeightCache;
        static float sLastScaleTextSize;
        static std::map<float, float> sCachedScaleSize;
        static SkPaint ALPHA_PAINT;
        static SkPaint UNDERLINE_PAINT;
        static SkPaint BORDER_PAINT;
        static float SHADOW_RADIUS;
        static float STROKE_WIDTH;
        static bool HAS_SHADOW;
        static bool HAS_STROKE;
        static bool ANTI_ALIAS;
    private:
        static ClassInitializer staticIniter;
    public:
        SkCanvas* canvas = nullptr;
    private:
        Sk3DView camera;
        SkMatrix matrix;
        int width = 0;
        int height = 0;
        float density = 1.0f;
        int densityDpi = 160;
        float scaledDensity = 1;
        int mSlopPixel = 0;
        time_t lastAverageRenderingTime = 16;
        time_t lastFrameRenderingTime = 0;

    };

}
}

#endif // _PCDFM_MODEL_SKDISPLAYER_HPP
