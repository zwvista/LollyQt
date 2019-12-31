#include "commonapi.h"
#include <boost/format.hpp>

string CommonApi::getAccuracy(int CORRECT, int TOTAL)
{
    return TOTAL == 0 ? "N/A"s : (boost::format("%1%%%") %
                        (floor(static_cast<double>(CORRECT) / TOTAL * 1000) / 10)).str();
}
