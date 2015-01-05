#include "SkiaAssembly.hpp"
#include <skia/core/SkSurface.h>
#include <skia/gpu/GrContext.h>
#include <skia/gpu/SkGpuDevice.h>
#include <skia/gpu/gl/GrGLUtil.h>
#include <skia/gpu/gl/GrGLInterface.h>
#include <skia/views/SkOSWindow_Win.h>
#include "SkStupidView.hpp"

namespace PCDanmakuFlameMaster {
namespace ui {

    SkStupidView::SkStupidView(void* nativeHandle) : SkOSWindow(nativeHandle) {
        this->setColorType(kN32_SkColorType);
        this->setVisibleP(true);
        this->setClipToBounds(false);
    }

    SkStupidView::~SkStupidView() {
        if (mBackendType != kNone_BackEndType) {
            teardownBackend();
        }

        SkSafeUnref(mCurrentContext);
        SkSafeUnref(mCurrentInterface);
        SkSafeUnref(mCurrentRenderTarget);
    }

    bool SkStupidView::setupBackend(SkBackEndTypes backendType, int msaaSampleCount) {
        SkASSERT(mBackendType == kNone_BackEndType);

        mBackendType = kNone_BackEndType;

#if SK_SUPPORT_GPU
        switch (backendType) {
            case kNone_BackEndType:
            case kNativeGL_BackEndType:
                mBackendType = kNativeGL_BackEndType;
                break;
#if SK_ANGLE
            case kANGLE_BackEndType:
                mBackendType = kANGLE_BackEndType;
                break;
#endif // SK_ANGLE
            default:
                SkASSERT(false);
                break;
        }

        AttachmentInfo attachInfo;
        bool result = this->attach(mBackendType, msaaSampleCount, &attachInfo);
        if (!result) {
            SkDebugf("SkStupidView::setupBackend(): Fail to initialize GL backend");
            return false;
        }
        mMSAASampleCount = msaaSampleCount;

        SkASSERT(mCurrentInterface == nullptr);
        SkAutoTUnref<const GrGLInterface> glInterface;
        switch (mBackendType) {
            case kNone_BackEndType:
            case kNativeGL_BackEndType:
                glInterface.reset(GrGLCreateNativeInterface());
                break;
#if SK_ANGLE
            case kANGLE_BackEndType:
                glInterface.reset(GrGLCreateANGLEInterface());
                break;
#endif // SK_ANGLE
            default:
                SkASSERT(false);
                break;
        }
        
        mCurrentInterface = GrGLInterfaceRemoveNVPR(glInterface.get());
        
        SkASSERT(mCurrentContext == nullptr);
        mCurrentContext = GrContext::Create(kOpenGL_GrBackend, (GrBackendContext)mCurrentInterface);

        if (mCurrentContext == nullptr || mCurrentInterface == nullptr) {
            SkSafeUnref(mCurrentContext);
            SkSafeUnref(mCurrentInterface);
            mCurrentContext = nullptr;
            mCurrentInterface = nullptr;
            SkDebugf("SkStupidView::setupBackend(): Fail to setup 3D");

            this->detach();
        }
#endif // SK_SUPPORT_GPU
        this->windowSizeChanged();
        onAttach();
        return true;
    }

    bool SkStupidView::teardownBackend() {
#if SK_SUPPORT_GPU
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
        onDetach();
        return true;
    }

    bool SkStupidView::isHardwareAccelerated() {
#if SK_SUPPORT_GPU
        return (mBackendType == kNativeGL_BackEndType
#if SK_ANGLE
             || mBackendType == kANGLE_BackEndType
#endif // SK_ANGLE
            );
#endif // SK_SUPPORT_GPU
        return false;
    }

    SkSurface* SkStupidView::createSurface() {
        SkSurface* surface = nullptr;

        if (mCurrentContext) {
            SkSurfaceProps props(this->getSurfaceProps());
            surface = SkSurface::NewRenderTargetDirect(mCurrentRenderTarget, &props);
        }
        
        if (surface == nullptr) {
            surface = this->SkOSWindow::createSurface();
        }

        return surface;
    }

    void SkStupidView::publishCanvas(SkCanvas* canvas) {
#if SK_SUPPORT_GPU
        if (mCurrentContext) {
            mCurrentContext->flush();

            if (!isHardwareAccelerated()) {
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

    void SkStupidView::setSize(int width, int height) {
        this->SkView::setSize(static_cast<SkScalar>(width), static_cast<SkScalar>(height));
        this->windowSizeChanged();
        this->onResize();
    }

    void SkStupidView::windowSizeChanged() {
#if SK_SUPPORT_GPU
        if (mCurrentContext) {
            AttachmentInfo attachInfo;
            this->attach(mBackendType, mMSAASampleCount, &attachInfo);
            
            GrBackendRenderTargetDesc desc;
            desc.fWidth = SkScalarRoundToInt(this->width());
            desc.fHeight = SkScalarRoundToInt(this->height());
            desc.fConfig = kRGBA_8888_GrPixelConfig; //kSkia8888_GrPixelConfig;
            desc.fOrigin = kBottomLeft_GrSurfaceOrigin;
            desc.fSampleCnt = attachInfo.fSampleCount;
            desc.fStencilBits = attachInfo.fStencilBits;
            
            GrGLint buffer;
            GR_GL_GetIntegerv(mCurrentInterface, GR_GL_FRAMEBUFFER_BINDING, &buffer);
            desc.fRenderTargetHandle = buffer;
            
            SkSafeUnref(mCurrentRenderTarget);
            mCurrentRenderTarget = mCurrentContext->wrapBackendRenderTarget(desc);
        }
#endif
    }

}
}
