#include "sunitword.h"
#include <boost/format.hpp>
#include <boost/range/algorithm.hpp>

observable<vector<MUnitWord> > SUnitWord::getDataByTextbookUnitPart(const MTextbook &textbook, int unitPartFrom, int unitPartTo)
{
    auto url = boost::format("VUNITWORDS?filter=TEXTBOOKID,eq,%1%&filter=UNITPART,bt,%2%,%3%&order=UNITPART&order=SEQNUM") % textbook.ID % unitPartFrom % unitPartTo;
    return apis.getObject(url.str()).map([&](MUnitWords& o){
        for (auto& o2 : o.records)
            o2.pTextbook = &textbook;
        return o.records;
    });
}

observable<vector<MUnitWord> > SUnitWord::getDataByLang(int langid, const vector<MTextbook> &textbooks)
{
    auto url = boost::format("VUNITWORDS?filter=LANGID,eq,%1%&order=TEXTBOOKID&order=UNIT&order=PART&order=SEQNUM") % langid;
    return apis.getObject(url.str()).map([&](MUnitWords& o){
        for (auto& o2 : o.records)
            o2.pTextbook = &*boost::find_if(textbooks, [&](const MTextbook& o){
                return o.ID == o2.TEXTBOOKID;
            });
        return o.records;
    });
}

observable<vector<MUnitWord> > SUnitWord::getDataByLangWord(int wordid)
{
    auto url = boost::format("VUNITWORDS?filter=WORDID,eq,%1%&") % wordid;
    return apis.getObject(url.str()).map([](const MUnitWords& o){
        return o.records;
    });
}

observable<string> SUnitWord::updateObject(int id, int seqnum)
{
    auto url = boost::format("UNITWORDS/%1%&") % id;
    auto body = boost::format("SEQNUM=%1%&") % seqnum;
    return api.updateObject(url.str(), body.str());
}

observable<string> SUnitWord::updateObject(const MUnitWord &item)
{
    auto url = boost::format("UNITWORDS/%1%&") % item.ID;
    return api.updateObject(url.str(), item);
}

observable<string> SUnitWord::createObject(const MUnitWord &item)
{
    return api.createObject("UNITWORDS", item);
}

observable<string> SUnitWord::deleteObject(int id)
{
    auto url = boost::format("UNITWORDS/%1%&") % id;
    return api.deleteObject(url.str());
}
