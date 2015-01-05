/**
 * @file    DrawingCacheHolder.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-03
 */

#ifndef _PCDFM_MODEL_DRAWING_CACHE_HOLDER_HPP
#define _PCDFM_MODEL_DRAWING_CACHE_HOLDER_HPP

#include "../SkiaAssembly.hpp"
#include <skia/core/SkCanvas.h>
#include <skia/core/SkBitmap.h>

namespace PCDanmakuFlameMaster {
namespace model {

    class DrawingCacheHolder {
    public:
        DrawingCacheHolder();
        DrawingCacheHolder(int width, int height);
        DrawingCacheHolder(int width, int height, int density);
        void buildCache(int width, int height, int density, bool checkSizeEquals);
        void erase();
        void dispose();
    public:
        SkCanvas* canvas = nullptr;
        SkBitmap* bitmap = nullptr;
        void* extra = nullptr;
        int width = 0;
        int height = 0;
        bool drawn = false;
    private:
        int mDensity = 0;
    };

}
}

#endif // _PCDFM_MODEL_DRAWING_CACHE_HOLDER_HPP
