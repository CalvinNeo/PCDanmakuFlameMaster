#ifndef _PCDFM_DEMO_SKWINDOWHELPER_HPP
#define _PCDFM_DEMO_SKWINDOWHELPER_HPP

#include <skia/views/SkOSWindow_Win.h>

class SkSurface; class GrContext; struct GrGLInterface; class GrRenderTarget;

namespace PCDFM_Demo {
    
    class SkWindowHelper : public SkOSWindow {
    public:
        enum DeviceType {
            kRaster_DeviceType,
            kPicture_DeviceType,
#ifdef SK_SUPPORT_GPU
            kGPU_DeviceType,
#ifdef SK_ANGLE
            kANGLE_DeviceType,
#endif // SK_ANGLE
            kNullGPU_DeviceType
#endif // SK_SUPPORT_GPU
        };
    public:
        static bool IsGpuDeviceType(DeviceType deviceType);

        SkWindowHelper(HWND hWnd) : SkOSWindow(hWnd) { };

        ~SkWindowHelper() { };

        bool isHardwareAccelerated() {
            return IsGpuDeviceType(mDeviceType);
        }

        bool setUpBackend(SkBackEndTypes backendType, int msaaSampleCount);

        bool tearDownBackend();

        SkSurface* createSurface();

        void publishCanvas(SkCanvas* canvas);

        void windowSizeChanged();

        DeviceType getDeviceType() {
            return mDeviceType;
        }

        GrContext* getGrContext() {
            return mCurrentContext;
        }

        GrRenderTarget* getGrRenderTarget() {
            return mCurrentRenderTarget;
        }
    public:

    private:
        DeviceType mDeviceType = kRaster_DeviceType;
        SkBackEndTypes mBackendType = kNone_BackEndType;

        int mMSAASampleCount = 0;
        GrContext* mCurrentContext = nullptr;
        const GrGLInterface* mCurrentInterface = nullptr;
        GrRenderTarget* mCurrentRenderTarget = nullptr;
    };

} // namespace PCDFM_Demo

#endif // _PCDFM_DEMO_SKWINDOWHELPER_HPP
