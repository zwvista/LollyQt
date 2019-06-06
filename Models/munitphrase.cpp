#include "munitphrase.h"

void to_json(json& j, const MUnitPhrase& p) {
    j = json{
        {"ID", p.ID},
        {"LANGID", p.LANGID},
        {"TEXTBOOKID", p.TEXTBOOKID},
        {"TEXTBOOKNAME", p.TEXTBOOKNAME},
        {"UNIT", p.UNIT},
        {"PART", p.PART},
        {"SEQNUM", p.SEQNUM},
        {"PHRASEID", p.PHRASEID},
        {"PHRASE", p.PHRASE},
        {"TRANSLATION", p.TRANSLATION},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MUnitPhrase& p) {
    p.ID = j.at("ID").get<int>();
    p.LANGID = j.at("LANGID").get<int>();
    p.TEXTBOOKID = j.at("TEXTBOOKID").get<int>();
    p.TEXTBOOKNAME = j.at("TEXTBOOKNAME").get<string>();
    p.UNIT = j.at("UNIT").get<int>();
    p.PART = j.at("PART").get<int>();
    p.SEQNUM = j.at("SEQNUM").get<int>();
    p.PHRASEID = j.at("PHRASEID").get<int>();
    p.PHRASE = j.at("PHRASE").get<string>();
    p.TRANSLATION = j.at("TRANSLATION").get<boost::optional<string>>();
}

void from_json(const json& j, MUnitPhrases& p) {
    p.records = j.at("records").get<vector<MUnitPhrase>>();
}
