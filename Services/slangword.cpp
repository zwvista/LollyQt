#include <range/v3/all.hpp>
using namespace ranges;
#include "slangword.h"
#include <boost/format.hpp>
#include "Helpers/uri.h"

observable<vector<MLangWord> > SLangWord::getDataByLang(int langid)
{
    auto url = boost::wformat(L"VLANGWORDS?filter=LANGID,eq,%1%&order=WORD") % langid;
    return apis.getObject(url.str()).map([&](const MLangWords& o){
        return o.records;
    });
}

observable<vector<MLangWord> > SLangWord::getDataByLangWord(int langid, wstring word)
{
    auto url = boost::wformat(L"VLANGWORDS?filter=LANGID,eq,%1%&filter=WORD,eq,%2%") % langid % urlencode(word);
    return apis.getObject(url.str()).map([&](const MLangWords& o){
        return o.records | views::filter([&](const MLangWord& o){
            return o.WORD == word;
        }) | to<vector>;
    });
}

observable<vector<MLangWord> > SLangWord::getDataById(int id)
{
    auto url = boost::wformat(L"VLANGWORDS?filter=ID,eq,%1%") % id;
    return apis.getObject(url.str()).map([&](const MLangWords& o){
        return o.records;
    });
}

observable<wstring> SLangWord::updateObject(int id, wstring note)
{
    auto url = boost::wformat(L"LANGWORDS/%1%&") % id;
    auto body = boost::wformat(L"NOTE=%1%&") % note;
    return api.updateObject(url.str(), body.str());
}

observable<wstring> SLangWord::updateObject(const MLangWord &item)
{
    auto url = boost::wformat(L"LANGWORDS/%1%&") % item.ID;
    return api.updateObject(url.str(), item);
}

observable<wstring> SLangWord::createObject(const MLangWord &item)
{
    return api.createObject(L"LANGWORDS", item);
}

observable<wstring> SLangWord::deleteObject(int id)
{
    auto url = boost::wformat(L"LANGWORDS/%1%&") % id;
    return api.deleteObject(url.str());
}
