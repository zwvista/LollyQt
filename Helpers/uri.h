#ifndef URI_H
#define URI_H

#include <string>

// https://stackoverflow.com/questions/3589936/c-urlencode-library-unicode-capable
std::wstring urlencode(const std::wstring& url);

#endif // URI_H
