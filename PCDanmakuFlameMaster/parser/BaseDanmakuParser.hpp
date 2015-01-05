/**
* @file    BaseDanmakuParser.hpp
* @brief   ...
* @author  zheng qian <xqq@0ginr.com>
* @date    2014-11-28
*/

#ifndef _PCDFM_PARSER_BASE_HPP
#define _PCDFM_PARSER_BASE_HPP

#include <memory>
#include "../model/Danmakus.hpp"
#include "../model/IDisplayer.hpp"
#include "../model/DanmakuTimer.hpp"
//#include "IDataSource.hpp"

using PCDanmakuFlameMaster::model::Danmakus;
using PCDanmakuFlameMaster::model::IDisplayer;
using PCDanmakuFlameMaster::model::DanmakuTimer;

namespace PCDanmakuFlameMaster {
namespace parser {

    class BaseDanmakuParser {
    public:
        virtual BaseDanmakuParser& setDisplayer(IDisplayer& disp);
        IDisplayer& getDisplayer() const;
        BaseDanmakuParser& load(void* pDataSource);
        BaseDanmakuParser& setTimer(DanmakuTimer& timer);
        DanmakuTimer getTimer() const;
        Danmakus getDanmakus();
        void release();
    protected:
        float getViewportSizeFactor() const;
        void releaseDataSource();
        virtual Danmakus parse();
    private:
        std::shared_ptr<Danmakus> mDanmakus;
    protected:
        void* mDataSource = nullptr;
        IDisplayer* mDisp = nullptr;
        DanmakuTimer mTimer;
        int mDispWidth = 0;
        int mDispHeight = 0;
        float mDispDensity = 0.0f;
        float mScaledDensity = 0.0f;
    };

}
}

#endif // _PCDFM_PARSER_BASE_HPP
