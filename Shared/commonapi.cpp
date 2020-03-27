#include "commonapi.h"
#include <boost/format.hpp>

string_t CommonApi::getAccuracy(int CORRECT, int TOTAL)
{
    return TOTAL == 0 ? _XPLATSTR("N/A"s) : (boost::format_t(_XPLATSTR("%1%%%")) %
                        (floor(static_cast<double>(CORRECT) / TOTAL * 1000) / 10)).str();
}
