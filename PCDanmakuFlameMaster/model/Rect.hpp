/**
 * @file    Rect.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-30
 */

#ifndef _PCDFM_MODEL_RECT_HPP
#define _PCDFM_MODEL_RECT_HPP

namespace PCDanmakuFlameMaster {
namespace model {

    template <typename T>
    struct Rect {
    public:
        Rect() = default;

        Rect(T left, T top, T right, T bottom) {
            this->left = left;
            this->top = top;
            this->right = right;
            this->bottom = bottom;
        }
    public:
        T left = 0;
        T top = 0;
        T right = 0;
        T bottom = 0;
    };

}
}

#endif // _PCDFM_MODEL_RECT_HPP
