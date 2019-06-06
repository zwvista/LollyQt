#include "stextbook.h"
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/adaptors.hpp>

observable<vector<MTextbook>> STextbook::getDataByLang(int langid)
{
    auto f = [](string units) -> vector<string> {
        boost::match_results<string::const_iterator> mr;
        boost::regex_search(units, mr, boost::regex(R"(UNITS,(\d+))"));
        if (!mr.empty()) {
            int n = boost::lexical_cast<int>(mr[0]);
            vector<int> v(n);
            boost::iota(v, 1) | boost::adaptors::transformed([](int i){
                return boost::lexical_cast<string>(i);
            })
        }
    };
    auto url = boost::format("TEXTBOOKS?filter=LANGID,eq,%1%") % langid;
    return apis.getObject(url.str()).map([](const MTextbooks& o){
        return o.records;
    });
}
