#ifndef STRING_T_H
#define STRING_T_H

#define _TURN_OFF_PLATFORM_STRING
#include <cpprest/details/basic_types.h>
using namespace utility;

#ifdef _UTF16_STRINGS
    #define to_string_t to_wstring
    #define fromStdString_t fromStdWString
    #define format_t wformat
#else
    #define to_string_t to_string
    #define format_t format
#endif

#endif // STRING_T_H
