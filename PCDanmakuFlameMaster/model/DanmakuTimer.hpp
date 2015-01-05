/**
 * @file    DanmakuTimer.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-27
 */

#ifndef _PCDFM_MODEL_DANMAKUTIMER_HPP
#define _PCDFM_MODEL_DANMAKUTIMER_HPP

#include <cstdint>

namespace PCDanmakuFlameMaster {
namespace model {

    class DanmakuTimer {
    public:
        inline time_t update(time_t curr) {
            mLastInterval = curr - currMillisecond;
            currMillisecond = curr;
            return mLastInterval;
        }

        inline time_t add(time_t mills) {
            return update(currMillisecond + mills);
        }

        inline time_t lastInterval() const {
            return mLastInterval;
        }
    public:
        time_t currMillisecond = 0;
    private:
        time_t mLastInterval = 0;
    };

}
}

#endif // _PCDFM_MODEL_DANMAKUTIMER_HPP
