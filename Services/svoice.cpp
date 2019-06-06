#include "svoice.h"
#include <boost/format.hpp>

observable<vector<MVoice>> SVoice::getDataByLang(int langid)
{
    auto url = boost::format("VVOICES?filter=LANGID,eq,%1%") % langid;
    return apis.getObject(url.str()).map([](const MVoices& o){
        return o.records;
    });
}
