#ifndef URI_H
#define URI_H

#include "Helpers/string_t.h"

// https://stackoverflow.com/questions/3589936/c-urlencode-library-unicode-capable
string_t urlencode(const string_t& url);

#endif // URI_H
