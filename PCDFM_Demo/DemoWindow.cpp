#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <atlbase.h>
#include <atlwin.h>
#include <wtl/atlapp.h>
#include <wtl/atlframe.h>
#include <wtl/atlmisc.h>
#include <wtl/atlcrack.h>
#include "SkiaAssembly.hpp"
#include <skia/core/SkGraphics.h>
#include <skia/core/SkSurface.h>
#include <skia/core/SkCanvas.h>
//#include <skia/core/SkTypeface.h>
#include <skia/views/SkEvent.h>
#include "SkWindowHelper.hpp"
#include "SkStupidView.hpp"
#include <vlc/vlc.h>
#include <string>
#include "Utils.hpp"
#include "resource.h"
#include "DemoWindow.hpp"
#include "GLSL.hpp"
#include "TestDanmakuView.hpp"

extern CAppModule module;

using namespace xl;

namespace PCDFM_Demo {

    static const char* vlc_args[] = {
        "-V", "opengl",
        //"--avcodec-hw=any",
        "--ignore-config",
        "-I", "dummy",
        "--no-media-library"
    };

    static const int vlc_argc = sizeof(vlc_args) / sizeof(vlc_args[0]);

    static const char* fileName = R"(G:\Downloads\ver_00_14-20860012-avc-647688-aac-128001-4556460-448861359-13159231c4aec2b17a58d9c5662a98b4-1401287444969.mp4)";
    static const char* file2 = R"(F:\Downloads\686067-1.flv)";

    static libvlc_instance_t* vlcInstance = nullptr;
    static libvlc_media_t* vlcMedia = nullptr;
    static libvlc_media_player_t* vlcMediaPlayer = nullptr;

    //static SkWindowHelper* skWindow = nullptr;
    static TestDanmakuView* danmakuView = nullptr;
    static SkSurface* surface = nullptr;
    static SkCanvas* canvas = nullptr;

    void setupPixelFormat(HDC hdc) {
        PIXELFORMATDESCRIPTOR pfd = {0};
        int pixelFormat = GetPixelFormat(hdc);
        DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd);
        __asm int 3;
    }

    LRESULT DemoWindow::OnCreate(LPCREATESTRUCT pcs) {
        rootMenu.Attach(LoadMenu(module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MENU1)));
        this->SetMenu(rootMenu);
        //-------------------------------------------------
        HWND hStatic = CreateWindow("Static", "a static", SS_BITMAP | WS_VISIBLE | WS_CHILD, 40, 40, 854, 480, this->m_hWnd, 0, GetModuleHandle(nullptr), 0);
        HDC hStaticDC = ::GetDC(hStatic);
        SetBkColor(hStaticDC, 0x00000000);
        SetBkMode(hStaticDC, TRANSPARENT);


        //::ReleaseDC(hStatic, hStaticDC);
        //danmakuStatic.Create(this->m_hWnd, 0, "my static", WS_CHILD | WS_VISIBLE | SS_CENTER);
        //this->Attach(danmakuStatic.m_hWnd);
        //this->Attach(this->danmakuStatic);
        //-------------------------------------------------
        vlcInstance = libvlc_new(vlc_argc, vlc_args);
        vlcMedia = libvlc_media_new_path(vlcInstance, file2);
        vlcMediaPlayer = libvlc_media_player_new_from_media(vlcMedia);
        libvlc_media_release(vlcMedia);
        libvlc_media_player_set_hwnd(vlcMediaPlayer, this->m_hWnd);
        
        
        SkGraphics::Init();
        SkEvent::Init();

        danmakuView = new TestDanmakuView(hStatic);
        danmakuView->setSize(854, 480);

        //skWindow = new SkWindowHelper(this->m_hWnd);
        //skWindow->setColorType(kRGBA_8888_SkColorType);
        //skWindow->setVisibleP(true);
        //skWindow->setClipToBounds(false);
        //
        //skWindow->SkWindow::setSize(1024, 576);
        //skWindow->setUpBackend(SkOSWindow::SkBackEndTypes::kNativeGL_BackEndType, 4);
        //                
        //surface = skWindow->createSurface();
        //canvas = surface->getCanvas();

        SetMsgHandled(FALSE);
        return 0;
    }

    LRESULT DemoWindow::OnMenuLoadVideo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        MessageBox("LoadVideo!");
        
        return 0;
    }

    LRESULT DemoWindow::OnMenuLoadDanmaku(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        return 0;
    }

    LRESULT DemoWindow::OnMenuStart(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        libvlc_media_player_play(vlcMediaPlayer);
        setupPixelFormat(this->GetDC());

        return 0;
    }

    LRESULT DemoWindow::OnMenuPause(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        libvlc_media_player_pause(vlcMediaPlayer);
        return 0;
    }

    LRESULT DemoWindow::OnMenuResume(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        libvlc_media_player_play(vlcMediaPlayer);
        return 0;
    }

    LRESULT DemoWindow::OnMenuStop(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        libvlc_media_player_stop(vlcMediaPlayer);
        return 0;
    }
    

    LRESULT DemoWindow::OnMenuHide(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        //const char* str = "ÖÐÎÄ mother fuck skia! ²âÊÔ";
        //const wchar_t* wideChar = L"¿í×Ö·û fuck skia! ²ÝÄàÂí";
        //
        //std::string u8str = ansiToUTF8(str);
        //std::string u8str2 = wideToUTF8(wideChar);
        //
        //canvas->drawColor(SK_ColorWHITE);
        //
        //SkPaint paint;
        //paint.setColor(SK_ColorBLACK);
        ////paint.setFakeBoldText(true);
        //paint.setStyle(SkPaint::kStroke_Style);
        //paint.setStrokeWidth(1.0f);
        //paint.setTextSize(25);
        //paint.setAntiAlias(true);
        //paint.setLCDRenderText(true);
        //
        //SkTypeface* font = SkTypeface::CreateFromName("SimHei", SkTypeface::Style::kNormal);
        ////SkTypeface* font = SkTypeface::CreateFromFile(R"(F:\AndroidFonts\DroidSansFallback.ttf)");
        //paint.setTypeface(font);
        //
        //canvas->drawText(u8str2.c_str(), u8str2.length(), 0, 40, paint);
        //
        ////skWindow->draw(canvas);
        //
        //skWindow->publishCanvas(canvas);
        danmakuView->start();
        return 0;
    }

    LRESULT DemoWindow::OnMenuShow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        //skWindow->publishCanvas(canvas);
        danmakuView->stop();
        return 0;
    }

    LRESULT DemoWindow::Dispose() {
        if (!disposed) {
            libvlc_media_player_stop(vlcMediaPlayer);
            libvlc_media_player_release(vlcMediaPlayer);
            libvlc_release(vlcInstance);
            disposed = true;
        }
        return 0;
    }
    
    LRESULT DemoWindow::OnMenuExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
        Dispose();
        this->DestroyWindow();
        return 0;
    }

    void DemoWindow::OnDestory() {
        if (!disposed) Dispose();
        //PostQuitMessage(0);
        //skWindow->tearDownBackend();
        delete danmakuView;
        //delete skWindow;
        SetMsgHandled(FALSE);
    }

} // namespace PCDFM_Demo
