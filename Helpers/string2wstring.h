#ifndef STRING2WSTRING_H
#define STRING2WSTRING_H

#include <locale>
#include <codecvt>
#include <string>

std::wstring string2wstring(const std::string &narrow_utf8_source_string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(narrow_utf8_source_string);
    return wide;
}

std::string wstring2string(const std::wstring &wide_utf16_source_string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string narrow = converter.to_bytes(wide_utf16_source_string);
    return narrow;
}

#endif // STRING2WSTRING_H
