#ifndef _PCDFM_DEMO_SKSTUPIDVIEW_HPP
#define _PCDFM_DEMO_SKSTUPIDVIEW_HPP

#include "SkiaAssembly.hpp"
#include <skia/views/SkOSWindow_Win.h>

class SkSurface; class SkCanvas; class GrContext; struct GrGLInterface; class GrRenderTarget;

namespace PCDanmakuFlameMaster {
namespace ui {

    class SkStupidView : public SkOSWindow {
    public:
        SkStupidView(void* nativeHandle);

        virtual ~SkStupidView();

        bool isHardwareAccelerated();

        void setSize(int width, int height);

    public:
        bool setupBackend(SkBackEndTypes backendType, int msaaSampleCount);

        bool teardownBackend();

        SkSurface* createSurface() override;

        void publishCanvas(SkCanvas* canvas);

    protected:
        virtual void onAttach() { };

        virtual void onDetach() { };

        virtual void onResize() { };

        //virtual void onSurfaceCreated() = 0;

        //virtual void onSurfaceChanged() = 0;

        //virtual void onSurfaceDestroyed() = 0;

    private:
        void windowSizeChanged();

    private:
        int mMSAASampleCount = 0;
        SkBackEndTypes mBackendType = kNone_BackEndType;
#if SK_SUPPORT_GPU
        GrContext* mCurrentContext = nullptr;
        const GrGLInterface* mCurrentInterface = nullptr;
        GrRenderTarget* mCurrentRenderTarget = nullptr;
#endif
    };

} // namespace ui
} // namespace PCDanmakuFlameMaster

#endif // _PCDFM_DEMO_SKSTUPIDVIEW_HPP
