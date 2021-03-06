#include "slanguage.h"

observable<vector<MLanguage> > SLanguage::getData()
{
    auto url = _XPLATSTR("LANGUAGES?filter=ID,neq,0");
    return apis.getObject(url).map([](const MLanguages& o){
        return o.records;
    });
}
