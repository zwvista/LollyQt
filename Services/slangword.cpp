#include <range/v3/all.hpp>
using namespace ranges;
#include "slangword.h"
#include <boost/format.hpp>
#include "Helpers/uri.h"

observable<vector<MLangWord> > SLangWord::getDataByLang(int langid)
{
    auto url = boost::format_t(_XPLATSTR("VLANGWORDS?filter=LANGID,eq,%1%&order=WORD")) % langid;
    return apis.getObject(url.str()).map([&](const MLangWords& o){
        return o.records;
    });
}

observable<vector<MLangWord> > SLangWord::getDataByLangWord(int langid, string_t word)
{
    auto url = boost::format_t(_XPLATSTR("VLANGWORDS?filter=LANGID,eq,%1%&filter=WORD,eq,%2%")) % langid % urlencode(word);
    return apis.getObject(url.str()).map([&](const MLangWords& o){
        return o.records | views::filter([&](const MLangWord& o){
            return o.WORD == word;
        }) | to<vector>;
    });
}

observable<vector<MLangWord> > SLangWord::getDataById(int id)
{
    auto url = boost::format_t(_XPLATSTR("VLANGWORDS?filter=ID,eq,%1%")) % id;
    return apis.getObject(url.str()).map([&](const MLangWords& o){
        return o.records;
    });
}

observable<string_t> SLangWord::updateObject(int id, string_t note)
{
    auto url = boost::format_t(_XPLATSTR("LANGWORDS/%1%&")) % id;
    auto body = boost::format_t(_XPLATSTR("NOTE=%1%&")) % note;
    return api.updateObject(url.str(), body.str());
}

observable<string_t> SLangWord::updateObject(const MLangWord &item)
{
    auto url = boost::format_t(_XPLATSTR("LANGWORDS/%1%&")) % item.ID;
    return api.updateObject(url.str(), item);
}

observable<string_t> SLangWord::createObject(const MLangWord &item)
{
    return api.createObject(_XPLATSTR("LANGWORDS"), item);
}

observable<string_t> SLangWord::deleteObject(int id)
{
    auto url = boost::format_t(_XPLATSTR("LANGWORDS/%1%&")) % id;
    return api.deleteObject(url.str());
}
