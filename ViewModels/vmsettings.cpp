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

MUserSettingInfo VMSettings::getUSInfo(const wstring &name)
{
    const auto& o = *ranges::find_if(usmappings, [&](const MUSMapping& o3){
        return o3.NAME == name;
    });
    const int entityid = o.ENTITYID != -1 ? o.ENTITYID :
        o.LEVEL == 1 ? selectedLang().ID :
        o.LEVEL == 2 ? selectedTextbook().ID :
        0;
    const auto& o2 = *ranges::find_if(userSettings, [&](const MUserSetting& o3){
        return o3.KIND == o.KIND && o3.ENTITYID == entityid;
    });
    return {o2.ID, o.VALUEID};
}

boost::optional<wstring> VMSettings::getUSValue(const MUserSettingInfo &info) const
{
    const auto& o2 = *ranges::find_if(userSettings, [&](const MUserSetting& o){
        return o.ID == info.USERSETTINGID;
    });
    switch (info.VALUEID) {
    case 1: return o2.VALUE1;
    case 2: return o2.VALUE2;
    case 3: return o2.VALUE3;
    case 4: return o2.VALUE4;
    default: return {};
    }
}

void VMSettings::setUSValue(const MUserSettingInfo &info, const wstring &value)
{
    auto& o2 = *ranges::find_if(userSettings, [&](const MUserSetting& o){
        return o.ID == info.USERSETTINGID;
    });
    switch (info.VALUEID) {
    case 1: o2.VALUE1 = value; break;
    case 2: o2.VALUE2 = value; break;
    case 3: o2.VALUE3 = value; break;
    case 4: o2.VALUE4 = value; break;
    }
}

vector<int> VMSettings::getUSROWSPERPAGEOPTIONS() const
{
    vector<wstring> result = getUSValue(INFO_USROWSPERPAGEOPTIONS).get() | view::split(',');
    return result | view::transform([](const wstring& s){
        return stoi(s);
    });
}

observable<wstring> VMSettings::getData()
{
    return slanguage.getData().zip(
                susmapping.getData(),
                susersetting.getData(1),
                sdicttype.getData()).flat_map([&](const auto& o){
        languages = get<0>(o);
        usmappings = get<1>(o);
        userSettings = get<2>(o);
        dictTypes = get<3>(o);
        INFO_USLANGID = getUSInfo(MUSMapping::NAME_USLANGID);
        INFO_USROWSPERPAGEOPTIONS = getUSInfo(MUSMapping::NAME_USROWSPERPAGEOPTIONS);
        INFO_USROWSPERPAGE = getUSInfo(MUSMapping::NAME_USROWSPERPAGE);
        INFO_USLEVELCOLORS = getUSInfo(MUSMapping::NAME_USLEVELCOLORS);
        INFO_USSCANINTERVAL = getUSInfo(MUSMapping::NAME_USSCANINTERVAL);
        INFO_USREVIEWINTERVAL = getUSInfo(MUSMapping::NAME_USREVIEWINTERVAL);
        vector<wstring> lines = getUSValue(INFO_USLEVELCOLORS).get() | view::split("\r\n"s);
        for(const wstring& s : lines) {
            vector<wstring> colors = s | view::split(',');
            USLEVELCOLORS[stoi(colors[0])] = {colors[1], colors[2]};
        }
        selectedLangIndex = ranges::find_if(languages, [&](const MLanguage& o){
            return o.ID == USLANGID();
        }) - languages.begin();
        if (delegate) delegate->onGetData();
        return setSelectedLang(selectedLangIndex);
    }) APPLY_IO;
}

observable<wstring> VMSettings::setSelectedLang(int langIndex)
{
    bool isinit = selectedLangIndex == langIndex;
    selectedLangIndex = langIndex;
    int langid = selectedLang().ID;
    USLANGID(langid);
    INFO_USTEXTBOOKID = getUSInfo(MUSMapping::NAME_USTEXTBOOKID);
    INFO_USDICTITEM = getUSInfo(MUSMapping::NAME_USDICTITEM);
    INFO_USDICTNOTEID = getUSInfo(MUSMapping::NAME_USDICTNOTEID);
    INFO_USDICTITEMS = getUSInfo(MUSMapping::NAME_USDICTITEMS);
    INFO_USDICTTRANSLATIONID = getUSInfo(MUSMapping::NAME_USDICTTRANSLATIONID);
    INFO_USMACVOICEID = getUSInfo(MUSMapping::NAME_USMACVOICEID);
    auto s = USDICTITEMS();
    vector<wstring> dicts = s | view::split("\r\n"s);
    return sdictreference.getDataByLang(langid).zip(
                sdictnote.getDataByLang(langid),
                sdicttranslation.getDataByLang(langid),
                stextbook.getDataByLang(langid),
                sautocorrect.getDataByLang(langid),
                svoice.getDataByLang(langid)).flat_map([&, dicts](const auto& o) -> observable<wstring> {
        dictsReference = get<0>(o);
        int i = 0;
        // https://stackoverflow.com/questions/36051851/how-to-implement-flatmap-using-rangev3-ranges
        dictItems = dicts | view::transform([&](const wstring& d){
            return d == "0" ?
                dictsReference | view::transform([](const auto& o2){
                    return MDictItem{ to_wstring(o2.DICTID), o2.DICTNAME };
                }) | ranges::to_vector :
                vector{MDictItem{ d, (boost::wformat(L"Custom%1%") % ++i).str() }};
        }) | action::join;
        int index = ranges::find_if(dictItems, [&](const MDictItem& o){
            return o.DICTID == USDICTITEM();
        }) - dictItems.begin();
        setSelectedDictItem(index);
        dictsNote = get<1>(o);
        index = ranges::find_if(dictsNote, [&](const MDictNote& o){
            return o.DICTID == USDICTNOTEID();
        }) - dictsNote.begin();
        if (dictsNote.empty()) dictsNote.emplace_back();
        setSelectedDictNote(index);
        dictsTranslation = get<2>(o);
        index = ranges::find_if(dictsTranslation, [&](const MDictTranslation& o){
            return o.DICTID == USDICTTRANSLATIONID();
        }) - dictsTranslation.begin();
        if (dictsTranslation.empty()) dictsTranslation.emplace_back();
        setSelectedDictTranslation(index);
        textbooks = get<3>(o);
        index = ranges::find_if(textbooks, [&](const MTextbook& o){
            return o.ID == USTEXTBOOKID();
        }) - textbooks.begin();
        setSelectedTextbook(index);
        autoCorrects = get<4>(o);
        macVoices = get<5>(o) | view::filter([](const MVoice& o) {
            return o.VOICETYPEID == 2;
        });
        index = ranges::find_if(macVoices, [&](const MVoice& o){
            return o.ID == USMACVOICEID();
        }) - macVoices.begin();
        setSelectedMacVoice(index);
        if (isinit) {
            if (delegate) delegate->onUpdateLang();
            return just(wstring{});
        } else {
            return updateLang();
        }
    }) APPLY_IO;
}

void VMSettings::setSelectedMacVoice(int index)
{
   selectedMacVoiceIndex = index;
   USMACVOICEID(selectedMacVoice().ID);
}

void VMSettings::setSelectedDictItem(int index)
{
   selectedDictItemIndex = index;
   USDICTITEM(selectedDictItem().DICTID);
}

void VMSettings::setSelectedDictNote(int index)
{
   selectedDictNoteIndex = index;
   USDICTNOTEID(selectedDictNote().DICTID);
}

void VMSettings::setSelectedDictTranslation(int index)
{
    selectedDictTranslationIndex = index;
    USDICTTRANSLATIONID(selectedDictTranslation().DICTID);
}

void VMSettings::setSelectedTextbook(int index)
{
    selectedTextbookIndex = index;
    int textbookid = selectedTextbook().ID;
    USTEXTBOOKID(textbookid);
    INFO_USUNITFROM = getUSInfo(MUSMapping::NAME_USUNITFROM);
    INFO_USPARTFROM = getUSInfo(MUSMapping::NAME_USPARTFROM);
    INFO_USUNITTO = getUSInfo(MUSMapping::NAME_USUNITTO);
    INFO_USPARTTO = getUSInfo(MUSMapping::NAME_USPARTTO);
    toType = isSingleUnit() ? UnitPartToType::UNIT : isSingleUnitPart() ? UnitPartToType::PART : UnitPartToType::TO;
}

observable<wstring> VMSettings::updateLang()
{
    return susersetting.updateObject(INFO_USLANGID, USLANGID()).tap([&](const auto& ){
        if (delegate) delegate->onUpdateLang();
    }) APPLY_IO;
}

observable<wstring> VMSettings::updateTextbook()
{
    return susersetting.updateObject(INFO_USTEXTBOOKID, USTEXTBOOKID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateTextbook();
    }) APPLY_IO;
}

observable<wstring> VMSettings::updateDictItem()
{
    return susersetting.updateObject(INFO_USDICTITEM, USDICTITEM()).tap([&](const auto&){
        if (delegate) delegate->onUpdateDictItem();
    }) APPLY_IO;
}

observable<wstring> VMSettings::updateDictNote()
{
    return susersetting.updateObject(INFO_USDICTNOTEID, USDICTNOTEID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateDictNote();
    }) APPLY_IO;
}

observable<wstring> VMSettings::updateDictTranslation()
{
    return susersetting.updateObject(INFO_USDICTTRANSLATIONID, USDICTTRANSLATIONID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateDictTranslation();
    }) APPLY_IO;
}

observable<wstring> VMSettings::updateMacVoice()
{
    return susersetting.updateObject(INFO_USMACVOICEID, USMACVOICEID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateMacVoice();
    }) APPLY_IO;
}

wstring VMSettings::autoCorrectInput(const wstring &text)
{
    return autoCorrect(text, autoCorrects, [](const MAutoCorrect& row){
        return row.INPUT;
    }, [](const MAutoCorrect& row){
        return row.EXTENDED;
    });
}

observable<wstring> VMSettings::updateUnitFrom()
{
    return doUpdateUnitFrom(USUNITFROM()).concat(
        toType == UnitPartToType::UNIT ? doUpdateSingleUnit() :
        toType == UnitPartToType::PART || isInvalidUnitPart() ? doUpdateUnitPartTo() :
        static_cast<observable<wstring>>(empty<wstring>())) APPLY_IO;
}

observable<wstring> VMSettings::updatePartFrom()
{
    return doUpdatePartFrom(USPARTFROM()).concat(
        toType == UnitPartToType::PART || isInvalidUnitPart() ? doUpdateUnitPartTo() :
        static_cast<observable<wstring>>(empty<wstring>())) APPLY_IO;
}

observable<wstring> VMSettings::updateUnitTo()
{
    return doUpdateUnitTo(USUNITTO()).concat(
        isInvalidUnitPart() ? doUpdateUnitPartFrom() :
        static_cast<observable<wstring>>(empty<wstring>())) APPLY_IO;
}

observable<wstring> VMSettings::updatePartTo()
{
    return doUpdatePartTo(USPARTTO()).concat(
        isInvalidUnitPart() ? doUpdateUnitPartFrom() :
        static_cast<observable<wstring>>(empty<wstring>())) APPLY_IO;
}

observable<wstring> VMSettings::updateToType()
{
    return (toType == UnitPartToType::UNIT ? doUpdateSingleUnit() :
        toType == UnitPartToType::PART ? doUpdateUnitPartTo() :
        static_cast<observable<wstring>>(empty<wstring>())) APPLY_IO;
}

observable<wstring> VMSettings::previousUnitPart()
{
    if (toType == UnitPartToType::UNIT)
        if (USUNITFROM() > 1)
            return doUpdateUnitFrom(USUNITFROM() - 1).zip(doUpdateUnitTo(USUNITFROM())).map([](const auto&){
                return wstring{};
            }) APPLY_IO;
        else
            return empty<wstring>();
    else if (USPARTFROM() > 1)
        return doUpdatePartFrom(USPARTFROM() - 1).zip(doUpdateUnitPartTo()).map([](const auto&){
            return wstring{};
        }) APPLY_IO;
    else if (USUNITFROM() > 1)
        return doUpdateUnitFrom(USUNITFROM() - 1).zip(doUpdatePartFrom(getPartCount()), doUpdateUnitPartTo()).map([](const auto&){
            return wstring{};
        }) APPLY_IO;
    else
        return empty<wstring>();
}

observable<wstring> VMSettings::nextUnitPart()
{
    if (toType == UnitPartToType::UNIT)
        if (USUNITFROM() < getUnitCount())
            return doUpdateUnitFrom(USUNITFROM() + 1).zip(doUpdateUnitTo(USUNITFROM())).map([](const auto&){
                return wstring{};
            }) APPLY_IO;
        else
            return empty<wstring>();
    else if (USPARTFROM() < getPartCount())
        return doUpdatePartFrom(USPARTFROM() + 1).zip(doUpdateUnitPartTo()).map([](const auto&){
            return wstring{};
        }) APPLY_IO;
    else if (USUNITFROM() < getUnitCount())
        return doUpdateUnitFrom(USUNITFROM() + 1).zip(doUpdatePartFrom(1), doUpdateUnitPartTo()).map([](const auto&){
            return wstring{};
        }) APPLY_IO;
    else
        return empty<wstring>();
}

observable<wstring> VMSettings::doUpdateUnitPartFrom()
{
    return doUpdateUnitFrom(USUNITTO()).zip(doUpdatePartFrom(USPARTTO())).map([](const auto&){
        return wstring{};
    });
}

observable<wstring> VMSettings::doUpdateUnitPartTo()
{
    return doUpdateUnitTo(USUNITFROM()).zip(doUpdatePartTo(USPARTFROM())).map([](const auto&){
        return wstring{};
    });
}

observable<wstring> VMSettings::doUpdateSingleUnit()
{
    return doUpdateUnitTo(USUNITFROM()).zip(doUpdatePartFrom(1), doUpdatePartTo(getPartCount())).map([](const auto&){
        return wstring{};
    });
}

observable<wstring> VMSettings::doUpdateUnitFrom(int v)
{
    USUNITFROM(v);
    return susersetting.updateObject(INFO_USUNITFROM, v).tap([&](const auto&){
        if (delegate) delegate->onUpdateUnitFrom();
    });
}

observable<wstring> VMSettings::doUpdatePartFrom(int v)
{
    USPARTFROM(v);
    return susersetting.updateObject(INFO_USPARTFROM, v).tap([&](const auto&){
        if (delegate) delegate->onUpdatePartFrom();
    });
}

observable<wstring> VMSettings::doUpdateUnitTo(int v)
{
    USUNITTO(v);
    return susersetting.updateObject(INFO_USUNITTO, v).tap([&](const auto&){
        if (delegate) delegate->onUpdateUnitTo();
    });
}

observable<wstring> VMSettings::doUpdatePartTo(int v)
{
    USPARTTO(v);
    return susersetting.updateObject(INFO_USPARTTO, v).tap([&](const auto&){
        if (delegate) delegate->onUpdatePartTo();
    });
}
