#include "svoice.h"
#include <boost/format.hpp>

observable<vector<MVoice>> SVoice::getDataByLang(int langid)
{
    auto url = boost::format_t(_XPLATSTR("VVOICES?filter=LANGID,eq,%1%")) % langid;
    return apis.getObject(url.str()).map([](const MVoices& o){
        return o.records;
    });
}
