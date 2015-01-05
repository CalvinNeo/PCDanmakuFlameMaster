/**
 * @file    BiliDanmakuParser.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-13
 */

#ifndef _PCDFM_PARSER_BILI_HPP
#define _PCDFM_PARSER_BILI_HPP

#include "../model/BaseDanmaku.hpp"
#include "../model/Danmakus.hpp"
#include "BaseDanmakuParser.hpp"

namespace rapidxml { template<class Ch = char> class xml_document; }

namespace PCDanmakuFlameMaster {
namespace parser {


    class BiliDanmakuParser : public BaseDanmakuParser {
    public:
        virtual Danmakus parse() override;
        virtual BaseDanmakuParser& setDisplayer(IDisplayer& disp) override;
    private:
        Danmakus parseXml(rapidxml::xml_document<>& doc);
        void parseCharacters(const char* input, BaseDanmaku& item);
    private:
        int index = 0;
        float mDispScaleX = 1.0f;
        float mDispScaleY = 1.0f;
    };

}
}

#endif // _PCDFM_PARSER_BILI_HPP
