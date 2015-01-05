/**
 * @file    DrawHelper.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-09
 */

#include <string>
#include "../SkiaAssembly.hpp"
#include <skia/core/SkCanvas.h>
#include <skia/core/SkColor.h>
#include <skia/core/SkPaint.h>
#include <skia/core/SkRect.h>
#include "../model/Rect.hpp"
#include "DrawHelper.hpp"

using PCDanmakuFlameMaster::model::Rect;

namespace PCDanmakuFlameMaster {
namespace controller {

    bool DrawHelper::USE_DRAWCOLOR_TO_CLEAR_CANVAS = false;
    bool DrawHelper::PAINT_FPS_Inited = false;

    void DrawHelper::useDrawColorToClearCanvas(bool use) {
        USE_DRAWCOLOR_TO_CLEAR_CANVAS = use;
    }

    void DrawHelper::drawFPS(SkCanvas& canvas, std::string& text) {
        if (!PAINT_FPS_Inited) {
            PAINT_FPS.setColor(SK_ColorRED);
            PAINT_FPS.setTextSize(25);
            PAINT_FPS_Inited = true;
        }
        SkISize canvasSize = canvas.getBaseLayerSize();
        int top = canvasSize.height() - 25;

        clearCanvas(canvas, 10, static_cast<float>(top - 25), PAINT_FPS.measureText(text.c_str(), text.length()) + 20, static_cast<float>(canvasSize.height()));
    }

    void DrawHelper::clearCanvas(SkCanvas& canvas) {
        if (USE_DRAWCOLOR_TO_CLEAR_CANVAS) {
            canvas.drawColor(SK_ColorTRANSPARENT, SkXfermode::kClear_Mode);
        } else {
            SkISize size = canvas.getBaseLayerSize();
            RECT.set(0, 0, static_cast<SkScalar>(size.width()), static_cast<SkScalar>(size.height()));
            clearCanvas(canvas, RECT);
        }
    }

    void DrawHelper::fillTransparent(SkCanvas& canvas) {
        canvas.drawColor(SK_ColorTRANSPARENT, SkXfermode::kClear_Mode);
    }

    void DrawHelper::clearCanvas(SkCanvas& canvas, float left, float top, float right, float bottom) {
        RECT.set(left, top, right, bottom);
        clearCanvas(canvas, RECT);
    }

    void DrawHelper::clearCanvas(SkCanvas& canvas, Rect<float> rect) {
        RECT.set(rect.left, rect.top, rect.right, rect.bottom);
        clearCanvas(canvas, RECT);
    }

    void DrawHelper::clearCanvas(SkCanvas& canvas, SkRect& rect) {
        if (rect.width() <= 0 || rect.height() <= 0)
            return;
        canvas.drawRect(rect, PAINT);
    }

}
}
