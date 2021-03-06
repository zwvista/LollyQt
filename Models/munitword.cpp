#include "munitword.h"

void to_json(json& j, const MUnitWord& p) {
    j = json{
        {"ID", p.ID},
        {"LANGID", p.LANGID},
        {"TEXTBOOKID", p.TEXTBOOKID},
        {"TEXTBOOKNAME", p.TEXTBOOKNAME},
        {"UNIT", p.UNIT},
        {"PART", p.PART},
        {"SEQNUM", p.SEQNUM},
        {"WORDID", p.WORDID},
        {"WORD", p.WORD},
        {"NOTE", p.NOTE},
        {"FAMIID", p.FAMIID},
        {"CORRECT", p.CORRECT},
        {"TOTAL", p.TOTAL},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MUnitWord& p) {
    p.ID = j.at("ID").get<int>();
    p.LANGID = j.at("LANGID").get<int>();
    p.TEXTBOOKID = j.at("TEXTBOOKID").get<int>();
    p.TEXTBOOKNAME = j.at("TEXTBOOKNAME").get<string_t>();
    p.UNIT = j.at("UNIT").get<int>();
    p.PART = j.at("PART").get<int>();
    p.SEQNUM = j.at("SEQNUM").get<int>();
    p.WORDID = j.at("WORDID").get<int>();
    p.WORD = j.at("WORD").get<string_t>();
    p.NOTE = j.at("NOTE").get<string_t>();
    p.FAMIID = j.at("FAMIID").get<int>();
    p.CORRECT = j.at("CORRECT").get<int>();
    p.TOTAL = j.at("TOTAL").get<int>();
}

void from_json(const json& j, MUnitWords& p) {
    p.records = j.at("records").get<vector<MUnitWord>>();
}
