/**
 * @file    DrawHelper.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-09
 */

#ifndef _PCDFM_CONTROLLER_DRAW_HELPER_HPP
#define _PCDFM_CONTROLLER_DRAW_HELPER_HPP

#include <string>
#include "../SkiaAssembly.hpp"
#include <skia/core/SkCanvas.h>
#include <skia/core/SkColor.h>
#include <skia/core/SkPaint.h>
#include <skia/core/SkRect.h>
#include "../model/Rect.hpp"

using PCDanmakuFlameMaster::model::Rect;

class SkCanvas; struct RectF;

namespace PCDanmakuFlameMaster {
namespace controller {

    class DrawHelper {
    public:
        static void useDrawColorToClearCanvas(bool use);
        static void drawFPS(SkCanvas& canvas, std::string& text);
        static void clearCanvas(SkCanvas& canvas);
        static void fillTransparent(SkCanvas& canvas);
        static void clearCanvas(SkCanvas& canvas, float left, float top, float right, float bottom);
        static void clearCanvas(SkCanvas& canvas, Rect<float> rect);
        static void clearCanvas(SkCanvas& canvas, SkRect& rect);
    public:
        static SkPaint PAINT, PAINT_FPS;
        static bool PAINT_FPS_Inited;
        static SkRect RECT;
    private:
        static bool USE_DRAWCOLOR_TO_CLEAR_CANVAS;
    };

}
}

#endif // _PCDFM_CONTROLLER_DRAW_HELPER_HPP
