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
    virtual void onUpdateDictItem();
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
    MUserSettingInfo getUSInfo(const wstring& name);
    boost::optional<wstring> getUSValue(const MUserSettingInfo& info) const;
    void setUSValue(const MUserSettingInfo& info, const wstring& value);
    MUserSettingInfo INFO_USLANGID;
    int USLANGID() const { return stoi(getUSValue(INFO_USLANGID).get()); }
    void USLANGID(int value) { setUSValue(INFO_USLANGID, to_wstring(value)); }
    MUserSettingInfo INFO_USROWSPERPAGEOPTIONS;
    MUserSettingInfo INFO_USROWSPERPAGE;
    MUserSettingInfo INFO_USLEVELCOLORS;
    MUserSettingInfo INFO_USSCANINTERVAL;
    MUserSettingInfo INFO_USREVIEWINTERVAL;
    MUserSettingInfo INFO_USTEXTBOOKID;
    MUserSettingInfo INFO_USDICTITEM;
    MUserSettingInfo INFO_USDICTNOTEID;
    MUserSettingInfo INFO_USDICTITEMS;
    MUserSettingInfo INFO_USDICTTRANSLATIONID;
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
    SDictReference sdictreference;
    SDictNote sdictnote;
    SDictTranslation sdicttranslation;
    STextbook stextbook;
    SAutoCorrect sautocorrect;

    observable<wstring> doUpdateUnitPartFrom();
    observable<wstring> doUpdateUnitPartTo();
    observable<wstring> doUpdateSingleUnit();
    observable<wstring> doUpdateUnitFrom(int v);
    observable<wstring> doUpdatePartFrom(int v);
    observable<wstring> doUpdateUnitTo(int v);
    observable<wstring> doUpdatePartTo(int v);

public:
    vector<MUserSetting> userSettings;
    vector<int> getUSROWSPERPAGEOPTIONS() const;
    int USROWSPERPAGED() const { return stoi(getUSValue(INFO_USROWSPERPAGE).get()); }
    std::map<int, vector<wstring>> USLEVELCOLORS;
    int USSCANINTERVAL() const { return stoi(getUSValue(INFO_USSCANINTERVAL).get()); }
    int USREVIEWINTERVAL() const { return stoi(getUSValue(INFO_USREVIEWINTERVAL).get()); }
    int USTEXTBOOKID() const { return stoi(getUSValue(INFO_USTEXTBOOKID).get()); }
    void USTEXTBOOKID(int value) { setUSValue(INFO_USTEXTBOOKID, to_wstring(value)); }
    wstring USDICTITEM() const { return getUSValue(INFO_USDICTITEM).get(); }
    void USDICTITEM(const wstring& value) { setUSValue(INFO_USDICTITEM, value); }
    int USDICTNOTEID() const { return stoi(getUSValue(INFO_USDICTNOTEID).get_value_or(L"0")); }
    void USDICTNOTEID(int value) { setUSValue(INFO_USDICTNOTEID, to_wstring(value)); }
    wstring USDICTITEMS() const { return getUSValue(INFO_USDICTITEMS).get_value_or(L"0"); }
    void USDICTITEMS(const wstring& value) { setUSValue(INFO_USDICTITEMS, value); }
    int USDICTTRANSLATIONID() const { return stoi(getUSValue(INFO_USDICTTRANSLATIONID).get_value_or(L"0")); }
    void USDICTTRANSLATIONID(int value) { setUSValue(INFO_USDICTTRANSLATIONID, to_wstring(value)); }
    int USMACVOICEID() const { return stoi(getUSValue(INFO_USMACVOICEID).get_value_or(L"0")); }
    void USMACVOICEID(int value) { setUSValue(INFO_USMACVOICEID, to_wstring(value)); }
    int USUNITFROM() const { return stoi(getUSValue(INFO_USUNITFROM).get()); }
    void USUNITFROM(int value) { setUSValue(INFO_USUNITFROM, to_wstring(value)); }
    int USPARTFROM() const { return stoi(getUSValue(INFO_USPARTFROM).get()); }
    void USPARTFROM(int value) { setUSValue(INFO_USPARTFROM, to_wstring(value)); }
    int USUNITTO() const { return stoi(getUSValue(INFO_USUNITTO).get()); }
    void USUNITTO(int value) { setUSValue(INFO_USUNITTO, to_wstring(value)); }
    int USPARTTO() const { return stoi(getUSValue(INFO_USPARTTO).get()); }
    void USPARTTO(int value) { setUSValue(INFO_USPARTTO, to_wstring(value)); }
    int USUNITPARTFROM() const { return USUNITFROM() * 10 + USPARTFROM(); }
    int USUNITPARTTO() const { return USUNITTO() * 10 + USPARTTO(); }
    bool isSingleUnitPart() const { return USUNITPARTFROM() == USUNITPARTTO(); }
    bool isInvalidUnitPart() const { return USUNITPARTFROM() > USUNITPARTTO(); }

    vector<MLanguage> languages;
    int selectedLangIndex = 0;
    const MLanguage& selectedLang() const { return languages[selectedLangIndex]; }
    observable<wstring> setSelectedLang(int langIndex);
    vector<MVoice> macVoices;
    int selectedMacVoiceIndex = 0;
    const MVoice& selectedMacVoice() const { return macVoices[selectedMacVoiceIndex]; }
    void setSelectedMacVoice(int index);
    vector<MDictReference> dictsReference;
    vector<MDictItem> dictItems;
    int selectedDictItemIndex = 0;
    const MDictItem& selectedDictItem() const { return dictItems[selectedDictItemIndex]; }
    void setSelectedDictItem(int index);
    vector<MDictNote> dictsNote;
    int selectedDictNoteIndex = 0;
    const MDictNote& selectedDictNote() const { return dictsNote[selectedDictNoteIndex]; }
    void setSelectedDictNote(int index);
    vector<MDictTranslation> dictsTranslation;
    int selectedDictTranslationIndex = 0;
    const MDictTranslation& selectedDictTranslation() const { return dictsTranslation[selectedDictTranslationIndex]; }
    void setSelectedDictTranslation(int index);
    vector<MTextbook> textbooks;
    int selectedTextbookIndex = 0;
    const MTextbook& selectedTextbook() const { return textbooks[selectedTextbookIndex]; }
    void setSelectedTextbook(int index);

    const vector<MSelectItem>& getUnits() const { return selectedTextbook().units; }
    int getUnitCount() const { return getUnits().size(); }
    wstring getUnitsInAll() const { return (boost::wformat(L"(%1% in all)") % getUnitCount()).str(); }
    const vector<MSelectItem>& getParts() const { return selectedTextbook().parts; }
    int getPartCount() const { return getParts().size(); }
    bool isSingleUnit() const { return USUNITFROM() == USUNITTO() && USPARTFROM() == 1 && USPARTTO() == getPartCount(); }
    bool isSinglePart() const { return getPartCount() == 1; }

    vector<MAutoCorrect> autoCorrects;
    vector<MDictType> dictTypes;
    vector<wstring> toTypes = { L"Unit", L"Part", L"To" };
    UnitPartToType toType = UnitPartToType::PART;
    VMSettingsDelegate* delegate = nullptr;

    observable<wstring> getData();
    observable<wstring> updateLang();
    observable<wstring> updateDictItem();
    observable<wstring> updateDictNote();
    observable<wstring> updateDictTranslation();
    observable<wstring> updateTextbook();
    observable<wstring> updateMacVoice();
    wstring autoCorrectInput(const wstring& text);
    observable<wstring> updateUnitFrom();
    observable<wstring> updatePartFrom();
    observable<wstring> updateUnitTo();
    observable<wstring> updatePartTo();
    observable<wstring> updateToType();
    observable<wstring> previousUnitPart();
    observable<wstring> nextUnitPart();
};

extern VMSettings vmSettings;

#endif // VMSETTINGS_H
