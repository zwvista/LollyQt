#include "musmapping.h"

void to_json(nlohmann::json &j, const MUSMapping &p)
{
    j = json{
        {"ID", p.ID},
        {"NAME", p.NAME},
        {"KIND", p.KIND},
        {"ENTITYID", p.ENTITYID},
        {"VALUEID", p.VALUEID},
        {"LEVEL", p.LEVEL},
    };
    if (p.ID == 0) j["ID"] = nullptr;
}

void from_json(const nlohmann::json &j, MUSMapping &p)
{
    p.ID = j.at("ID").get<int>();
    p.NAME = j.at("NAME").get<string_t>();
    p.KIND = j.at("KIND").get<int>();
    p.ENTITYID = j.at("ENTITYID").get<int>();
    p.VALUEID = j.at("VALUEID").get<int>();
    p.LEVEL = j.at("LEVEL").get<int>();
}

void from_json(const nlohmann::json &j, MUSMappings &p)
{
    p.records = j.at("records").get<vector<MUSMapping>>();
}

const string_t MUSMapping::NAME_USLANGID = _XPLATSTR("USLANGID");
const string_t MUSMapping::NAME_USROWSPERPAGEOPTIONS = _XPLATSTR("USROWSPERPAGEOPTIONS");
const string_t MUSMapping::NAME_USROWSPERPAGE = _XPLATSTR("USROWSPERPAGE");
const string_t MUSMapping::NAME_USLEVELCOLORS = _XPLATSTR("USLEVELCOLORS");
const string_t MUSMapping::NAME_USSCANINTERVAL = _XPLATSTR("USSCANINTERVAL");
const string_t MUSMapping::NAME_USREVIEWINTERVAL = _XPLATSTR("USREVIEWINTERVAL");
const string_t MUSMapping::NAME_USTEXTBOOKID = _XPLATSTR("USTEXTBOOKID");
const string_t MUSMapping::NAME_USDICTREFERENCE = _XPLATSTR("USDICTREFERENCE");
const string_t MUSMapping::NAME_USDICTNOTEID = _XPLATSTR("USDICTNOTEID");
const string_t MUSMapping::NAME_USDICTSREFERENCE = _XPLATSTR("USDICTSREFERENCE");
const string_t MUSMapping::NAME_USDICTTRANSLATIONID = _XPLATSTR("USDICTTRANSLATIONID");
const string_t MUSMapping::NAME_USMACVOICEID = _XPLATSTR("USMACVOICEID");
const string_t MUSMapping::NAME_USIOSVOICEID = _XPLATSTR("USIOSVOICEID");
const string_t MUSMapping::NAME_USANDROIDVOICEID = _XPLATSTR("USANDROIDVOICEID");
const string_t MUSMapping::NAME_USWEBVOICEID = _XPLATSTR("USWEBVOICEID");
const string_t MUSMapping::NAME_USWINDOWSVOICEID = _XPLATSTR("USWINDOWSVOICEID");
const string_t MUSMapping::NAME_USUNITFROM = _XPLATSTR("USUNITFROM");
const string_t MUSMapping::NAME_USPARTFROM = _XPLATSTR("USPARTFROM");
const string_t MUSMapping::NAME_USUNITTO = _XPLATSTR("USUNITTO");
const string_t MUSMapping::NAME_USPARTTO = _XPLATSTR("USPARTTO");

