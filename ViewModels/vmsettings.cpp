#include <range/v3/all.hpp>
using namespace ranges;
#include "vmsettings.h"

vector<int> VMSettings::getUSROWSPERPAGEOPTIONS() const
{
    vector<string> result = selectedUSUser0->VALUE2.get() | view::split(',');
    return result | view::transform([](const string& s){
        return stoi(s);
    }) | ranges::to_vector;
}

observable<string> VMSettings::getData()
{
    return slanguage.getData().zip(susersetting.getData(1), sdicttype.getData()).flat_map([&](const auto& o){
        languages = get<0>(o);
        userSettings = get<1>(o);
        dictTypes = get<2>(o);
        selectedUSUser0 = &*ranges::find_if(userSettings, [](const MUserSetting& o){
            return o.KIND == 1 && o.ENTITYID == 0;
        });
        selectedUSUser1 = &*ranges::find_if(userSettings, [](const MUserSetting& o){
            return o.KIND == 1 && o.ENTITYID == 1;
        });
        vector<string> lines = selectedUSUser0->VALUE4.get() | view::split("\r\n"s);
        for(const string& s : lines) {
            vector<string> colors = s | view::split(',');
            USLEVELCOLORS[stoi(colors[0])] = {colors[1], colors[2]};
        }
        int langIndex = ranges::find_if(languages, [&](const MLanguage& o){
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
    selectedUSLang2 = &*ranges::find_if(userSettings, [&](const MUserSetting& o){
        return o.KIND == 2 && o.ENTITYID == langid;
    });
    selectedUSLang3 = &*ranges::find_if(userSettings, [&](const MUserSetting& o){
        return o.KIND == 3 && o.ENTITYID == langid;
    });
    auto s = getUSDICTITEMS();
    vector<string> dicts = s | view::split("\r\n"s);
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
        int index = ranges::find_if(dictItems, [&](const MDictItem& o){
            return o.DICTID == getUSDICTITEM();
        }) - dictItems.begin();
        setSelectedDictItem(index);
        dictsNote = get<1>(o);
        index = ranges::find_if(dictsNote, [&](const MDictNote& o){
            return o.DICTID == getUSDICTNOTEID();
        }) - dictsNote.begin();
        setSelectedDictNote(index);
        if (dictsNote.empty()) dictsNote.emplace_back();
        dictsTranslation = get<2>(o);
        index = ranges::find_if(dictsTranslation, [&](const MDictTranslation& o){
            return o.DICTID == getUSDICTTRANSLATIONID();
        }) - dictsTranslation.begin();
        setSelectedDictTranslation(index);
        if (dictsTranslation.empty()) dictsTranslation.emplace_back();
        textbooks = get<3>(o);
        index = ranges::find_if(textbooks, [&](const MTextbook& o){
            return o.ID == getUSTEXTBOOKID();
        }) - textbooks.begin();
        setSelectedTextbook(index);
        autoCorrects = get<4>(o);
        macVoices = get<5>(o) | view::filter([](const MVoice& o) {
            return o.VOICETYPEID == 2;
        }) | ranges::to_vector;
        index = ranges::find_if(macVoices, [&](const MVoice& o){
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
    selectedUSTextbook = &*ranges::find_if(userSettings, [&](const MUserSetting& o){
        return o.KIND == 11 && o.ENTITYID == textbookid;
    });
}
