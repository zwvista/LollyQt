#ifndef MUSMAPPING_H
#define MUSMAPPING_H

#include "mcommon.h"

struct MUSMapping
{
    int ID = 0;
    string_t NAME;
    int KIND = 0;
    int ENTITYID = 0;
    int VALUEID = 0;
    int LEVEL = 0;

    static const string_t NAME_USLANGID;
    static const string_t NAME_USROWSPERPAGEOPTIONS;
    static const string_t NAME_USROWSPERPAGE;
    static const string_t NAME_USLEVELCOLORS;
    static const string_t NAME_USSCANINTERVAL;
    static const string_t NAME_USREVIEWINTERVAL;
    static const string_t NAME_USTEXTBOOKID;
    static const string_t NAME_USDICTITEM ;
    static const string_t NAME_USDICTNOTEID;
    static const string_t NAME_USDICTITEMS;
    static const string_t NAME_USDICTTRANSLATIONID;
    static const string_t NAME_USMACVOICEID;
    static const string_t NAME_USIOSVOICEID;
    static const string_t NAME_USANDROIDVOICEID;
    static const string_t NAME_USWEBVOICEID;
    static const string_t NAME_USWINDOWSVOICEID;
    static const string_t NAME_USUNITFROM;
    static const string_t NAME_USPARTFROM;
    static const string_t NAME_USUNITTO;
    static const string_t NAME_USPARTTO;
};

struct MUSMappings
{
    vector<MUSMapping> records;
};

void to_json(json& j, const MUSMapping& p);
void from_json(const json& j, MUSMapping& p);
void from_json(const json& j, MUSMappings& p);

#endif // MUSMAPPING_H
