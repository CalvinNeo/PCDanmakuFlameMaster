/**
 * @file    SkiaAssembly.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-02
 */

#ifndef _PCDFM_SKIA_ASSEMBLY_HPP
#define _PCDFM_SKIA_ASSEMBLY_HPP

#define SK_INTERNAL
#define SK_GAMMA_SRGB
#define SK_GAMMA_APPLY_TO_A8
#define SK_SCALAR_TO_FLOAT_EXCLUDED
#define SK_ALLOW_STATIC_GLOBAL_INITIALIZERS 1
#define SK_SUPPORT_GPU 1
#define SK_SUPPORT_OPENCL 0
#define SK_FORCE_DISTANCE_FIELD_TEXT 0
#define SK_SCALAR_IS_FLOAT
#define SK_BUILD_FOR_WIN32
#define _CRT_SECURE_NO_WARNINGS
#define GR_GL_FUNCTION_TYPE __stdcall
#define SK_DEVELOPER 1

#ifdef _DEBUG
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_animator.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_core.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_effects.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_images.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_opts.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_opts_sse4.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_opts_ssse3.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_ports.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_sfnt.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_skgpu.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_skgputest.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_utils.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_views.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skia_xml.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/skflate.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/sk_tool_utils.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/views_animated.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/crash_handler.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/experimental.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/flags.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/flags_common.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/libetc1.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/libjpeg.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/libSkKTX.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/picture_utils.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/proc_stats.lib")
    #pragma comment (lib, "3rdparty/skia_lib_debug/resources.lib")
#else

#endif

#endif // _PCDFM_SKIA_ASSEMBLY_HPP
