#include "mlanguage.h"

void to_json(json& j, const MLanguage& p) {
    j = json{
        {"ID", p.ID},
        {"NAME", p.LANGNAME},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MLanguage& p) {
    p.ID = j.at("ID").get<int>();
    p.LANGNAME = j.at("NAME").get<string_t>();
}

void from_json(const json& j, MLanguages& p) {
    p.records = j.at("records").get<vector<MLanguage>>();
}
