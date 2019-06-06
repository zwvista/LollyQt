#include "mwordfami.h"

void to_json(json& j, const MWordFami& p) {
    j = json{
        {"ID", p.ID},
        {"USERID", p.USERID},
        {"WORDID", p.WORDID},
        {"LEVEL", p.LEVEL},
        {"CORRECT", p.CORRECT},
        {"TOTAL", p.TOTAL},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MWordFami& p) {
    p.ID = j.at("ID").get<int>();
    p.USERID = j.at("USERID").get<int>();
    p.WORDID = j.at("WORDID").get<int>();
    p.LEVEL = j.at("LEVEL").get<int>();
    p.CORRECT = j.at("CORRECT").get<int>();
    p.TOTAL = j.at("TOTAL").get<int>();
}

void from_json(const json& j, MWordsFami& p) {
    p.records = j.at("records").get<vector<MWordFami>>();
}
