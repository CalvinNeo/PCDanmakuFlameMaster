/**
 * @file    RapixXmlDataSource.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-08
 */

#ifndef _PCDFM_PARSER_RAPID_XML_DATA_SOURCE_HPP
#define _PCDFM_PARSER_RAPID_XML_DATA_SOURCE_HPP

#include "../3rdparty/rapidxml/rapidxml_utils.hpp"
#include "IDataSource.hpp"

namespace PCDanmakuFlameMaster {
namespace parser {

    //template <class Ch = char>
    //class file;

    class RapidXmlDataSource : public IDataSource<rapidxml::file<>> {
    public:
        RapidXmlDataSource(const char* fileName);
        rapidxml::file<>& data() override;
        void release() override;
    private:
        rapidxml::file<> xmlFile;
    };

}
}

#endif // _PCDFM_PARSER_RAPID__XML_DATA_SOURCE_HPP
