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
        selectedLangIndex = ranges::find_if(languages, [&](const MLanguage& o){
            return o.ID == getUSLANGID();
        }) - languages.begin();
        if (delegate) delegate->onGetData();
        return setSelectedLang(selectedLangIndex);
    });
}

observable<string> VMSettings::setSelectedLang(int langIndex)
{
    bool isinit = selectedLangIndex == langIndex;
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
                svoice.getDataByLang(langid)).flat_map([&, dicts](const auto& o) -> observable<string> {
        dictsReference = get<0>(o);
        int i = 0;
        // https://stackoverflow.com/questions/36051851/how-to-implement-flatmap-using-rangev3-ranges
        dictItems = dicts | view::transform([&](const string& d){
            return d == "0" ?
                dictsReference | view::transform([](const auto& o2){
                    return MDictItem{ to_string(o2.DICTID), o2.DICTNAME };
                }) | ranges::to_vector :
                vector{MDictItem{ d, (boost::format("Custom%1%") % ++i).str() }};
        }) | action::join;
        int index = ranges::find_if(dictItems, [&](const MDictItem& o){
            return o.DICTID == getUSDICTITEM();
        }) - dictItems.begin();
        setSelectedDictItem(index);
        dictsNote = get<1>(o);
        index = ranges::find_if(dictsNote, [&](const MDictNote& o){
            return o.DICTID == getUSDICTNOTEID();
        }) - dictsNote.begin();
        if (dictsNote.empty()) dictsNote.emplace_back();
        setSelectedDictNote(index);
        dictsTranslation = get<2>(o);
        index = ranges::find_if(dictsTranslation, [&](const MDictTranslation& o){
            return o.DICTID == getUSDICTTRANSLATIONID();
        }) - dictsTranslation.begin();
        if (dictsTranslation.empty()) dictsTranslation.emplace_back();
        setSelectedDictTranslation(index);
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
    toType = isSingleUnit() ? 0 : isSingleUnitPart() ? 1 : 2;
}

observable<string> VMSettings::updateLang()
{
    return susersetting.updateLang(selectedUSUser0->ID, getUSLANGID()).tap([&](const auto& ){
        if (delegate) delegate->onUpdateLang();
    });
}

observable<string> VMSettings::updateDictItem()
{
    return susersetting.updateDictItem(selectedUSLang2->ID, getUSDICTITEM()).tap([&](const auto&){
        if (delegate) delegate->onUpdateDictItem();
    });
}

observable<string> VMSettings::updateDictNote()
{
    return susersetting.updateDictNote(selectedUSLang2->ID, getUSDICTNOTEID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateDictNote();
    });
}

observable<string> VMSettings::updateDictTranslation()
{
    return susersetting.updateDictTranslation(selectedUSLang3->ID, getUSDICTTRANSLATIONID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateDictTranslation();
    });
}

observable<string> VMSettings::updateTextbook()
{
    return susersetting.updateTextbook(selectedUSLang2->ID, getUSTEXTBOOKID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateTextbook();
    });
}

observable<string> VMSettings::updateMacVoice()
{
    return susersetting.updateMacVoice(selectedUSLang3->ID, getUSMACVOICEID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateMacVoice();
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
    return susersetting.updateUnitFrom(selectedUSLang3->ID, getUSUNITFROM()).tap([&](const auto&){
        if (delegate) delegate->onUpdateUnitFrom();
    });
}

observable<string> VMSettings::updatePartFrom()
{
    return susersetting.updatePartFrom(selectedUSLang3->ID, getUSPARTFROM()).tap([&](const auto&){
        if (delegate) delegate->onUpdatePartFrom();
    });
}

observable<string> VMSettings::updateUnitTo()
{
    return susersetting.updateUnitTo(selectedUSLang3->ID, getUSUNITTO()).tap([&](const auto&){
        if (delegate) delegate->onUpdateUnitTo();
    });
}

observable<string> VMSettings::updatePartTo()
{
    return susersetting.updatePartTo(selectedUSLang3->ID, getUSPARTTO()).tap([&](const auto&){
        if (delegate) delegate->onUpdatePartTo();
    });
}

observable<string> VMSettings::updateToType()
{
    if (toType == 0)
        return doUpdateSingleUnit();
    else if (toType == 1)
        return doUpdateUnitPartTo();
    else
        return empty<string>();
}

observable<string> VMSettings::previousUnitPart()
{
    if (toType == 0)
        if (getUSUNITFROM() > 1)
            return doUpdateUnitFrom(getUSUNITFROM() - 1).zip(doUpdateUnitTo(getUSUNITFROM())).map([](const auto&){
                return string{};
            });
        else
            return empty<string>();
    else if (getUSPARTFROM() > 1)
        return doUpdatePartFrom(getUSPARTFROM() - 1).zip(doUpdateUnitPartTo()).map([](const auto&){
            return string{};
        });
    else if (getUSUNITFROM() > 1)
        return doUpdateUnitFrom(getUSUNITFROM() - 1).zip(doUpdatePartFrom(getPartCount()), doUpdateUnitPartTo()).map([](const auto&){
            return string{};
        });
    else
        return empty<string>();
}

observable<string> VMSettings::nextUnitPart()
{
    if (toType == 0)
        if (getUSUNITFROM() < getUnitCount())
            return doUpdateUnitFrom(getUSUNITFROM() + 1).zip(doUpdateUnitTo(getUSUNITFROM())).map([](const auto&){
                return string{};
            });
        else
            return empty<string>();
    else if (getUSPARTFROM() < getPartCount())
        return doUpdatePartFrom(getUSPARTFROM() + 1).zip(doUpdateUnitPartTo()).map([](const auto&){
            return string{};
        });
    else if (getUSUNITFROM() < getUnitCount())
        return doUpdateUnitFrom(getUSUNITFROM() + 1).zip(doUpdatePartFrom(1), doUpdateUnitPartTo()).map([](const auto&){
            return string{};
        });
    else
        return empty<string>();
}

observable<string> VMSettings::doUpdateUnitPartFrom()
{
    return doUpdateUnitFrom(getUSUNITTO()).zip(doUpdatePartFrom(getUSPARTTO())).map([](const auto&){
        return string{};
    });
}

observable<string> VMSettings::doUpdateUnitPartTo()
{
    return doUpdateUnitTo(getUSUNITFROM()).zip(doUpdatePartTo(getUSPARTFROM())).map([](const auto&){
        return string{};
    });
}

observable<string> VMSettings::doUpdateSingleUnit()
{
    return doUpdateUnitTo(getUSUNITFROM()).zip(doUpdatePartFrom(1), doUpdatePartTo(getPartCount())).map([](const auto&){
        return string{};
    });
}

observable<string> VMSettings::doUpdateUnitFrom(int v)
{
    setUSUNITFROM(v);
    return susersetting.updateUnitFrom(selectedUSLang3->ID, v).tap([&](const auto&){
        if (delegate) delegate->onUpdateUnitFrom();
    });
}

observable<string> VMSettings::doUpdatePartFrom(int v)
{
    setUSPARTFROM(v);
    return susersetting.updatePartFrom(selectedUSLang3->ID, v).tap([&](const auto&){
        if (delegate) delegate->onUpdatePartFrom();
    });
}

observable<string> VMSettings::doUpdateUnitTo(int v)
{
    setUSUNITTO(v);
    return susersetting.updateUnitTo(selectedUSLang3->ID, v).tap([&](const auto&){
        if (delegate) delegate->onUpdateUnitTo();
    });
}

observable<string> VMSettings::doUpdatePartTo(int v)
{
    setUSPARTTO(v);
    return susersetting.updatePartTo(selectedUSLang3->ID, v).tap([&](const auto&){
        if (delegate) delegate->onUpdatePartTo();
    });
}
