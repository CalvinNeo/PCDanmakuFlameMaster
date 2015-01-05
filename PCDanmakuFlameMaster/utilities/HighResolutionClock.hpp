/**
 * @file    HighResolutionClock.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-06
 */

#ifndef _PCDFM_UTILS_HRCLOCK_HPP
#define _PCDFM_UTILS_HRCLOCK_HPP

#include <cstdint>
#include <chrono>

namespace PCDanmakuFlameMaster {
namespace util {

#ifdef _MSC_VER
    typedef class HighResolutionClockWin32 HighResolutionClock;
#else
    typedef class HighResolutionClockCpp11 HighResolutionClock;
#endif

    class HighResolutionClockCpp11 {
    public:
        using TimePoint = decltype(std::chrono::high_resolution_clock::now());
    public:
        inline HighResolutionClockCpp11() = default;

        inline HighResolutionClockCpp11& begin() {
            startTime = std::chrono::high_resolution_clock::now();
            return *this;
        }

        inline HighResolutionClockCpp11& end() {
            TimePoint endTime = std::chrono::high_resolution_clock::now();
            auto elapsed = endTime - startTime;
            milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            return *this;
        }

        inline static time_t getCurrentMillis() {
            return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
            //return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        }
    public:
        time_t milliseconds = 0;
    private:
        TimePoint startTime;
    };

#ifdef _MSC_VER

    typedef union _LargeInteger {
        struct {
            uint32_t LowPart;
            int32_t HighPart;
        };
        struct {
            uint32_t LowPart;
            int32_t HighPart;
        } u;
        int64_t QuadPart;
    } LargeInteger;

    class HighResolutionClockWin32 {
    public:
        HighResolutionClockWin32();
        HighResolutionClockWin32& begin();
        HighResolutionClockWin32& end();
        static time_t getCurrentMillis();
    public:
        time_t milliseconds = 0;
    private:
        LargeInteger startTime;
        LargeInteger mFrequency;
    };

#endif

}
}

#endif // _PCDFM_UTILS_HRCLOCK_HPP
