#include "sunitword.h"
#include <boost/format.hpp>

observable<vector<MUnitWord>> SUnitWord::getDataByTextbookUnitPart(const MTextbook &textbook, int unitPartFrom, int unitPartTo)
{
    auto url = boost::format("VUNITWORDS?filter=TEXTBOOKID,eq,%1%&filter=UNITPART,bt,%2%,%3%&order=UNITPART&order=SEQNUM") % textbook.ID % unitPartFrom % unitPartTo;
    return apis.getObject(url.str()).map([](const MUnitWords& o){
        return o.records;
    });
}
