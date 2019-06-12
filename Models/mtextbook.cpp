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
    p.TEXTBOOKNAME = j.at("NAME").get<string>();
    p.UNITS = j.at("UNITS").get<string>();
    p.PARTS = j.at("PARTS").get<string>();
}

void from_json(const json& j, MTextbooks& p) {
    p.records = j.at("records").get<vector<MTextbook>>();
}
