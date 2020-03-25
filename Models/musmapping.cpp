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
    p.NAME = j.at("NAME").get<wstring>();
    p.KIND = j.at("KIND").get<int>();
    p.ENTITYID = j.at("ENTITYID").get<int>();
    p.VALUEID = j.at("VALUEID").get<int>();
    p.LEVEL = j.at("LEVEL").get<int>();
}

void from_json(const nlohmann::json &j, MUSMappings &p)
{
    p.records = j.at("records").get<vector<MUSMapping>>();
}

const wstring MUSMapping::NAME_USLANGID = L"USLANGID";
const wstring MUSMapping::NAME_USROWSPERPAGEOPTIONS = L"USROWSPERPAGEOPTIONS";
const wstring MUSMapping::NAME_USROWSPERPAGE = L"USROWSPERPAGE";
const wstring MUSMapping::NAME_USLEVELCOLORS = L"USLEVELCOLORS";
const wstring MUSMapping::NAME_USSCANINTERVAL = L"USSCANINTERVAL";
const wstring MUSMapping::NAME_USREVIEWINTERVAL = L"USREVIEWINTERVAL";
const wstring MUSMapping::NAME_USTEXTBOOKID = L"USTEXTBOOKID";
const wstring MUSMapping::NAME_USDICTITEM = L"USDICTITEM";
const wstring MUSMapping::NAME_USDICTNOTEID = L"USDICTNOTEID";
const wstring MUSMapping::NAME_USDICTITEMS = L"USDICTITEMS";
const wstring MUSMapping::NAME_USDICTTRANSLATIONID = L"USDICTTRANSLATIONID";
const wstring MUSMapping::NAME_USMACVOICEID = L"USMACVOICEID";
const wstring MUSMapping::NAME_USIOSVOICEID = L"USIOSVOICEID";
const wstring MUSMapping::NAME_USANDROIDVOICEID = L"USANDROIDVOICEID";
const wstring MUSMapping::NAME_USWEBVOICEID = L"USWEBVOICEID";
const wstring MUSMapping::NAME_USWINDOWSVOICEID = L"USWINDOWSVOICEID";
const wstring MUSMapping::NAME_USUNITFROM = L"USUNITFROM";
const wstring MUSMapping::NAME_USPARTFROM = L"USPARTFROM";
const wstring MUSMapping::NAME_USUNITTO = L"USUNITTO";
const wstring MUSMapping::NAME_USPARTTO = L"USPARTTO";

