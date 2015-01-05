/**
 * @file    IDataSource.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-08
 */

#ifndef _PCDFM_PARSER_IDATASOURCE_HPP
#define _PCDFM_PARSER_IDATASOURCE_HPP

#include "../utilities/Interface.hpp"

namespace PCDanmakuFlameMaster {
namespace parser {

    template <typename T>
    __interface_class
    class IDataSource {
    public:
        virtual T& data();
        virtual void release();
    public:
        const char* const SCHEME_HTTP_TAG = "http";
        const char* const SCHEME_HTPS_TAG = "https";
        const char* const SCHEME_FILE_TAG = "file";
    };

}
}

#endif // _PCDFM_PARSER_IDATASOURCE_HPP