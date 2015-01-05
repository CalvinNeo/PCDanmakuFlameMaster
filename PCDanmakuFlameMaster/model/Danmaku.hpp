/**
 * @file    Danmaku.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-05
 */

#ifndef _PCDFM_MODEL_DANMAKU_HPP
#define _PCDFM_MODEL_DANMAKU_HPP

#include <string>
#include "BaseDanmaku.hpp"
#include "IDisplayer.hpp"
#include "Rect.hpp"
#include "../parser/DanmakuFactory.hpp"

namespace PCDanmakuFlameMaster {
namespace model {

    class Danmaku : public BaseDanmaku {
    public:
        Danmaku(const std::string& text) {
            // TODO
        }

        bool isShown() const override {
            return false;
        }

        void layout(IDisplayer& displayer, float x, float y) override {
            // do nothing
        }

        Rect<float> getRectAtTime(IDisplayer& displayer, time_t currTime) const override {
            return Rect<float>();
        }

        float getLeft() const override {
            return 0;
        }

        float getTop() const override {
            return 0;
        }

        float getRight() const override {
            return 0;
        }

        float getBottom() const override {
            return 0;
        }

        DanmakuType getType() const override {
            return static_cast<DanmakuType>(0);
        }
    };

}
}

#endif // _PCDFM_MODEL_DANMAKU_HPP
