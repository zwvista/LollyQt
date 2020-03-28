#include <range/v3/all.hpp>
using namespace ranges;
#include "stextbook.h"
#include "Models/mselectitem.h"
#include <boost/format.hpp>
#include <boost/regex.hpp>

observable<vector<MTextbook>> STextbook::getDataByLang(int langid)
{
    auto f = [](const string_t& units) -> vector<string_t> {
        boost::match_results<string_t::const_iterator> mr;
        bool found = boost::regex_search(units, mr, boost::regex_t(_XPLATSTR(R"(UNITS,(\d+))")));
        if (found) {
            int n = stoi(mr[1]);
            vector<int> v = views::iota(1, n + 1) | to<vector>;
            return v | views::transform([](int i){
                return to_string_t(i);
            }) | to<vector>;
        }
        found = boost::regex_search(units, mr, boost::regex_t(_XPLATSTR(R"(PAGES,(\d+),(\d+))")));
        if (found) {
            int n1 = stoi(mr[1]), n2 = stoi(mr[2]);
            int n = n = (n1 + n2 - 1) / n2;
            vector<int> v = views::iota(1, n + 1) | to<vector>;
            return v | views::transform([&](int i){
                return (boost::format_t(_XPLATSTR("%1%~%2%")) % (i * n2 - n2 + 1) % (i * n2)).str();
            }) | to<vector>;
        }
        found = boost::regex_search(units, mr, boost::regex_t(_XPLATSTR(R"(CUSTOM,(.+))")));
        if (found) {
            vector<string_t> result = mr[1] | views::split(',') | to<vector<string_t>>;
            return result;
        }
        return {};
    };
    auto url = boost::format_t(_XPLATSTR("TEXTBOOKS?filter=LANGID,eq,%1%")) % langid;
    return apis.getObject(url.str()).map([&](MTextbooks& o){
        for (auto& o2 : o.records) {
            auto v = f(o2.UNITS);
            auto v2 = v | views::enumerate | to<vector>;
            o2.units = v2 | views::transform([&](const auto& o3){
                return MSelectItem { static_cast<int>(o3.first + 1), o3.second };
            }) | to<vector>;
            vector<string_t> result = o2.PARTS | views::split(',') | to<vector<string_t>>;
            v2 = result | views::enumerate | to<vector>;
            o2.parts = v2 | views::transform([&](const auto& o3){
                return MSelectItem { static_cast<int>(o3.first + 1), o3.second };
            }) | to<vector>;
        }
        return o.records;
    });
}
