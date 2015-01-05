#include <thread>
#include <chrono>
#include <string>
#include "SkiaAssembly.hpp"
#include <skia/core/SkSurface.h>
#include <skia/core/SkCanvas.h>
#include "TestDanmakuView.hpp"

namespace PCDFM_Demo {

    void TestDanmakuView::initialize() {

    }

    void TestDanmakuView::start() {
        if (stopFlag) {
            stopFlag = false;
            renderThread = std::thread(&TestDanmakuView::working, this);
        }
    }

    void TestDanmakuView::stop() {
        if (stopFlag == false) {
            stopFlag = true;
            renderThread.join();
        }
    }

    void TestDanmakuView::working() {
        setupBackend(kNativeGL_BackEndType, 4);
        
        surface = this->createSurface();
        canvas = surface->getCanvas();
        
        canvas->drawARGB(0, 0, 0, 0, SkXfermode::kClear_Mode);

        static int color = SK_ColorWHITE;
        static int fontSize = 25;

        while (-1) {
            if (stopFlag) {
                //canvas->unref();
                //surface->unref();
                teardownBackend();
                break;
            }

            canvas->drawARGB(0, 0, 0, 0, SkXfermode::kClear_Mode);
            
            SkPaint paint;
            paint.setColor(SK_ColorYELLOW);
            paint.setStyle(SkPaint::kStrokeAndFill_Style);
            paint.setStrokeWidth(1.0f);
            paint.setTextSize(fontSize);
            paint.setAntiAlias(true);
            paint.setLCDRenderText(true);
            std::string teststr = "this is a yellow picture";
            canvas->drawText(teststr.c_str(), teststr.length(), 0, 100, paint);
            //canvas->drawPoint(0, 0, SK_ColorBLACK);
            //color++;
            fontSize++;

            publishCanvas(canvas);

            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
    }

    void TestDanmakuView::onAttach() {

    }

    void TestDanmakuView::onDetach() {

    }

    void TestDanmakuView::onResize() {

    }

}

