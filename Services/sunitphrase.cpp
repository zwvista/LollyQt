#include <range/v3/all.hpp>
using namespace ranges;
#include "sunitphrase.h"
#include <boost/format.hpp>

observable<vector<MUnitPhrase> > SUnitPhrase::getDataByTextbookUnitPart(const MTextbook &textbook, int unitPartFrom, int unitPartTo)
{
    auto url = boost::format("VUNITPHRASES?filter=TEXTBOOKID,eq,%1%&filter=UNITPART,bt,%2%,%3%&order=UNITPART&order=SEQNUM") % textbook.ID % unitPartFrom % unitPartTo;
    return apis.getObject(url.str()).map([&](MUnitPhrases& o){
        for (auto& o2 : o.records)
            o2.pTextbook = &textbook;
        return o.records;
    });
}

observable<vector<MUnitPhrase> > SUnitPhrase::getDataByLang(int langid, const vector<MTextbook> &textbooks)
{
    auto url = boost::format("VUNITPHRASES?filter=LANGID,eq,%1%&order=TEXTBOOKID&order=UNIT&order=PART&order=SEQNUM") % langid;
    return apis.getObject(url.str()).map([&](MUnitPhrases& o){
        for (auto& o2 : o.records)
            o2.pTextbook = &*ranges::find_if(textbooks, [&](const MTextbook& o){
                return o.ID == o2.TEXTBOOKID;
            });
        return o.records;
    });
}

observable<vector<MUnitPhrase> > SUnitPhrase::getDataByLangPhrase(int Phraseid)
{
    auto url = boost::format("VUNITPHRASES?filter=PhraseID,eq,%1%&") % Phraseid;
    return apis.getObject(url.str()).map([](const MUnitPhrases& o){
        return o.records;
    });
}

observable<string> SUnitPhrase::updateObject(int id, int seqnum)
{
    auto url = boost::format("UNITPHRASES/%1%&") % id;
    auto body = boost::format("SEQNUM=%1%&") % seqnum;
    return api.updateObject(url.str(), body.str());
}

observable<string> SUnitPhrase::updateObject(const MUnitPhrase &item)
{
    auto url = boost::format("UNITPHRASES/%1%&") % item.ID;
    return api.updateObject(url.str(), item);
}

observable<string> SUnitPhrase::createObject(const MUnitPhrase &item)
{
    return api.createObject("UNITPHRASES", item);
}

observable<string> SUnitPhrase::deleteObject(int id)
{
    auto url = boost::format("UNITPHRASES/%1%&") % id;
    return api.deleteObject(url.str());
}
