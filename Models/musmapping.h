#ifndef MUSMAPPING_H
#define MUSMAPPING_H

#include "mcommon.h"

struct MUSMapping
{
    int ID = 0;
    string NAME;
    int KIND = 0;
    int ENTITYID = 0;
    int VALUEID = 0;
    int LEVEL = 0;

    static const string NAME_USLANGID;
    static const string NAME_USROWSPERPAGEOPTIONS;
    static const string NAME_USROWSPERPAGE;
    static const string NAME_USLEVELCOLORS;
    static const string NAME_USSCANINTERVAL;
    static const string NAME_USREVIEWINTERVAL;
    static const string NAME_USTEXTBOOKID;
    static const string NAME_USDICTITEM ;
    static const string NAME_USDICTNOTEID;
    static const string NAME_USDICTITEMS;
    static const string NAME_USDICTTRANSLATIONID;
    static const string NAME_USMACVOICEID;
    static const string NAME_USIOSVOICEID;
    static const string NAME_USANDROIDVOICEID;
    static const string NAME_USWEBVOICEID;
    static const string NAME_USWINDOWSVOICEID;
    static const string NAME_USUNITFROM;
    static const string NAME_USPARTFROM;
    static const string NAME_USUNITTO;
    static const string NAME_USPARTTO;
};

struct MUSMappings
{
    vector<MUSMapping> records;
};

void to_json(json& j, const MUSMapping& p);
void from_json(const json& j, MUSMapping& p);
void from_json(const json& j, MUSMappings& p);

#endif // MUSMAPPING_H
