#include <range/v3/all.hpp>
using namespace ranges;
#include "slangphrase.h"
#include <boost/format.hpp>
#include "Helpers/uri.h"

observable<vector<MLangPhrase> > SLangPhrase::getDataByLang(int langid)
{
    auto url = boost::format_t(_XPLATSTR("LANGPHRASES?filter=LANGID,eq,%1%&order=Phrase")) % langid;
    return apis.getObject(url.str()).map([&](const MLangPhrases& o){
        return o.records;
    });
}

observable<vector<MLangPhrase> > SLangPhrase::getDataByLangPhrase(int langid, string_t phrase)
{
    auto url = boost::format_t(_XPLATSTR("LANGPHRASES?filter=LANGID,eq,%1%&filter=Phrase,eq,%2%")) % langid % urlencode(phrase);
    return apis.getObject(url.str()).map([&](const MLangPhrases& o){
        return o.records | views::filter([&](const MLangPhrase& o){
            return o.PHRASE == phrase;
        }) | to<vector>;
    });
}

observable<vector<MLangPhrase> > SLangPhrase::getDataById(int id)
{
    auto url = boost::format_t(_XPLATSTR("LANGPHRASES?filter=ID,eq,%1%")) % id;
    return apis.getObject(url.str()).map([&](const MLangPhrases& o){
        return o.records;
    });
}

observable<string_t> SLangPhrase::updateObject(int id, string_t translation)
{
    auto url = boost::format_t(_XPLATSTR("LANGPHRASES/%1%&")) % id;
    auto body = boost::format_t(_XPLATSTR("TRANSLATION=%1%&")) % translation;
    return api.updateObject(url.str(), body.str());
}

observable<string_t> SLangPhrase::updateObject(const MLangPhrase &item)
{
    auto url = boost::format_t(_XPLATSTR("LANGPHRASES/%1%&")) % item.ID;
    return api.updateObject(url.str(), item);
}

observable<string_t> SLangPhrase::createObject(const MLangPhrase &item)
{
    return api.createObject(_XPLATSTR("LANGPHRASES"), item);
}

observable<string_t> SLangPhrase::deleteObject(int id)
{
    auto url = boost::format_t(_XPLATSTR("LANGPHRASES/%1%&")) % id;
    return api.deleteObject(url.str());
}
