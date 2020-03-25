#include <range/v3/all.hpp>
using namespace ranges;
#include "sunitword.h"
#include <boost/format.hpp>

observable<vector<MUnitWord> > SUnitWord::getDataByTextbookUnitPart(const MTextbook &textbook, int unitPartFrom, int unitPartTo)
{
    auto url = boost::wformat(L"VUNITWORDS?filter=TEXTBOOKID,eq,%1%&filter=UNITPART,bt,%2%,%3%&order=UNITPART&order=SEQNUM") % textbook.ID % unitPartFrom % unitPartTo;
    return apis.getObject(url.str()).map([&](MUnitWords& o){
        for (auto& o2 : o.records)
            o2.pTextbook = &textbook;
        return o.records;
    });
}

observable<vector<MUnitWord> > SUnitWord::getDataByLang(int langid, const vector<MTextbook> &textbooks)
{
    auto url = boost::wformat(L"VUNITWORDS?filter=LANGID,eq,%1%&order=TEXTBOOKID&order=UNIT&order=PART&order=SEQNUM") % langid;
    return apis.getObject(url.str()).map([&](MUnitWords& o){
        for (auto& o2 : o.records)
            o2.pTextbook = &*ranges::find_if(textbooks, [&](const MTextbook& o){
                return o.ID == o2.TEXTBOOKID;
            });
        return o.records;
    });
}

observable<vector<MUnitWord> > SUnitWord::getDataByLangWord(int wordid)
{
    auto url = boost::wformat(L"VUNITWORDS?filter=WORDID,eq,%1%&") % wordid;
    return apis.getObject(url.str()).map([](const MUnitWords& o){
        return o.records;
    });
}

observable<wstring> SUnitWord::updateObject(int id, int seqnum)
{
    auto url = boost::wformat(L"UNITWORDS/%1%&") % id;
    auto body = boost::wformat(L"SEQNUM=%1%&") % seqnum;
    return api.updateObject(url.str(), body.str());
}

observable<wstring> SUnitWord::updateObject(const MUnitWord &item)
{
    auto url = boost::wformat(L"UNITWORDS/%1%&") % item.ID;
    return api.updateObject(url.str(), item);
}

observable<wstring> SUnitWord::createObject(const MUnitWord &item)
{
    return api.createObject("UNITWORDS", item);
}

observable<wstring> SUnitWord::deleteObject(int id)
{
    auto url = boost::wformat(L"UNITWORDS/%1%&") % id;
    return api.deleteObject(url.str());
}
