#include "vmsettings.h"
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/algorithm/string.hpp>

vector<int> VMSettings::getUSROWSPERPAGEOPTIONS() const
{
    vector<string> result;
    boost::algorithm::split(result, selectedUSUser0->VALUE2.get(), boost::is_any_of(","));
    return boost::copy_range<vector<int>>(result | boost::adaptors::transformed([](const string& s){
        return stoi(s);
    }));
}
