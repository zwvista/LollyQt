#include <range/v3/all.hpp>
using namespace ranges;
#include "stextbook.h"
#include "Models/mselectitem.h"
#include <boost/format.hpp>
#include <boost/regex.hpp>

observable<vector<MTextbook>> STextbook::getDataByLang(int langid)
{
    auto f = [](const wstring& units) -> vector<wstring> {
        boost::match_results<wstring::const_iterator> mr;
        bool found = boost::regex_search(units, mr, boost::wregex(LR"(UNITS,(\d+))"));
        if (found) {
            int n = stoi(mr[1]);
            vector<int> v = views::iota(1, n + 1) | ranges::to_vector;
            return v | views::transform([](int i){
                return to_wstring(i);
            }) | ranges::to_vector;
        }
        found = boost::regex_search(units, mr, boost::wregex(LR"(PAGES,(\d+),(\d+))"));
        if (found) {
            int n1 = stoi(mr[1]), n2 = stoi(mr[2]);
            int n = n = (n1 + n2 - 1) / n2;
            vector<int> v = views::iota(1, n + 1) | ranges::to_vector;
            return v | views::transform([&](int i){
                return (boost::wformat(L"%1%~%2%") % (i * n2 - n2 + 1) % (i * n2)).str();
            }) | ranges::to_vector;
        }
        found = boost::regex_search(units, mr, boost::wregex(LR"(CUSTOM,(.+))"));
        if (found) {
            vector<wstring> result = mr[1] | views::split(',') | ranges::to_vector;
            return result;
        }
        return {};
    };
    auto url = boost::wformat(L"TEXTBOOKS?filter=LANGID,eq,%1%") % langid;
    return apis.getObject(url.str()).map([&](MTextbooks& o){
        for (auto& o2 : o.records) {
            auto v = f(o2.UNITS);
            auto v2 = v | views::enumerate | ranges::to_vector;
            o2.units = v2 | views::transform([&](const auto& o3){
                return MSelectItem { static_cast<int>(o3.first + 1), o3.second };
            }) | ranges::to_vector;
            vector<wstring> result = o2.PARTS | views::split(',') | ranges::to_vector;
            v2 = result | views::enumerate | ranges::to_vector;
            o2.parts = v2 | views::transform([&](const auto& o3){
                return MSelectItem { static_cast<int>(o3.first + 1), o3.second };
            }) | ranges::to_vector;
        }
        return o.records;
    });
}
