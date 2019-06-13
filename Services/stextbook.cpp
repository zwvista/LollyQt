#include "stextbook.h"
#include "Models/mselectitem.h"
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/algorithm/string.hpp>

observable<vector<MTextbook>> STextbook::getDataByLang(int langid)
{
    auto f = [](const string& units) -> vector<string> {
        boost::match_results<string::const_iterator> mr;
        boost::regex_search(units, mr, boost::regex(R"(UNITS,(\d+))"));
        if (!mr.empty()) {
            int n = stoi(mr[1]);
            return boost::copy_range<vector<string>>(boost::irange(1, n + 1) | boost::adaptors::transformed([](int i){
                return to_string(i);
            }));
        }
        boost::regex_search(units, mr, boost::regex(R"(PAGES,(\d+),(\d+))"));
        if (!mr.empty()) {
            int n1 = stoi(mr[1]), n2 = stoi(mr[2]);
            int n = n = (n1 + n2 - 1) / n2;
            return boost::copy_range<vector<string>>(boost::irange(1, n + 1) | boost::adaptors::transformed([&](int i){
                return (boost::format("%1%~%2%") % (i * n2 - n2 + 1) % (i * n2)).str();
            }));
        }
        boost::regex_search(units, mr, boost::regex(R"(CUSTOM,(.+))"));
        if (!mr.empty()) {
            vector<string> result;
            boost::algorithm::split(result, mr[1], boost::is_any_of(","));
            return result;
        }
        return {};
    };
    auto url = boost::format("TEXTBOOKS?filter=LANGID,eq,%1%") % langid;
    return apis.getObject(url.str()).map([&](MTextbooks& o){
        for (auto& o2 : o.records) {
            o2.units = boost::copy_range<vector<MSelectItem>>(f(o2.UNITS) | boost::adaptors::indexed(1) | boost::adaptors::transformed([&](const auto& o3){
                return MSelectItem { static_cast<int>(o3.index()), o3.value() };
            }));
            vector<string> result;
            boost::algorithm::split(result, o2.PARTS, boost::is_any_of(","));
            o2.parts = boost::copy_range<vector<MSelectItem>>(result | boost::adaptors::indexed(1) | boost::adaptors::transformed([&](const auto& o3){
                return MSelectItem { static_cast<int>(o3.index()), o3.value() };
            }));
        }
        return o.records;
    });
}
