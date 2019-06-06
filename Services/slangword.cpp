#include "slangword.h"
#include <boost/format.hpp>
#include "Helpers/uri.h"

observable<vector<MLangWord> > SLangWord::getDataByLang(int langid)
{
    auto url = boost::format("VLANGWORDS?filter=LANGID,eq,%1%&order=WORD") % langid;
    return apis.getObject(url.str()).map([&](MLangWords& o){
        return o.records;
    });
}

observable<vector<MLangWord> > SLangWord::getDataByLangWord(int langid, string word)
{
    auto url = boost::format("VLANGWORDS?filter=LANGID,eq,%1%&filter=WORD,eq,%2%") % langid % urlencode(word);
    return apis.getObject(url.str()).map([&](MLangWords& o){
        return o.records;
    }).filter([&](MLangWord& o){
        return o.WORD == word;
    });
}

observable<vector<MLangWord> > SLangWord::getDataById(int id)
{
    auto url = boost::format("VLANGWORDS?filter=ID,eq,%1%") % id;
    return apis.getObject(url.str()).map([&](MLangWords& o){
        return o.records;
    });
}

observable<string> SLangWord::updateObject(int id, string note)
{
    auto url = boost::format("LANGWORDS/%1%&") % id;
    auto body = boost::format("NOTE=%1%&") % note;
    return api.updateObject(url.str(), body.str());
}

observable<string> SLangWord::updateObject(const MLangWord &item)
{
    auto url = boost::format("LANGWORDS/%1%&") % item.ID;
    return api.updateObject(url.str(), item);
}

observable<string> SLangWord::createObject(const MLangWord &item)
{
    return api.createObject("LANGWORDS", item);
}

observable<string> SLangWord::deleteObject(int id)
{
    auto url = boost::format("LANGWORDS/%1%&") % id;
    return api.deleteObject(url.str());
}
