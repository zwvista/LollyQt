#include "sautocorrect.h"
#include <boost/format.hpp>

observable<vector<MAutoCorrect>> SAutoCorrect::getDataByLang(int langid)
{
    auto url = boost::format("AUTOCORRECT?filter=LANGID,eq,%1%") % langid;
    return apis.getObject(url.str()).map([](const MAutoCorrects& o){
        return o.records;
    });
}
