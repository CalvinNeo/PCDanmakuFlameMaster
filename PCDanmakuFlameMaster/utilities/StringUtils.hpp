/**
 * @file    StringUtils.hpp
 * @brief   ...
 * @author  zheng qian <xqq@0ginr.com>
 * @date    2014-12-06
 */

#ifndef _PCDFM_UTILS_STRING_UTILS_HPP
#define _PCDFM_UTILS_STRING_UTILS_HPP

#include <string>
#include <vector>
#include <algorithm>

namespace PCDanmakuFlameMaster {
namespace util {
namespace StringUtils {

    static inline std::vector<std::string> splitString(const char* input, char delimiter) {
        std::vector<std::string> fragments;
        while (auto next = strchr(input, delimiter)) {
            fragments.push_back(std::string(input, next));
            input = next + 1;
        }
        fragments.push_back(std::string(input));
        return fragments;
    }

    static inline std::vector<std::string> splitString(const char* input, const char* delimiterString) {
        std::vector<std::string> fragments;
        // TODO
        return std::vector<std::string>();
    }

    static inline std::string trim(std::string input) {
        input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end());
        return input;
    }

    static inline void trim_in_situ(std::string& input) {
        input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end());
    }

    static inline bool startsWith(std::string& input, const char* what) {
        return (input.find(what) == 0);
    }

    static inline bool startsWith(std::string& input, std::string& what) {
        return (input.find(what) == 0);
    }

    static inline bool endsWith(std::string& input, const char* what) {
        return (input.rfind(what) == input.length() - strlen(what));
    }

    static inline bool endsWith(std::string& input, std::string& what) {
        return (input.rfind(what) == input.length() - what.length());
    }
}
}
}

#endif // _PCDFM_UTILS_STRING_UTILS_HPP
