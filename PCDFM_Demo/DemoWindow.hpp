#ifndef _PCDFM_DEMO_DEMOWINDOW_HPP
#define _PCDFM_DEMO_DEMOWINDOW_HPP

#include <atlbase.h>
#include <atlwin.h>
#include <wtl/atlapp.h>
#include <wtl/atlframe.h>
#include <wtl/atlmisc.h>
#include <wtl/atlcrack.h>
#include <wtl/atlctrls.h>
#include "resource.h"

namespace PCDFM_Demo {

    class DemoWindow : public CFrameWindowImpl<DemoWindow> {
    public:
        DECLARE_FRAME_WND_CLASS("PCDFM_Demo", NULL);

        BEGIN_MSG_MAP_EX(DemoWindow)
            MSG_WM_CREATE(OnCreate)
            COMMAND_ID_HANDLER(ID_FILES_LOADVIDEO, OnMenuLoadVideo)
            COMMAND_ID_HANDLER(ID_FILES_LOADDANMAKU, OnMenuLoadDanmaku)
            COMMAND_ID_HANDLER(ID_FILES_EXIT, OnMenuExit)
            COMMAND_ID_HANDLER(ID_START, OnMenuStart)
            COMMAND_ID_HANDLER(ID_PAUSE, OnMenuPause)
            COMMAND_ID_HANDLER(ID_RESUME, OnMenuResume)
            COMMAND_ID_HANDLER(ID_STOP, OnMenuStop)
            COMMAND_ID_HANDLER(ID_HIDE, OnMenuHide)
            COMMAND_ID_HANDLER(ID_SHOW, OnMenuShow)
            MSG_WM_DESTROY(OnDestory)
            CHAIN_MSG_MAP(CFrameWindowImpl<DemoWindow>)
        END_MSG_MAP()

        LRESULT OnCreate(LPCREATESTRUCT pcs);
        LRESULT OnMenuLoadVideo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        LRESULT OnMenuLoadDanmaku(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        LRESULT OnMenuExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        LRESULT OnMenuStart(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        LRESULT OnMenuPause(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        LRESULT OnMenuResume(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        LRESULT OnMenuStop(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        LRESULT OnMenuHide(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        LRESULT OnMenuShow(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
        LRESULT Dispose();
        void OnDestory();
    private:
        CMenu rootMenu;
        CStatic danmakuStatic;
        bool disposed = false;
    };

} // namespace PCDFM_Demo

#endif // _PCDFM_DEMO_DEMOWINDOW_HPP
