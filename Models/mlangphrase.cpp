#include "mlangphrase.h"

void to_json(json& j, const MLangPhrase& p) {
    j = json{
        {"ID", p.ID},
        {"LANGID", p.LANGID},
        {"PHRASE", p.PHRASE},
        {"TRANSLATION", p.TRANSLATION},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MLangPhrase& p) {
    p.ID = j.at("ID").get<int>();
    p.LANGID = j.at("LANGID").get<int>();
    p.PHRASE = j.at("PHRASE").get<string_t>();
    p.TRANSLATION = j.at("TRANSLATION").get<boost::optional<string_t>>();
}

void from_json(const json& j, MLangPhrases& p) {
    p.records = j.at("records").get<vector<MLangPhrase>>();
}
