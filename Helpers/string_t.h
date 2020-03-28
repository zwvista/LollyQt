#ifndef STRING_T_H
#define STRING_T_H

#define _TURN_OFF_PLATFORM_STRING
#include <cpprest/details/basic_types.h>
using namespace utility;

#ifdef _UTF16_STRINGS
    #define to_string_t to_wstring
    #define fromStdString_t fromStdWString
    #define format_t wformat
    #define regex_t wregex
#else
    #define to_string_t to_string
    #define fromStdString_t fromStdString
    #define format_t format
    #define regex_t regex
#endif

#endif // STRING_T_H
