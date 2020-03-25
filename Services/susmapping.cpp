#include "susmapping.h"

observable<vector<MUSMapping> > SUSMapping::getData()
{
    auto url = L"USMAPPINGS";
    return apis.getObject(url).map([](const MUSMappings& o){
        return o.records;
    });
}
