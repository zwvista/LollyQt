#ifndef WSTRING2JSON_H
#define WSTRING2JSON_H

#include <boost/optional.hpp>
#include <nlohmann/json.hpp>
#include <locale>
#include <codecvt>
#include <string>

// partial specialization (full specialization works too)
namespace nlohmann {
    // https://github.com/nlohmann/json/issues/1592
    // https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
    template <>
    struct adl_serializer<std::wstring> {
        static void to_json(json& j, const std::wstring& str) {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            j = converter.to_bytes(str);
        }

        static void from_json(const json& j, std::wstring& str) {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            str = converter.from_bytes(j.get<std::string>());
        }
    };
}

#endif // WSTRING2JSON_H
