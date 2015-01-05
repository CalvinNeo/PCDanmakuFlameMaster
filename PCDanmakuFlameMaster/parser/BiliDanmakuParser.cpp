/**
 * @file    BiliDanmakuParser.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-11-13
 */

#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include "../3rdparty/rapidxml/rapidxml.hpp"
#include "../3rdparty/rapidxml/rapidxml_utils.hpp"
#include "../utilities/StringUtils.hpp"
#include "DanmakuFactory.hpp"
#include "RapidXmlDataSource.hpp"
#include "BaseDanmakuParser.hpp"
#include "BiliDanmakuParser.hpp"

using namespace rapidxml;
using namespace PCDanmakuFlameMaster::util::StringUtils;

namespace PCDanmakuFlameMaster {
namespace parser {

    Danmakus BiliDanmakuParser::parse() {
        if (mDataSource == nullptr) {
            RapidXmlDataSource dataSource = *static_cast<RapidXmlDataSource*>(mDataSource);
            xml_document<> doc;
            doc.parse<0>(dataSource.data().data());
            return parseXml(doc);
        } else {
            throw std::exception("mDataSource is NullPointer");
        }
    }

    Danmakus BiliDanmakuParser::parseXml(rapidxml::xml_document<>& doc) {
        Danmakus result;
        
        xml_node<char>* root = doc.first_node("i");

        for (auto node = root->first_node("d"); node != nullptr; node = node->next_sibling()) {
            const char* attribute = node->first_attribute("p")->value();
            auto attributes = splitString(attribute, ',');

            if (attributes.size() > 0) {
                time_t time = std::stoll(attributes[0]);
                DanmakuType type = static_cast<DanmakuType>(std::stoi(attributes[1]));
                float textSize = std::stof(attributes[2]);
                int color = std::stoi(attributes[3]) | 0xFF000000;
                
                auto item = DanmakuFactory::createDanmaku(type, *mDisp);
                item.time = time;
                item.textSize = textSize * (mDispDensity - 0.6f);
                item.textColor = color;
                item.textShadowColor = (color <= 0xFF000000) ? 0xFFFFFFFF : 0xFF000000;
                parseCharacters(node->value(), item);
                result.addItem(item);
            }
        }

        return result;
    }

    void BiliDanmakuParser::parseCharacters(const char* input, BaseDanmaku& item) {
        DanmakuFactory::fillText(item, std::string(input));
        item.index = index++;

        if (item.getType() == DanmakuType::DanmakuType_Special) {
            std::string text = trim(item.text);
            if (text[0] == '[' && text[text.length() - 1] == ']') {
                // initial special danmaku data

            }
        }
    }

    BaseDanmakuParser& BiliDanmakuParser::setDisplayer(IDisplayer& disp) {
        this->BaseDanmakuParser::setDisplayer(disp);
        mDispScaleX = static_cast<float>(mDispWidth / DanmakuFactory::BILI_PLAYER_WIDTH);
        mDispScaleY = static_cast<float>(mDispHeight / DanmakuFactory::BILI_PLAYER_HEIGHT);
        return *this;
    }

}
}
