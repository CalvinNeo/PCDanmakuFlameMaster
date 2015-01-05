#ifndef _PCDFM_DEMO_ASSEMBLY_HPP
#define _PCDFM_DEMO_ASSEMBLY_HPP

#ifdef _DEBUG
//#pragma comment (lib, "../Debug/PCDanmakuFlameMaster.lib")
#else
#pragma comment (lib, "../Release/PCDanmakuFlameMaster.lib")
#endif

#pragma comment (lib, "3rdparty/vlc_lib/libvlc.lib")
#pragma comment (lib, "3rdparty/vlc_lib/libvlccore.lib")

#pragma comment (lib, "Comctl32.lib")
#pragma comment (linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#endif // _PCDFM_DEMO_ASSEMBLY_HPP
