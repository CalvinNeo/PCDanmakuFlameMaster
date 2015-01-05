/**
 * @file    HighResolutionClockWin32.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-06
 */

#include "HighResolutionClock.hpp"

#ifdef _MSC_VER
#include <Windows.h>
#endif

namespace PCDanmakuFlameMaster {
namespace util {

#ifdef _MSC_VER

    HighResolutionClockWin32::HighResolutionClockWin32() {
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mFrequency));
    }

    HighResolutionClockWin32& HighResolutionClockWin32::begin() {
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));
        return *this;
    }

    HighResolutionClockWin32& HighResolutionClockWin32::end() {
        LargeInteger endTime;
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&endTime));
        milliseconds = (endTime.QuadPart - startTime.QuadPart) * 1000 / mFrequency.QuadPart;
        return *this;
    }

    time_t HighResolutionClockWin32::getCurrentMillis() {
        LargeInteger frequency;
        LargeInteger currentTime;

        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));
        
        return currentTime.QuadPart * 1000 / frequency.QuadPart;
    }

#endif

}
}
