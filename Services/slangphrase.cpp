#include "slangphrase.h"
#include <boost/format.hpp>
#include "Helpers/uri.h"
#include <boost/range/adaptors.hpp>

observable<vector<MLangPhrase> > SLangPhrase::getDataByLang(int langid)
{
    auto url = boost::format("LANGPHRASES?filter=LANGID,eq,%1%&order=Phrase") % langid;
    return apis.getObject(url.str()).map([&](const MLangPhrases& o){
        return o.records;
    });
}

observable<vector<MLangPhrase> > SLangPhrase::getDataByLangPhrase(int langid, string phrase)
{
    auto url = boost::format("LANGPHRASES?filter=LANGID,eq,%1%&filter=Phrase,eq,%2%") % langid % urlencode(phrase);
    return apis.getObject(url.str()).map([&](const MLangPhrases& o){
        return boost::copy_range<vector<MLangPhrase>>(o.records | boost::adaptors::filtered([&](const MLangPhrase& o){
            return o.PHRASE == phrase;
        }));
    });
}

observable<vector<MLangPhrase> > SLangPhrase::getDataById(int id)
{
    auto url = boost::format("LANGPHRASES?filter=ID,eq,%1%") % id;
    return apis.getObject(url.str()).map([&](const MLangPhrases& o){
        return o.records;
    });
}

observable<string> SLangPhrase::updateObject(int id, string translation)
{
    auto url = boost::format("LANGPHRASES/%1%&") % id;
    auto body = boost::format("TRANSLATION=%1%&") % translation;
    return api.updateObject(url.str(), body.str());
}

observable<string> SLangPhrase::updateObject(const MLangPhrase &item)
{
    auto url = boost::format("LANGPHRASES/%1%&") % item.ID;
    return api.updateObject(url.str(), item);
}

observable<string> SLangPhrase::createObject(const MLangPhrase &item)
{
    return api.createObject("LANGPHRASES", item);
}

observable<string> SLangPhrase::deleteObject(int id)
{
    auto url = boost::format("LANGPHRASES/%1%&") % id;
    return api.deleteObject(url.str());
}
