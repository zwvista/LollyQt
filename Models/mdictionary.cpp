#include <range/v3/all.hpp>
using namespace ranges;
#include "mdictionary.h"

void to_json(json& j, const MDictionary& p) {
    j = json{
        {"ID", p.ID},
        {"DICTID", p.DICTID},
        {"LANGIDFROM", p.LANGIDFROM},
        {"LANGNAMEFROM", p.LANGNAMEFROM},
        {"LANGIDTO", p.LANGIDTO},
        {"LANGNAMETO", p.LANGNAMETO},
        {"SEQNUM", p.SEQNUM},
        {"DICTTYPEID", p.DICTTYPEID},
        {"DICTTYPENAME", p.DICTTYPENAME},
        {"DICTNAME", p.DICTNAME},
        {"URL", p.URL},
        {"CHCONV", p.CHCONV},
        {"AUTOMATION", p.AUTOMATION},
        {"DICTTABLE", p.DICTTABLE},
        {"TRANSFORM", p.TRANSFORM},
        {"WAIT", p.WAIT},
        {"TEMPLATE", p.TEMPLATE},
        {"TEMPLATE2", p.TEMPLATE2},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const json& j, MDictionary& p) {
    p.ID = j.at("ID").get<int>();
    p.DICTID = j.at("DICTID").get<int>();
    p.LANGIDFROM = j.at("LANGIDFROM").get<int>();
    p.LANGNAMEFROM = j.at("LANGNAMEFROM").get<string_t>();
    p.LANGIDTO = j.at("LANGIDTO").get<int>();
    p.LANGNAMETO = j.at("LANGNAMETO").get<string_t>();
    p.SEQNUM = j.at("SEQNUM").get<int>();
    p.DICTTYPEID = j.at("DICTTYPEID").get<int>();
    p.DICTTYPENAME = j.at("DICTTYPENAME").get<string_t>();
    p.DICTNAME = j.at("DICTNAME").get<string_t>();
    p.URL = j.at("URL").get<boost::optional<string_t>>();
    p.CHCONV = j.at("CHCONV").get<boost::optional<string_t>>();
    p.AUTOMATION = j.at("AUTOMATION").get<boost::optional<string_t>>();
    p.DICTTABLE = j.at("DICTTABLE").get<boost::optional<string_t>>();
    p.TRANSFORM = j.at("TRANSFORM").get<boost::optional<string_t>>();
    p.WAIT = j.at("WAIT").get<int>();
    p.TEMPLATE = j.at("TEMPLATE").get<boost::optional<string_t>>();
    p.TEMPLATE2 = j.at("TEMPLATE2").get<boost::optional<string_t>>();
}

void from_json(const json& j, MDictsReference& p) {
    p.records = j.at("records").get<vector<MDictionary>>();
}

void from_json(const json& j, MDictsNote& p) {
    p.records = j.at("records").get<vector<MDictionary>>();
}

void from_json(const json& j, MDictsTranslation& p) {
    p.records = j.at("records").get<vector<MDictionary>>();
}

void from_json(const nlohmann::json &j, MDictType &p)
{
    p.CODE = j.at("CODE").get<int>();
    p.NAME = j.at("NAME").get<string_t>();
}

void from_json(const nlohmann::json &j, MDictTypes &p)
{
    p.records = j.at("records").get<vector<MDictType>>();
}
