#ifndef VMSETTINGS_H
#define VMSETTINGS_H

#include <vector>
#include <map>
#include "Services/susmapping.h"
#include "Services/susersetting.h"
#include "Services/sautocorrect.h"
#include "Services/sdictionary.h"
#include "Services/slanguage.h"
#include "Services/stextbook.h"
#include "Services/svoice.h"
#include "Helpers/restapi.h"
#include "Shared/commonapi.h"
#include <boost/format.hpp>
using namespace std;

struct VMSettingsDelegate
{
    virtual ~VMSettingsDelegate();
    virtual void onGetData();
    virtual void onUpdateLang();
    virtual void onUpdateDictReference();
    virtual void onUpdateDictNote();
    virtual void onUpdateDictTranslation();
    virtual void onUpdateTextbook();
    virtual void onUpdateUnitFrom();
    virtual void onUpdatePartFrom();
    virtual void onUpdateUnitTo();
    virtual void onUpdatePartTo();
    virtual void onUpdateMacVoice();
};

class VMSettings
{
    vector<MUSMapping> usmappings;
    MUserSettingInfo getUSInfo(const string_t& name);
    boost::optional<string_t> getUSValue(const MUserSettingInfo& info) const;
    void setUSValue(const MUserSettingInfo& info, const string_t& value);
    MUserSettingInfo INFO_USLANGID;
    int USLANGID() const { return stoi(getUSValue(INFO_USLANGID).get()); }
    void USLANGID(int value) { setUSValue(INFO_USLANGID, to_string_t(value)); }
    MUserSettingInfo INFO_USROWSPERPAGEOPTIONS;
    MUserSettingInfo INFO_USROWSPERPAGE;
    MUserSettingInfo INFO_USLEVELCOLORS;
    MUserSettingInfo INFO_USSCANINTERVAL;
    MUserSettingInfo INFO_USREVIEWINTERVAL;
    MUserSettingInfo INFO_USTEXTBOOKID;
    MUserSettingInfo INFO_USDICTREFERENCE;
    MUserSettingInfo INFO_USDICTNOTE;
    MUserSettingInfo INFO_USDICTSREFERENCE;
    MUserSettingInfo INFO_USDICTTRANSLATION;
    MUserSettingInfo INFO_USMACVOICEID;
    MUserSettingInfo INFO_USUNITFROM;
    MUserSettingInfo INFO_USPARTFROM;
    MUserSettingInfo INFO_USUNITTO;
    MUserSettingInfo INFO_USPARTTO;

    SLanguage slanguage;
    SUSMapping susmapping;
    SUserSetting susersetting;
    SDictType sdicttype;
    SVoice svoice;
    SDictionary sdictionary;
    STextbook stextbook;
    SAutoCorrect sautocorrect;

    observable<string_t> doUpdateUnitPartFrom();
    observable<string_t> doUpdateUnitPartTo();
    observable<string_t> doUpdateSingleUnit();
    observable<string_t> doUpdateUnitFrom(int v);
    observable<string_t> doUpdatePartFrom(int v);
    observable<string_t> doUpdateUnitTo(int v);
    observable<string_t> doUpdatePartTo(int v);

public:
    vector<MUserSetting> userSettings;
    vector<int> getUSROWSPERPAGEOPTIONS() const;
    int USROWSPERPAGED() const { return stoi(getUSValue(INFO_USROWSPERPAGE).get()); }
    std::map<int, vector<string_t>> USLEVELCOLORS;
    int USSCANINTERVAL() const { return stoi(getUSValue(INFO_USSCANINTERVAL).get()); }
    int USREVIEWINTERVAL() const { return stoi(getUSValue(INFO_USREVIEWINTERVAL).get()); }
    int USTEXTBOOKID() const { return stoi(getUSValue(INFO_USTEXTBOOKID).get()); }
    void USTEXTBOOKID(int value) { setUSValue(INFO_USTEXTBOOKID, to_string_t(value)); }
    string_t USDICTREFERENCE() const { return getUSValue(INFO_USDICTREFERENCE).get(); }
    void USDICTREFERENCE(const string_t& value) { setUSValue(INFO_USDICTREFERENCE, value); }
    int USDICTNOTE() const { return stoi(getUSValue(INFO_USDICTNOTE).get_value_or(_XPLATSTR("0"))); }
    void USDICTNOTE(int value) { setUSValue(INFO_USDICTNOTE, to_string_t(value)); }
    string_t USDICTSREFERENCE() const { return getUSValue(INFO_USDICTSREFERENCE).get_value_or(_XPLATSTR("0")); }
    void USDICTSREFERENCE(const string_t& value) { setUSValue(INFO_USDICTSREFERENCE, value); }
    int USDICTTRANSLATION() const { return stoi(getUSValue(INFO_USDICTTRANSLATION).get_value_or(_XPLATSTR("0"))); }
    void USDICTTRANSLATION(int value) { setUSValue(INFO_USDICTTRANSLATION, to_string_t(value)); }
    int USMACVOICEID() const { return stoi(getUSValue(INFO_USMACVOICEID).get_value_or(_XPLATSTR("0"))); }
    void USMACVOICEID(int value) { setUSValue(INFO_USMACVOICEID, to_string_t(value)); }
    int USUNITFROM() const { return stoi(getUSValue(INFO_USUNITFROM).get()); }
    void USUNITFROM(int value) { setUSValue(INFO_USUNITFROM, to_string_t(value)); }
    int USPARTFROM() const { return stoi(getUSValue(INFO_USPARTFROM).get()); }
    void USPARTFROM(int value) { setUSValue(INFO_USPARTFROM, to_string_t(value)); }
    int USUNITTO() const { return stoi(getUSValue(INFO_USUNITTO).get()); }
    void USUNITTO(int value) { setUSValue(INFO_USUNITTO, to_string_t(value)); }
    int USPARTTO() const { return stoi(getUSValue(INFO_USPARTTO).get()); }
    void USPARTTO(int value) { setUSValue(INFO_USPARTTO, to_string_t(value)); }
    int USUNITPARTFROM() const { return USUNITFROM() * 10 + USPARTFROM(); }
    int USUNITPARTTO() const { return USUNITTO() * 10 + USPARTTO(); }
    bool isSingleUnitPart() const { return USUNITPARTFROM() == USUNITPARTTO(); }
    bool isInvalidUnitPart() const { return USUNITPARTFROM() > USUNITPARTTO(); }

    vector<MLanguage> languages;
    int selectedLangIndex = 0;
    const MLanguage& selectedLang() const { return languages[selectedLangIndex]; }
    observable<string_t> setSelectedLang(int langIndex);
    vector<MVoice> macVoices;
    int selectedMacVoiceIndex = 0;
    const MVoice& selectedMacVoice() const { return macVoices[selectedMacVoiceIndex]; }
    void setSelectedMacVoice(int index);
    vector<MDictionary> dictsReference;
    int selectedDictReferenceIndex = 0;
    const MDictionary& selectedDictReference() const { return dictsReference[selectedDictReferenceIndex]; }
    void setSelectedDictReference(int index);
    vector<MDictionary> dictsNote;
    int selectedDictNoteIndex = 0;
    const MDictionary& selectedDictNote() const { return dictsNote[selectedDictNoteIndex]; }
    void setSelectedDictNote(int index);
    vector<MDictionary> dictsTranslation;
    int selectedDictTranslationIndex = 0;
    const MDictionary& selectedDictTranslation() const { return dictsTranslation[selectedDictTranslationIndex]; }
    void setSelectedDictTranslation(int index);
    vector<MTextbook> textbooks;
    int selectedTextbookIndex = 0;
    const MTextbook& selectedTextbook() const { return textbooks[selectedTextbookIndex]; }
    void setSelectedTextbook(int index);

    const vector<MSelectItem>& getUnits() const { return selectedTextbook().units; }
    int getUnitCount() const { return getUnits().size(); }
    string_t getUnitsInAll() const { return (boost::format_t(_XPLATSTR("(%1% in all)")) % getUnitCount()).str(); }
    const vector<MSelectItem>& getParts() const { return selectedTextbook().parts; }
    int getPartCount() const { return getParts().size(); }
    bool isSingleUnit() const { return USUNITFROM() == USUNITTO() && USPARTFROM() == 1 && USPARTTO() == getPartCount(); }
    bool isSinglePart() const { return getPartCount() == 1; }

    vector<MAutoCorrect> autoCorrects;
    vector<MDictType> dictTypes;
    vector<string_t> toTypes = { _XPLATSTR("Unit"), _XPLATSTR("Part"), _XPLATSTR("To") };
    UnitPartToType toType = UnitPartToType::PART;
    VMSettingsDelegate* delegate = nullptr;

    observable<string_t> getData();
    observable<string_t> updateLang();
    observable<string_t> updateDictReference();
    observable<string_t> updateDictNote();
    observable<string_t> updateDictTranslation();
    observable<string_t> updateTextbook();
    observable<string_t> updateMacVoice();
    string_t autoCorrectInput(const string_t& text);
    observable<string_t> updateUnitFrom();
    observable<string_t> updatePartFrom();
    observable<string_t> updateUnitTo();
    observable<string_t> updatePartTo();
    observable<string_t> updateToType();
    observable<string_t> previousUnitPart();
    observable<string_t> nextUnitPart();
};

extern VMSettings vmSettings;

#endif // VMSETTINGS_H
