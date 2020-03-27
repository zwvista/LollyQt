#include "musersetting.h"

void to_json(json& j, const MUserSetting& p) {
    j = json{
        {"ID", p.ID},
        {"USERID", p.USERID},
        {"KIND", p.KIND},
        {"ENTITYID", p.ENTITYID},
        {"VALUE1", p.VALUE1},
        {"VALUE2", p.VALUE2},
        {"VALUE3", p.VALUE3},
        {"VALUE4", p.VALUE4},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MUserSetting& p) {
    p.ID = j.at("ID").get<int>();
    p.USERID = j.at("USERID").get<int>();
    p.KIND = j.at("KIND").get<int>();
    p.ENTITYID = j.at("ENTITYID").get<int>();
    p.VALUE1 = j.at("VALUE1").get<boost::optional<string_t>>();
    p.VALUE2 = j.at("VALUE2").get<boost::optional<string_t>>();
    p.VALUE3 = j.at("VALUE3").get<boost::optional<string_t>>();
    p.VALUE4 = j.at("VALUE4").get<boost::optional<string_t>>();
}

void from_json(const json& j, MUserSettings& p) {
    p.records = j.at("records").get<vector<MUserSetting>>();
}
