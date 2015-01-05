#include <iostream>
#include <atlbase.h>
#include <atlwin.h>
#include <wtl/atlapp.h>
#include <wtl/atlframe.h>
#include <wtl/atlmisc.h>
#include <wtl/atlcrack.h>
#include "../PCDanmakuFlameMaster/PCDFM.hpp"
#include "Assembly.hpp"
#include "DemoWindow.hpp"

using namespace PCDFM_Demo;

CAppModule module;

static const int windowStartupWidth = 1024;
static const int windowStartupHeight = 576;

int main(int argc, char* argv[]) {
    module.Init(NULL, GetModuleHandle(nullptr));
    
    DemoWindow demoWindow;
    if (!demoWindow.CreateEx()) {
        std::cout << "Error while creating demo window.\n";
        return -1;
    }

    demoWindow.SetWindowTextA("PCDanmakuFlameMaster Demo");
    demoWindow.ResizeClient(windowStartupWidth, windowStartupHeight);
    demoWindow.ShowWindow(1);
    demoWindow.UpdateWindow();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    module.Term();
    return msg.wParam;
}
