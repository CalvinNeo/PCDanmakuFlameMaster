/**
 * @file    DrawingCacheHolder.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-03
 */

#include "../SkiaAssembly.hpp"
#include <skia/core/SkCanvas.h>
#include <skia/core/SkBitmap.h>
#include "DrawingCacheHolder.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    DrawingCacheHolder::DrawingCacheHolder() {
        // do nothing
    }

    DrawingCacheHolder::DrawingCacheHolder(int width, int height) {
        buildCache(width, height, 0, true);
    }

    DrawingCacheHolder::DrawingCacheHolder(int width, int height, int density) {
        mDensity = density;
        buildCache(width, height, density, true);
    }

    void DrawingCacheHolder::buildCache(int w, int h, int density, bool checkSizeEquals) {
        bool reuse = checkSizeEquals ? (w == width && h == height) : (w <= width && h <= height);
        if (reuse && bitmap != nullptr) {
            bitmap->eraseColor(SK_ColorTRANSPARENT);
            return;
        }
        if (bitmap != nullptr) {
            dispose();
        }

        this->width = w;
        this->height = h;

        bitmap = new SkBitmap();
        SkImageInfo info = SkImageInfo::Make(w, h, SkColorType::kRGBA_8888_SkColorType,
                                                   SkAlphaType::kPremul_SkAlphaType,
                                                   SkColorProfileType::kSRGB_SkColorProfileType);
        bitmap->allocPixels(info);
        bitmap->eraseARGB(0, 0, 0, 0);
        
        if (density > 0) {
            mDensity = density;
            // TODO
        }
        if (canvas == nullptr) {
            canvas = new SkCanvas(*bitmap);
            // TODO
        } else {
            delete canvas;
            canvas = new SkCanvas(*bitmap);
        }
        
    }

    void DrawingCacheHolder::erase() {
        if (bitmap != nullptr) {
            bitmap->eraseColor(SK_ColorTRANSPARENT);
        }
    }

    void DrawingCacheHolder::dispose() {
        width = height = 0;
        if (canvas) {
            delete canvas;
            canvas = nullptr;
        }
        if (bitmap) {
            delete bitmap;
            bitmap = nullptr;
        }
    }

}
}
