#ifndef _PCDFM_DEMO_UTILS_HPP
#define _PCDFM_DEMO_UTILS_HPP

#include <string>
#include <codecvt>
#include <clocale>

namespace xl {

    std::string ansiToUTF8(const char* input) {
        std::setlocale(LC_CTYPE, "");
        size_t wideLength = mbstowcs(nullptr, input, 0);
        wchar_t* wideBuffer = new wchar_t[wideLength + 1];
        mbstowcs(wideBuffer, input, strlen(input));

        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wideToU8Conv;
        std::string u8str = wideToU8Conv.to_bytes(wideBuffer);
        delete [] wideBuffer;
        return u8str;
    }

    std::string wideToUTF8(const wchar_t* input) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.to_bytes(input);
    }

} // namespace xl

#endif // _PCDFM_DEMO_UTILS_HPP
