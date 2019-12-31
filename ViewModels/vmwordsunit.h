#ifndef VMWORDSUNIT_H
#define VMWORDSUNIT_H

#include "vmsettings.h"
#include "Helpers/restapi.h"
#include "Services/sunitword.h"

class VMWordsUnit
{
    VMSettings vmSettings;
    bool inTextbook;

    SUnitWord sunitword;
public:
    VMWordsUnit(const VMSettings& vmSettings, bool inTextbook);
    observable<int> reload();

    vector<MUnitWord> unitwords;
};

#endif // VMWORDSUNIT_H
