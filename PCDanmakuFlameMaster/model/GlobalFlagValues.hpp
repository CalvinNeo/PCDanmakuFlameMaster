/**
 * @file    GlobalFlagValues.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-27
 */

#ifndef _PCDFM_GLOBALFLAGVALUES_HPP
#define _PCDFM_GLOBALFLAGVALUES_HPP

namespace PCDanmakuFlameMaster {
namespace model {

    class GlobalFlagValues {
    public:
        inline static void resetAll() {
            VISIBLE_RESET_FLAG = 0;
            MEASURE_RESET_FLAG = 0;
        }

        inline static void updateVisibleFlag() {
            VISIBLE_RESET_FLAG++;
        }

        inline static void updateMeasureFlag() {
            MEASURE_RESET_FLAG++;
        }
    public:
        static int MEASURE_RESET_FLAG;
        static int VISIBLE_RESET_FLAG;
    };

}
}


#endif // _PCDFM_GLOBALFLAGVALUES_HPP
