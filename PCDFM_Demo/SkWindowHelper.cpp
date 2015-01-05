#include <cassert>
#include "SkiaAssembly.hpp"
#include <skia/core/SkSurface.h>
#include <skia/core/SkCanvas.h>
#include <skia/gpu/GrContext.h>
#include <skia/gpu/gl/GrGLUtil.h>
#include <skia/gpu/gl/GrGLDefines.h>
#include <skia/gpu/gl/GrGLInterface.h>
#include <skia/gpu/SkGpuDevice.h>
#include <skia/views/SkOSWindow_Win.h>
#include "SkWindowHelper.hpp"

namespace PCDFM_Demo {

    bool SkWindowHelper::IsGpuDeviceType(DeviceType deviceType) {
#ifdef SK_SUPPORT_GPU
        switch (deviceType) {
        case kGPU_DeviceType:
#if SK_ANGLE
        case kANGLE_DeviceType:
#endif // SK_ANGLE
        case kNullGPU_DeviceType:
            return true;
        default:
            return false;
        }
#endif // SK_SUPPORT_GPU
        return false;
    }

    bool SkWindowHelper::setUpBackend(SkBackEndTypes backendType, int msaaSampleCount) {
#ifdef SK_SUPPORT_GPU
        switch (backendType) {
        case kNone_BackEndType:
        case kNativeGL_BackEndType:
            mBackendType = kNativeGL_BackEndType;
            mDeviceType = kGPU_DeviceType;
            break;
#ifdef SK_ANGLE
        case kANGLE_BackEndType:
            mBackendType = kANGLE_BackEndType;
            mDeviceType = kANGLE_DeviceType;
            break;
#endif // SK_ANGLE
        default:
            assert(false);
            return false;
        }

        AttachmentInfo attachInfo;
        bool ret = this->attach(mBackendType, msaaSampleCount, &attachInfo);
        if (!ret) {
            SkDebugf("SkWindowHelper::setUpBackend(): Fail to initialize BackEnd");
            return false;
        }
        mMSAASampleCount = msaaSampleCount;

        assert(mCurrentInterface == nullptr);
        SkAutoTUnref<const GrGLInterface> glInterface;
        switch (mDeviceType) {
        case kRaster_DeviceType:
        case kPicture_DeviceType:
        case kGPU_DeviceType:
            glInterface.reset(GrGLCreateNativeInterface());
            break;
#ifdef SK_ANGLE
        case kANGLE_DeviceType:
            glInterface.reset(GrGLCreateANGLEInterface());
            break;
#endif // SK_ANGLE
        case kNullGPU_DeviceType:
            glInterface.reset(GrGLCreateNullInterface());
            break;
        default:
            assert(false);
            return false;
        }

        mCurrentInterface = GrGLInterfaceRemoveNVPR(glInterface.get());

        assert(mCurrentContext == nullptr);
        mCurrentContext = GrContext::Create(kOpenGL_GrBackend, (GrBackendContext)mCurrentInterface);
        if (mCurrentContext == nullptr || mCurrentInterface == nullptr) {
            SkSafeUnref(mCurrentContext);
            SkSafeUnref(mCurrentInterface);
            mCurrentContext = nullptr; mCurrentInterface = nullptr;
            SkDebugf("SkWindowHelper::setUpBackend(): Create GrContext failed");
            this->detach();
            return false;
        }
#endif // SK_SUPPORT_GPU
        
        this->windowSizeChanged();
        return true;
    }

    bool SkWindowHelper::tearDownBackend() {
#ifdef SK_SUPPORT_GPU
        if (mCurrentContext) {
            mCurrentContext->abandonContext();
            mCurrentContext->unref();
            mCurrentContext = nullptr;
        }
        SkSafeUnref(mCurrentInterface);
        mCurrentInterface = nullptr;
        SkSafeUnref(mCurrentRenderTarget);
        mCurrentRenderTarget = nullptr;
#endif // SK_SUPPORT_GPU
        this->detach();
        mBackendType = kNone_BackEndType;
        return true;
    }

    SkSurface* SkWindowHelper::createSurface() {
#ifdef SK_SUPPORT_GPU
        if (IsGpuDeviceType(mDeviceType) && mCurrentContext) {
            SkSurfaceProps props(this->getSurfaceProps());
            return SkSurface::NewRenderTargetDirect(mCurrentRenderTarget, &props);
        }
#endif // SK_SUPPORT_GPU
        return nullptr;
    }

    void SkWindowHelper::publishCanvas(SkCanvas* canvas) {
#ifdef SK_SUPPORT_GPU
        if (mCurrentContext) {
            mCurrentContext->flush();
            if (!IsGpuDeviceType(mDeviceType)) {
                mCurrentContext->setRenderTarget(mCurrentRenderTarget);
                const SkBitmap& bitmap = this->getBitmap();
                mCurrentRenderTarget->writePixels(
                    0, 0, bitmap.width(), bitmap.height(),
                    SkImageInfo2GrPixelConfig(bitmap.colorType(), bitmap.alphaType()),
                    bitmap.getPixels(), bitmap.rowBytes(), GrContext::kFlushWrites_PixelOp
                );
            }
        }
#endif
        this->present();
    }

    void SkWindowHelper::windowSizeChanged() {
#ifdef SK_SUPPORT_GPU
        if (mCurrentContext) {
            AttachmentInfo attachInfo;
            this->attach(SkBackEndTypes::kNativeGL_BackEndType, mMSAASampleCount, &attachInfo);

            GrBackendRenderTargetDesc desc;
            desc.fWidth = SkScalarRoundToInt(this->width());
            desc.fHeight = SkScalarRoundToInt(this->height());
            desc.fConfig = kSkia8888_GrPixelConfig;
            desc.fOrigin = kBottomLeft_GrSurfaceOrigin;
            desc.fSampleCnt = attachInfo.fSampleCount;
            desc.fStencilBits = attachInfo.fStencilBits;

            GrGLint buffer;
            GR_GL_GetIntegerv(mCurrentInterface, GR_GL_FRAMEBUFFER_BINDING, &buffer);
            desc.fRenderTargetHandle = buffer;

            SkSafeUnref(mCurrentRenderTarget);
            mCurrentRenderTarget = mCurrentContext->wrapBackendRenderTarget(desc);
        }
#endif // SK_SUPPORT_GPU
    }

} // namespace PCDFM_Demo
