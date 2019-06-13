#include "vmsettings.h"
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/range/algorithm_ext.hpp>
#include "Helpers/flattened.h"

vector<int> VMSettings::getUSROWSPERPAGEOPTIONS() const
{
    vector<string> result;
    boost::algorithm::split(result, selectedUSUser0->VALUE2.get(), boost::is_any_of(","));
    return boost::copy_range<vector<int>>(result | boost::adaptors::transformed([](const string& s){
        return stoi(s);
    }));
}

observable<string> VMSettings::getData()
{
    return slanguage.getData().zip(susersetting.getData(1), sdicttype.getData()).flat_map([&](const auto& o){
        languages = get<0>(o);
        userSettings = get<1>(o);
        dictTypes = get<2>(o);
        selectedUSUser0 = &*boost::find_if(userSettings, [](const MUserSetting& o){
            return o.KIND == 1 && o.ENTITYID == 0;
        });
        selectedUSUser1 = &*boost::find_if(userSettings, [](const MUserSetting& o){
            return o.KIND == 1 && o.ENTITYID == 1;
        });
        vector<string> lines, colors;
        boost::algorithm::split_regex(lines, selectedUSUser0->VALUE4.get(), boost::regex("\r\n"));
        for(const string& s : lines) {
            boost::algorithm::split(colors, s, boost::is_any_of(","));
            USLEVELCOLORS[stoi(colors[0])] = {colors[1], colors[2]};
        }
        int langIndex = boost::find_if(languages, [&](const MLanguage& o){
            return o.ID == getUSLANGID();
        }) - languages.begin();
        return setSelectedLang(langIndex);
    });
}

observable<string> VMSettings::setSelectedLang(int langIndex)
{
    selectedLangIndex = langIndex;
    int langid = getSelectedLang().ID;
    setUSLANGID(langid);
    selectedUSLang2 = &*boost::find_if(userSettings, [&](const MUserSetting& o){
        return o.KIND == 2 && o.ENTITYID == langid;
    });
    selectedUSLang3 = &*boost::find_if(userSettings, [&](const MUserSetting& o){
        return o.KIND == 3 && o.ENTITYID == langid;
    });
    vector<string> dicts;
    boost::algorithm::split_regex(dicts, getUSDICTITEMS(), boost::regex("\r\n"));
    return sdictreference.getDataByLang(langid).zip(
                sdictnote.getDataByLang(langid),
                sdicttranslation.getDataByLang(langid),
                stextbook.getDataByLang(langid),
                sautocorrect.getDataByLang(langid),
                svoice.getDataByLang(langid)).map([&, dicts](const auto& o){
        dictsReference = get<0>(o);
        dictItems.clear();
        int i = 0;
        for (const string& d : dicts) {
            if (d == "0")
                for (const auto& o2 :dictsReference)
                    dictItems.push_back({ to_string(o2.DICTID), o2.DICTNAME });
            else
                dictItems.push_back({ d, (boost::format("Custom%1%") % ++i).str() });
        }
//        boost::copy(dicts | boost::adaptors::transformed([&](const string& d){
//            return d == "0" ? boost::copy_range<vector<MDictItem>>(dictsReference | boost::adaptors::transformed([&](const auto& o2){
//                return MDictItem { to_string(o2.DICTID), o2.DICTNAME };
//            })) : vector<MDictItem>{};
//        }) | flattened, back_inserter(dictItems));
        int index = boost::find_if(dictItems, [&](const MDictItem& o){
            return o.DICTID == getUSDICTITEM();
        }) - dictItems.begin();
        setSelectedDictItem(index);
        dictsNote = get<1>(o);
        index = boost::find_if(dictsNote, [&](const MDictNote& o){
            return o.DICTID == getUSDICTNOTEID();
        }) - dictsNote.begin();
        setSelectedDictNote(index);
        if (dictsNote.empty()) dictsNote.emplace_back();
        dictsTranslation = get<2>(o);
        index = boost::find_if(dictsTranslation, [&](const MDictTranslation& o){
            return o.DICTID == getUSDICTTRANSLATIONID();
        }) - dictsTranslation.begin();
        setSelectedDictTranslation(index);
        if (dictsTranslation.empty()) dictsTranslation.emplace_back();
        textbooks = get<3>(o);
        index = boost::find_if(textbooks, [&](const MTextbook& o){
            return o.ID == getUSTEXTBOOKID();
        }) - textbooks.begin();
        setSelectedTextbook(index);
        autoCorrects = get<4>(o);
        macVoices = boost::copy_range<vector<MVoice>>(get<5>(o) | boost::adaptors::filtered([](const MVoice& o) {
            return o.VOICETYPEID == 2;
        }));
        index = boost::find_if(macVoices, [&](const MVoice& o){
            return o.ID == getUSMACVOICEID();
        }) - macVoices.begin();
        setSelectedMacVoice(index);
        return string{};
    });
}

void VMSettings::setSelectedMacVoice(int index)
{
   selectedMacVoiceIndex = index;
   setUSMACVOICEID(getSelectedMacVoice().ID);
}

void VMSettings::setSelectedDictItem(int index)
{
   selectedDictItemIndex = index;
   setUSDICTITEM(getSelectedDictItem().DICTID);
}

void VMSettings::setSelectedDictNote(int index)
{
   selectedDictNoteIndex = index;
   setUSDICTNOTEID(getSelectedDictNote().DICTID);
}

void VMSettings::setSelectedDictTranslation(int index)
{
    selectedDictTranslationIndex = index;
    setUSDICTTRANSLATIONID(getSelectedDictTranslation().DICTID);
}

void VMSettings::setSelectedTextbook(int index)
{
    selectedTextbookIndex = index;
    int textbookid = getSelectedTextbook().ID;
    setUSTEXTBOOKID(textbookid);
    selectedUSTextbook = &*boost::find_if(userSettings, [&](const MUserSetting& o){
        return o.KIND == 11 && o.ENTITYID == textbookid;
    });
}
