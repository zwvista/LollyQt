#include <range/v3/all.hpp>
using namespace ranges;
#include "vmsettings.h"

VMSettingsDelegate::~VMSettingsDelegate() {}
void VMSettingsDelegate::onGetData() {}
void VMSettingsDelegate::onUpdateLang() {}
void VMSettingsDelegate::onUpdateDictReference() {}
void VMSettingsDelegate::onUpdateDictNote() {}
void VMSettingsDelegate::onUpdateDictTranslation() {}
void VMSettingsDelegate::onUpdateTextbook() {}
void VMSettingsDelegate::onUpdateUnitFrom() {}
void VMSettingsDelegate::onUpdatePartFrom() {}
void VMSettingsDelegate::onUpdateUnitTo() {}
void VMSettingsDelegate::onUpdatePartTo() {}
void VMSettingsDelegate::onUpdateMacVoice() {}

MUserSettingInfo VMSettings::getUSInfo(const string_t &name)
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

boost::optional<string_t> VMSettings::getUSValue(const MUserSettingInfo &info) const
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

void VMSettings::setUSValue(const MUserSettingInfo &info, const string_t &value)
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
    vector<string_t> result = getUSValue(INFO_USROWSPERPAGEOPTIONS).get() | views::split(',') | to<vector<string_t>>;
    return result | views::transform([](const string_t& s){
        return stoi(s);
    }) | to<vector>;
}

observable<string_t> VMSettings::getData()
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
        vector<string_t> lines = getUSValue(INFO_USLEVELCOLORS).get() | views::split("\r\n"s) | to<vector<string_t>>;
        for(const string_t& s : lines) {
            vector<string_t> colors = s | views::split(',') | to<vector<string_t>>;
            USLEVELCOLORS[stoi(colors[0])] = {colors[1], colors[2]};
        }
        selectedLangIndex = ranges::find_if(languages, [&](const MLanguage& o){
            return o.ID == USLANGID();
        }) - languages.begin();
        if (delegate) delegate->onGetData();
        return setSelectedLang(selectedLangIndex);
    }) APPLY_IO;
}

observable<string_t> VMSettings::setSelectedLang(int langIndex)
{
    bool isinit = selectedLangIndex == langIndex;
    selectedLangIndex = langIndex;
    int langid = selectedLang().ID;
    USLANGID(langid);
    INFO_USTEXTBOOKID = getUSInfo(MUSMapping::NAME_USTEXTBOOKID);
    INFO_USDICTITEM = getUSInfo(MUSMapping::NAME_USDICTITEM);
    INFO_USDICTNOTEID = getUSInfo(MUSMapping::NAME_USDICTNOTEID);
    INFO_USDICTSREFERENCE = getUSInfo(MUSMapping::NAME_USDICTSREFERENCE);
    INFO_USDICTTRANSLATIONID = getUSInfo(MUSMapping::NAME_USDICTTRANSLATIONID);
    INFO_USMACVOICEID = getUSInfo(MUSMapping::NAME_USMACVOICEID);
    return sdictionary.getDictsReferenceByLang(langid).zip(
                sdictionary.getDictsNoteByLang(langid),
                sdictionary.getDictsTranslationByLang(langid),
                stextbook.getDataByLang(langid),
                sautocorrect.getDataByLang(langid),
                svoice.getDataByLang(langid)).flat_map([&](const auto& o) -> observable<string_t> {
        dictsReference = get<0>(o);
        int index = ranges::find_if(dictsReference, [&](const MDictionary& o){
            return to_string_t(o.DICTID) == USDICTREFERENCE();
        }) - dictsReference.begin();
        setSelectedDictReference(index);
        dictsNote = get<1>(o);
        index = ranges::find_if(dictsNote, [&](const MDictionary& o){
            return o.DICTID == USDICTNOTE();
        }) - dictsNote.begin();
        if (dictsNote.empty()) dictsNote.emplace_back();
        setSelectedDictNote(index);
        dictsTranslation = get<2>(o);
        index = ranges::find_if(dictsTranslation, [&](const MDictionary& o){
            return o.DICTID == USDICTTRANSLATION();
        }) - dictsTranslation.begin();
        if (dictsTranslation.empty()) dictsTranslation.emplace_back();
        setSelectedDictTranslation(index);
        textbooks = get<3>(o);
        index = ranges::find_if(textbooks, [&](const MTextbook& o){
            return o.ID == USTEXTBOOKID();
        }) - textbooks.begin();
        setSelectedTextbook(index);
        autoCorrects = get<4>(o);
        macVoices = get<5>(o) | views::filter([](const MVoice& o) {
            return o.VOICETYPEID == 2;
        }) | to<vector>;
        index = ranges::find_if(macVoices, [&](const MVoice& o){
            return o.ID == USMACVOICEID();
        }) - macVoices.begin();
        setSelectedMacVoice(index);
        if (isinit) {
            if (delegate) delegate->onUpdateLang();
            return just(string_t{});
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

void VMSettings::setSelectedDictReference(int index)
{
   selectedDictReferenceIndex = index;
   USDICTREFERENCE(to_string_t(selectedDictReference().DICTID));
}

void VMSettings::setSelectedDictNote(int index)
{
   selectedDictNoteIndex = index;
   USDICTNOTE(selectedDictNote().DICTID);
}

void VMSettings::setSelectedDictTranslation(int index)
{
    selectedDictTranslationIndex = index;
    USDICTTRANSLATION(selectedDictTranslation().DICTID);
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

observable<string_t> VMSettings::updateLang()
{
    return susersetting.updateObject(INFO_USLANGID, USLANGID()).tap([&](const auto& ){
        if (delegate) delegate->onUpdateLang();
    }) APPLY_IO;
}

observable<string_t> VMSettings::updateTextbook()
{
    return susersetting.updateObject(INFO_USTEXTBOOKID, USTEXTBOOKID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateTextbook();
    }) APPLY_IO;
}

observable<string_t> VMSettings::updateDictReference()
{
    return susersetting.updateObject(INFO_USDICTITEM, USDICTREFERENCE()).tap([&](const auto&){
        if (delegate) delegate->onUpdateDictReference();
    }) APPLY_IO;
}

observable<string_t> VMSettings::updateDictNote()
{
    return susersetting.updateObject(INFO_USDICTNOTEID, USDICTNOTE()).tap([&](const auto&){
        if (delegate) delegate->onUpdateDictNote();
    }) APPLY_IO;
}

observable<string_t> VMSettings::updateDictTranslation()
{
    return susersetting.updateObject(INFO_USDICTTRANSLATIONID, USDICTTRANSLATION()).tap([&](const auto&){
        if (delegate) delegate->onUpdateDictTranslation();
    }) APPLY_IO;
}

observable<string_t> VMSettings::updateMacVoice()
{
    return susersetting.updateObject(INFO_USMACVOICEID, USMACVOICEID()).tap([&](const auto&){
        if (delegate) delegate->onUpdateMacVoice();
    }) APPLY_IO;
}

string_t VMSettings::autoCorrectInput(const string_t &text)
{
    return autoCorrect(text, autoCorrects, [](const MAutoCorrect& row){
        return row.INPUT;
    }, [](const MAutoCorrect& row){
        return row.EXTENDED;
    });
}

observable<string_t> VMSettings::updateUnitFrom()
{
    return doUpdateUnitFrom(USUNITFROM()).concat(
        toType == UnitPartToType::UNIT ? doUpdateSingleUnit() :
        toType == UnitPartToType::PART || isInvalidUnitPart() ? doUpdateUnitPartTo() :
        static_cast<observable<string_t>>(rxcpp::sources::empty<string_t>())) APPLY_IO;
}

observable<string_t> VMSettings::updatePartFrom()
{
    return doUpdatePartFrom(USPARTFROM()).concat(
        toType == UnitPartToType::PART || isInvalidUnitPart() ? doUpdateUnitPartTo() :
        static_cast<observable<string_t>>(rxcpp::sources::empty<string_t>())) APPLY_IO;
}

observable<string_t> VMSettings::updateUnitTo()
{
    return doUpdateUnitTo(USUNITTO()).concat(
        isInvalidUnitPart() ? doUpdateUnitPartFrom() :
        static_cast<observable<string_t>>(rxcpp::sources::empty<string_t>())) APPLY_IO;
}

observable<string_t> VMSettings::updatePartTo()
{
    return doUpdatePartTo(USPARTTO()).concat(
        isInvalidUnitPart() ? doUpdateUnitPartFrom() :
        static_cast<observable<string_t>>(rxcpp::sources::empty<string_t>())) APPLY_IO;
}

observable<string_t> VMSettings::updateToType()
{
    return (toType == UnitPartToType::UNIT ? doUpdateSingleUnit() :
        toType == UnitPartToType::PART ? doUpdateUnitPartTo() :
        static_cast<observable<string_t>>(rxcpp::sources::empty<string_t>())) APPLY_IO;
}

observable<string_t> VMSettings::previousUnitPart()
{
    if (toType == UnitPartToType::UNIT)
        if (USUNITFROM() > 1)
            return doUpdateUnitFrom(USUNITFROM() - 1).zip(doUpdateUnitTo(USUNITFROM())).map([](const auto&){
                return string_t{};
            }) APPLY_IO;
        else
            return rxcpp::sources::empty<string_t>();
    else if (USPARTFROM() > 1)
        return doUpdatePartFrom(USPARTFROM() - 1).zip(doUpdateUnitPartTo()).map([](const auto&){
            return string_t{};
        }) APPLY_IO;
    else if (USUNITFROM() > 1)
        return doUpdateUnitFrom(USUNITFROM() - 1).zip(doUpdatePartFrom(getPartCount()), doUpdateUnitPartTo()).map([](const auto&){
            return string_t{};
        }) APPLY_IO;
    else
        return rxcpp::sources::empty<string_t>();
}

observable<string_t> VMSettings::nextUnitPart()
{
    if (toType == UnitPartToType::UNIT)
        if (USUNITFROM() < getUnitCount())
            return doUpdateUnitFrom(USUNITFROM() + 1).zip(doUpdateUnitTo(USUNITFROM())).map([](const auto&){
                return string_t{};
            }) APPLY_IO;
        else
            return rxcpp::sources::empty<string_t>();
    else if (USPARTFROM() < getPartCount())
        return doUpdatePartFrom(USPARTFROM() + 1).zip(doUpdateUnitPartTo()).map([](const auto&){
            return string_t{};
        }) APPLY_IO;
    else if (USUNITFROM() < getUnitCount())
        return doUpdateUnitFrom(USUNITFROM() + 1).zip(doUpdatePartFrom(1), doUpdateUnitPartTo()).map([](const auto&){
            return string_t{};
        }) APPLY_IO;
    else
        return rxcpp::sources::empty<string_t>();
}

observable<string_t> VMSettings::doUpdateUnitPartFrom()
{
    return doUpdateUnitFrom(USUNITTO()).zip(doUpdatePartFrom(USPARTTO())).map([](const auto&){
        return string_t{};
    });
}

observable<string_t> VMSettings::doUpdateUnitPartTo()
{
    return doUpdateUnitTo(USUNITFROM()).zip(doUpdatePartTo(USPARTFROM())).map([](const auto&){
        return string_t{};
    });
}

observable<string_t> VMSettings::doUpdateSingleUnit()
{
    return doUpdateUnitTo(USUNITFROM()).zip(doUpdatePartFrom(1), doUpdatePartTo(getPartCount())).map([](const auto&){
        return string_t{};
    });
}

observable<string_t> VMSettings::doUpdateUnitFrom(int v)
{
    USUNITFROM(v);
    return susersetting.updateObject(INFO_USUNITFROM, v).tap([&](const auto&){
        if (delegate) delegate->onUpdateUnitFrom();
    });
}

observable<string_t> VMSettings::doUpdatePartFrom(int v)
{
    USPARTFROM(v);
    return susersetting.updateObject(INFO_USPARTFROM, v).tap([&](const auto&){
        if (delegate) delegate->onUpdatePartFrom();
    });
}

observable<string_t> VMSettings::doUpdateUnitTo(int v)
{
    USUNITTO(v);
    return susersetting.updateObject(INFO_USUNITTO, v).tap([&](const auto&){
        if (delegate) delegate->onUpdateUnitTo();
    });
}

observable<string_t> VMSettings::doUpdatePartTo(int v)
{
    USPARTTO(v);
    return susersetting.updateObject(INFO_USPARTTO, v).tap([&](const auto&){
        if (delegate) delegate->onUpdatePartTo();
    });
}
