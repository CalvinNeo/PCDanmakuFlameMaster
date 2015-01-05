/**
 * @file    RapixXmlDataSource.cpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-08
 */

#include "../3rdparty/rapidxml/rapidxml_utils.hpp"
#include "RapidXmlDataSource.hpp"

using namespace rapidxml;

namespace PCDanmakuFlameMaster {
namespace parser {

    RapidXmlDataSource::RapidXmlDataSource(const char* fileName) : xmlFile(fileName) {
        // do nothing
    }

    file<>& RapidXmlDataSource::data() {
        return xmlFile;
    }

    void RapidXmlDataSource::release() {
        // do nothing
    }

}
}
