#include <range/v3/all.hpp>
using namespace ranges;
#include "mautocorrect.h"
#include <boost/algorithm/string/replace.hpp>

void to_json(json& j, const MAutoCorrect& p) {
    j = json{
        {"ID", p.ID},
        {"LANGID", p.LANGID},
        {"SEQNUM", p.SEQNUM},
        {"INPUT", p.INPUT},
        {"EXTENDED", p.EXTENDED},
        {"BASIC", p.BASIC}
    };
    if (p.ID == 0) j["ID"] = nullptr;
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

string autoCorrect(const string& text, const vector<MAutoCorrect> &autoCorrects, function<string (const MAutoCorrect &)> f1, function<string (const MAutoCorrect &)> f2)
{
    return ranges::accumulate(autoCorrects, text, [&](const string& str, const MAutoCorrect& row){
       return boost::replace_all_copy<string>(str, f1(row), f2(row));
    });
}
