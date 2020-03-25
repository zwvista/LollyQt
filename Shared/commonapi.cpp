#include "commonapi.h"
#include <boost/format.hpp>

wstring CommonApi::getAccuracy(int CORRECT, int TOTAL)
{
    return TOTAL == 0 ? L"N/A"s : (boost::wformat(L"%1%%%") %
                        (floor(static_cast<double>(CORRECT) / TOTAL * 1000) / 10)).str();
}
