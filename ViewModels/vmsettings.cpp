#include <range/v3/all.hpp>
using namespace ranges;
#include "vmsettings.h"

VMSettingsDelegate::~VMSettingsDelegate() {}
void VMSettingsDelegate::onGetData() {}
void VMSettingsDelegate::onUpdateLang() {}
void VMSettingsDelegate::onUpdateDictItem() {}
void VMSettingsDelegate::onUpdateDictNote() {}
void VMSettingsDelegate::onUpdateDictTranslation() {}
void VMSettingsDelegate::onUpdateTextbook() {}
void VMSettingsDelegate::onUpdateUnitFrom() {}
void VMSettingsDelegate::onUpdatePartFrom() {}
void VMSettingsDelegate::onUpdateUnitTo() {}
void VMSettingsDelegate::onUpdatePartTo() {}
void VMSettingsDelegate::onUpdateMacVoice() {}

vector<int> VMSettings::getUSROWSPERPAGEOPTIONS() const
{
    vector<string> result = selectedUSUser0->VALUE2.get() | view::split(',');
    return result | view::transform([](const string& s){
        return stoi(s);
    });
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
        if (delegate) delegate->onGetData();
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
    bool isinit = getUSLANGID() == langid;
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
                svoice.getDataByLang(langid)).flat_map([&, dicts](const auto& o) -> observable<string> {
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
        });
        index = ranges::find_if(macVoices, [&](const MVoice& o){
            return o.ID == getUSMACVOICEID();
        }) - macVoices.begin();
        setSelectedMacVoice(index);
        if (isinit) {
            if (delegate) delegate->onUpdateLang();
            return just(string{});
        } else {
            return updateLang();
        }
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

observable<string> VMSettings::updateLang()
{
    return susersetting.updateLang(selectedUSUser0->ID, getUSLANGID()).map([&](const auto& s){
        if (delegate) delegate->onUpdateLang();
        return s;
    });
}

observable<string> VMSettings::updateDictItem()
{
    return susersetting.updateDictItem(selectedUSLang2->ID, getUSDICTITEM()).map([&](const auto& s){
        if (delegate) delegate->onUpdateDictItem();
        return s;
    });
}

observable<string> VMSettings::updateDictNote()
{
    return susersetting.updateDictNote(selectedUSLang2->ID, getUSDICTNOTEID()).map([&](const auto& s){
        if (delegate) delegate->onUpdateDictNote();
        return s;
    });
}

observable<string> VMSettings::updateDictTranslation()
{
    return susersetting.updateDictTranslation(selectedUSLang3->ID, getUSDICTTRANSLATIONID()).map([&](const auto& s){
        if (delegate) delegate->onUpdateDictTranslation();
        return s;
    });
}

observable<string> VMSettings::updateTextbook()
{
    return susersetting.updateTextbook(selectedUSLang2->ID, getUSTEXTBOOKID()).map([&](const auto& s){
        if (delegate) delegate->onUpdateTextbook();
        return s;
    });
}

observable<string> VMSettings::updateMacVoice()
{
    return susersetting.updateMacVoice(selectedUSLang3->ID, getUSMACVOICEID()).map([&](const auto& s){
        if (delegate) delegate->onUpdateMacVoice();
        return s;
    });
}

string VMSettings::autoCorrectInput(const string &text)
{
    return autoCorrect(text, autoCorrects, [](const MAutoCorrect& row){
        return row.INPUT;
    }, [](const MAutoCorrect& row){
        return row.EXTENDED;
    });
}

observable<string> VMSettings::updateUnitFrom()
{
    return susersetting.updateUnitFrom(selectedUSLang3->ID, getUSUNITFROM()).map([&](const auto& s){
        if (delegate) delegate->onUpdateUnitFrom();
        return s;
    });
}

observable<string> VMSettings::updatePartFrom()
{
    return susersetting.updatePartFrom(selectedUSLang3->ID, getUSPARTFROM()).map([&](const auto& s){
        if (delegate) delegate->onUpdatePartFrom();
        return s;
    });
}

observable<string> VMSettings::updateUnitTo()
{
    return susersetting.updateUnitTo(selectedUSLang3->ID, getUSUNITTO()).map([&](const auto& s){
        if (delegate) delegate->onUpdateUnitTo();
        return s;
    });
}

observable<string> VMSettings::updatePartTo()
{
    return susersetting.updatePartTo(selectedUSLang3->ID, getUSPARTTO()).map([&](const auto& s){
        if (delegate) delegate->onUpdatePartTo();
        return s;
    });
}
