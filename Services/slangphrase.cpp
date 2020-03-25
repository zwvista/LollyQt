#include <range/v3/all.hpp>
using namespace ranges;
#include "slangphrase.h"
#include <boost/format.hpp>
#include "Helpers/uri.h"

observable<vector<MLangPhrase> > SLangPhrase::getDataByLang(int langid)
{
    auto url = boost::wformat(L"LANGPHRASES?filter=LANGID,eq,%1%&order=Phrase") % langid;
    return apis.getObject(url.str()).map([&](const MLangPhrases& o){
        return o.records;
    });
}

observable<vector<MLangPhrase> > SLangPhrase::getDataByLangPhrase(int langid, wstring phrase)
{
    auto url = boost::wformat(L"LANGPHRASES?filter=LANGID,eq,%1%&filter=Phrase,eq,%2%") % langid % urlencode(phrase);
    return apis.getObject(url.str()).map([&](const MLangPhrases& o){
        return o.records | views::filter([&](const MLangPhrase& o){
            return o.PHRASE == phrase;
        }) | ranges::to_vector;
    });
}

observable<vector<MLangPhrase> > SLangPhrase::getDataById(int id)
{
    auto url = boost::wformat(L"LANGPHRASES?filter=ID,eq,%1%") % id;
    return apis.getObject(url.str()).map([&](const MLangPhrases& o){
        return o.records;
    });
}

observable<wstring> SLangPhrase::updateObject(int id, wstring translation)
{
    auto url = boost::wformat(L"LANGPHRASES/%1%&") % id;
    auto body = boost::wformat(L"TRANSLATION=%1%&") % translation;
    return api.updateObject(url.str(), body.str());
}

observable<wstring> SLangPhrase::updateObject(const MLangPhrase &item)
{
    auto url = boost::wformat(L"LANGPHRASES/%1%&") % item.ID;
    return api.updateObject(url.str(), item);
}

observable<wstring> SLangPhrase::createObject(const MLangPhrase &item)
{
    return api.createObject(L"LANGPHRASES", item);
}

observable<wstring> SLangPhrase::deleteObject(int id)
{
    auto url = boost::wformat(L"LANGPHRASES/%1%&") % id;
    return api.deleteObject(url.str());
}
