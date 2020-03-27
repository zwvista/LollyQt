#include <range/v3/all.hpp>
using namespace ranges;
#include "mtextbook.h"

void to_json(json& j, const MTextbook& p) {
    j = json{
        {"ID", p.ID},
        {"LANGID", p.LANGID},
        {"NAME", p.TEXTBOOKNAME},
        {"UNITS", p.UNITS},
        {"PARTS", p.PARTS},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MTextbook& p) {
    p.ID = j.at("ID").get<int>();
    p.LANGID = j.at("LANGID").get<int>();
    p.TEXTBOOKNAME = j.at("NAME").get<string_t>();
    p.UNITS = j.at("UNITS").get<string_t>();
    p.PARTS = j.at("PARTS").get<string_t>();
}

void from_json(const json& j, MTextbooks& p) {
    p.records = j.at("records").get<vector<MTextbook>>();
}

string_t MTextbook::UNITSTR(int unit) const
{
    return ranges::find_if(units, [&](const MSelectItem& o){
        return o.value == unit;
    })->label;
}

string_t MTextbook::PARTSTR(int part) const
{
    return ranges::find_if(parts, [&](const MSelectItem& o){
        return o.value == part;
    })->label;
}
