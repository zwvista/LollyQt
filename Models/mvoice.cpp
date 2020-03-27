#include "mvoice.h"

void to_json(json& j, const MVoice& p) {
    j = json{
        {"ID", p.ID},
        {"LANGID", p.LANGID},
        {"VOICETYPEID", p.VOICETYPEID},
        {"VOICELANG", p.VOICELANG},
        {"VOICENAME", p.VOICENAME},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MVoice& p) {
    p.ID = j.at("ID").get<int>();
    p.LANGID = j.at("LANGID").get<int>();
    p.VOICETYPEID = j.at("VOICETYPEID").get<int>();
    p.VOICELANG = j.at("VOICELANG").get<boost::optional<string_t>>();
    p.VOICENAME = j.at("VOICENAME").get<string_t>();
}

void from_json(const json& j, MVoices& p) {
    p.records = j.at("records").get<vector<MVoice>>();
}
