#ifndef MUSMAPPING_H
#define MUSMAPPING_H

#include "mcommon.h"

struct MUSMapping
{
    int ID = 0;
    wstring NAME;
    int KIND = 0;
    int ENTITYID = 0;
    int VALUEID = 0;
    int LEVEL = 0;

    static const wstring NAME_USLANGID;
    static const wstring NAME_USROWSPERPAGEOPTIONS;
    static const wstring NAME_USROWSPERPAGE;
    static const wstring NAME_USLEVELCOLORS;
    static const wstring NAME_USSCANINTERVAL;
    static const wstring NAME_USREVIEWINTERVAL;
    static const wstring NAME_USTEXTBOOKID;
    static const wstring NAME_USDICTITEM ;
    static const wstring NAME_USDICTNOTEID;
    static const wstring NAME_USDICTITEMS;
    static const wstring NAME_USDICTTRANSLATIONID;
    static const wstring NAME_USMACVOICEID;
    static const wstring NAME_USIOSVOICEID;
    static const wstring NAME_USANDROIDVOICEID;
    static const wstring NAME_USWEBVOICEID;
    static const wstring NAME_USWINDOWSVOICEID;
    static const wstring NAME_USUNITFROM;
    static const wstring NAME_USPARTFROM;
    static const wstring NAME_USUNITTO;
    static const wstring NAME_USPARTTO;
};

struct MUSMappings
{
    vector<MUSMapping> records;
};

void to_json(json& j, const MUSMapping& p);
void from_json(const json& j, MUSMapping& p);
void from_json(const json& j, MUSMappings& p);

#endif // MUSMAPPING_H
