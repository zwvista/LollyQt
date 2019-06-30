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
    p.NAME = j.at("NAME").get<string>();
    p.KIND = j.at("KIND").get<int>();
    p.ENTITYID = j.at("ENTITYID").get<int>();
    p.VALUEID = j.at("VALUEID").get<int>();
    p.LEVEL = j.at("LEVEL").get<int>();
}

void from_json(const nlohmann::json &j, MUSMappings &p)
{
    p.records = j.at("records").get<vector<MUSMapping>>();
}

const string MUSMapping::NAME_USLANGID = "USLANGID";
const string MUSMapping::NAME_USROWSPERPAGEOPTIONS = "USROWSPERPAGEOPTIONS";
const string MUSMapping::NAME_USROWSPERPAGE = "USROWSPERPAGE";
const string MUSMapping::NAME_USLEVELCOLORS = "USLEVELCOLORS";
const string MUSMapping::NAME_USSCANINTERVAL = "USSCANINTERVAL";
const string MUSMapping::NAME_USREVIEWINTERVAL = "USREVIEWINTERVAL";
const string MUSMapping::NAME_USTEXTBOOKID = "USTEXTBOOKID";
const string MUSMapping::NAME_USDICTITEM = "USDICTITEM";
const string MUSMapping::NAME_USDICTNOTEID = "USDICTNOTEID";
const string MUSMapping::NAME_USDICTITEMS = "USDICTITEMS";
const string MUSMapping::NAME_USDICTTRANSLATIONID = "USDICTTRANSLATIONID";
const string MUSMapping::NAME_USMACVOICEID = "USMACVOICEID";
const string MUSMapping::NAME_USIOSVOICEID = "USIOSVOICEID";
const string MUSMapping::NAME_USANDROIDVOICEID = "USANDROIDVOICEID";
const string MUSMapping::NAME_USWEBVOICEID = "USWEBVOICEID";
const string MUSMapping::NAME_USWINDOWSVOICEID = "USWINDOWSVOICEID";
const string MUSMapping::NAME_USUNITFROM = "USUNITFROM";
const string MUSMapping::NAME_USPARTFROM = "USPARTFROM";
const string MUSMapping::NAME_USUNITTO = "USUNITTO";
const string MUSMapping::NAME_USPARTTO = "USPARTTO";

