#include "mautocorrect.h"

void to_json(json& j, const MAutoCorrect& p) {
    j = json{
        {"ID", p.ID},
        {"LANGID", p.LANGID},
        {"SEQNUM", p.SEQNUM},
        {"INPUT", p.INPUT},
        {"EXTENDED", p.EXTENDED},
        {"BASIC", p.BASIC}
    };
}

void from_json(const json& j, MAutoCorrect& p) {
    p.ID = j.at("ID").get<int>();
    p.LANGID = j.at("LANGID").get<int>();
    p.SEQNUM = j.at("SEQNUM").get<int>();
    p.INPUT = j.at("INPUT").get<string>();
    p.EXTENDED = j.at("EXTENDED").get<string>();
    p.BASIC = j.at("BASIC").get<string>();
}

void from_json(const json& j, MAutoCorrects& p) {
    p.records = j.at("records").get<vector<MAutoCorrect>>();
}
