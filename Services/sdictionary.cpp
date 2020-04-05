#include "sdictionary.h"
#include <boost/format.hpp>

observable<vector<MDictionary> > SDictionary::getDictsReferenceByLang(int langid)
{
    auto url = boost::format_t(_XPLATSTR("VDICTSREFERENCE?filter=LANGIDFROM,eq,%1%&order=SEQNUM&order=DICTNAME")) % langid;
    return apisReference.getObject(url.str()).map([&](const MDictsReference& o){
        return o.records;
    });
}

observable<vector<MDictionary> > SDictionary::getDictsNoteByLang(int langid)
{
    auto url = boost::format_t(_XPLATSTR("VDICTSNOTE?filter=LANGIDFROM,eq,%1%")) % langid;
    return apisNote.getObject(url.str()).map([&](const MDictsNote& o){
        return o.records;
    });
}

observable<vector<MDictionary> > SDictionary::getDictsTranslationByLang(int langid)
{
    auto url = boost::format_t(_XPLATSTR("VDICTSTRANSLATION?filter=LANGIDFROM,eq,%1%")) % langid;
    return apisTranslation.getObject(url.str()).map([&](const MDictsTranslation& o){
        return o.records;
    });
}

observable<vector<MDictType> > SDictType::getData()
{
    auto url = _XPLATSTR("CODES?filter=KIND,eq,1");
    return apis.getObject(url).map([](const MDictTypes& o){
        return o.records;
    });
}
