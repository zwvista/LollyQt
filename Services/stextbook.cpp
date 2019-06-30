#include <range/v3/all.hpp>
using namespace ranges;
#include "stextbook.h"
#include "Models/mselectitem.h"
#include <boost/format.hpp>
#include <boost/regex.hpp>

observable<vector<MTextbook>> STextbook::getDataByLang(int langid)
{
    auto f = [](const string& units) -> vector<string> {
        boost::match_results<string::const_iterator> mr;
        bool found = boost::regex_search(units, mr, boost::regex(R"(UNITS,(\d+))"));
        if (found) {
            int n = stoi(mr[1]);
            vector<int> v = view::iota(1, n + 1);
            return v | view::transform([](int i){
                return to_string(i);
            });
        }
        found = boost::regex_search(units, mr, boost::regex(R"(PAGES,(\d+),(\d+))"));
        if (found) {
            int n1 = stoi(mr[1]), n2 = stoi(mr[2]);
            int n = n = (n1 + n2 - 1) / n2;
            vector<int> v = view::iota(1, n + 1);
            return v | view::transform([&](int i){
                return (boost::format("%1%~%2%") % (i * n2 - n2 + 1) % (i * n2)).str();
            });
        }
        found = boost::regex_search(units, mr, boost::regex(R"(CUSTOM,(.+))"));
        if (found) {
            vector<string> result = mr[1] | view::split(',');
            return result;
        }
        return {};
    };
    auto url = boost::format("TEXTBOOKS?filter=LANGID,eq,%1%") % langid;
    return apis.getObject(url.str()).map([&](MTextbooks& o){
        for (auto& o2 : o.records) {
            auto v = f(o2.UNITS);
            auto v2 = v | view::enumerate | ranges::to_vector;
            o2.units = v2 | view::transform([&](const auto& o3){
                return MSelectItem { static_cast<int>(o3.first + 1), o3.second };
            });
            vector<string> result = o2.PARTS | view::split(',');
            v2 = result | view::enumerate;
            o2.parts = v2 | view::transform([&](const auto& o3){
                return MSelectItem { static_cast<int>(o3.first + 1), o3.second };
            });
        }
        return o.records;
    });
}
