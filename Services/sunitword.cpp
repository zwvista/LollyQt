#include <range/v3/all.hpp>
using namespace ranges;
#include "sunitword.h"
#include <boost/format.hpp>

observable<vector<MUnitWord> > SUnitWord::getDataByTextbookUnitPart(const MTextbook &textbook, int unitPartFrom, int unitPartTo)
{
    auto url = boost::format_t(_XPLATSTR("VUNITWORDS?filter=TEXTBOOKID,eq,%1%&filter=UNITPART,bt,%2%,%3%&order=UNITPART&order=SEQNUM")) % textbook.ID % unitPartFrom % unitPartTo;
    return apis.getObject(url.str()).map([&](const MUnitWords& o){
        auto oo = o;
        for (auto& o2 : oo.records)
            o2.pTextbook = &textbook;
        return oo.records;
    });
}

observable<vector<MUnitWord> > SUnitWord::getDataByLang(int langid, const vector<MTextbook> &textbooks)
{
    auto url = boost::format_t(_XPLATSTR("VUNITWORDS?filter=LANGID,eq,%1%&order=TEXTBOOKID&order=UNIT&order=PART&order=SEQNUM")) % langid;
    return apis.getObject(url.str()).map([&](const MUnitWords& o){
        auto oo = o;
        for (auto& o2 : oo.records)
            o2.pTextbook = &*ranges::find_if(textbooks, [&](const MTextbook& o3){
                return o3.ID == o2.TEXTBOOKID;
            });
        return oo.records;
    });
}

observable<vector<MUnitWord> > SUnitWord::getDataByLangWord(int wordid)
{
    auto url = boost::format_t(_XPLATSTR("VUNITWORDS?filter=WORDID,eq,%1%&")) % wordid;
    return apis.getObject(url.str()).map([](const MUnitWords& o){
        return o.records;
    });
}

observable<string_t> SUnitWord::updateObject(int id, int seqnum)
{
    auto url = boost::format_t(_XPLATSTR("UNITWORDS/%1%&")) % id;
    auto body = boost::format_t(_XPLATSTR("SEQNUM=%1%&")) % seqnum;
    return api.updateObject(url.str(), body.str());
}

observable<string_t> SUnitWord::updateObject(const MUnitWord &item)
{
    auto url = boost::format_t(_XPLATSTR("UNITWORDS/%1%&")) % item.ID;
    return api.updateObject(url.str(), item);
}

observable<string_t> SUnitWord::createObject(const MUnitWord &item)
{
    return api.createObject(_XPLATSTR("UNITWORDS"), item);
}

observable<string_t> SUnitWord::deleteObject(int id)
{
    auto url = boost::format_t(_XPLATSTR("UNITWORDS/%1%&")) % id;
    return api.deleteObject(url.str());
}
