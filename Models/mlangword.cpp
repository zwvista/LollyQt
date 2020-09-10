#include "mlangword.h"

void to_json(json& j, const MLangWord& p) {
    j = json{
        {"ID", p.ID},
        {"LANGID", p.LANGID},
        {"WORD", p.WORD},
        {"NOTE", p.NOTE},
        {"FAMIID", p.FAMIID},
        {"CORRECT", p.CORRECT},
        {"TOTAL", p.TOTAL},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MLangWord& p) {
    p.ID = j.at("ID").get<int>();
    p.LANGID = j.at("LANGID").get<int>();
    p.WORD = j.at("WORD").get<string_t>();
    p.NOTE = j.at("NOTE").get<boost::optional<string_t>>();
    p.FAMIID = j.at("FAMIID").get<int>();
    p.CORRECT = j.at("CORRECT").get<int>();
    p.TOTAL = j.at("TOTAL").get<int>();
}

void from_json(const json& j, MLangWords& p) {
    p.records = j.at("records").get<vector<MLangWord>>();
}
