#ifndef VMSETTINGS_H
#define VMSETTINGS_H

#include <vector>
#include <map>
#include "Services/susersetting.h"
#include "Services/sautocorrect.h"
#include "Services/sdictionary.h"
#include "Services/slanguage.h"
#include "Services/stextbook.h"
#include "Services/svoice.h"
#include "Helpers/restapi.h"
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
    MUserSetting* selectedUSUser0 = nullptr;
    MUserSetting* selectedUSUser1 = nullptr;
    int getUSLANGID() const { return stoi(selectedUSUser0->VALUE1.get()); }
    void setUSLANGID(int value) const { selectedUSUser0->VALUE1 = to_string(value); }
    MUserSetting* selectedUSLang2 = nullptr;
    MUserSetting* selectedUSLang3 = nullptr;
    MUserSetting* selectedUSTextbook = nullptr;

    SLanguage slanguage;
    SUserSetting susersetting;
    SDictType sdicttype;
    SVoice svoice;
    SDictReference sdictreference;
    SDictNote sdictnote;
    SDictTranslation sdicttranslation;
    STextbook stextbook;
    SAutoCorrect sautocorrect;
public:
    vector<MUserSetting> userSettings;
    vector<int> getUSROWSPERPAGEOPTIONS() const;
    int getUSROWSPERPAGED() const { return stoi(selectedUSUser0->VALUE3.get()); }
    std::map<int, vector<string>> USLEVELCOLORS;
    int getUSREADINTERVAL() const { return stoi(selectedUSUser1->VALUE1.get()); }
    int getUSREVIEWINTERVAL() const { return stoi(selectedUSUser1->VALUE2.get()); }
    int getUSTEXTBOOKID() const { return stoi(selectedUSLang2->VALUE1.get()); }
    void setUSTEXTBOOKID(int value) const { selectedUSLang2->VALUE1 = to_string(value); }
    string getUSDICTITEM() const { return selectedUSLang2->VALUE2.get(); }
    void setUSDICTITEM(const string& value) const { selectedUSLang2->VALUE2 = value; }
    int getUSDICTNOTEID() const { return stoi(selectedUSLang2->VALUE3.get_value_or("0")); }
    void setUSDICTNOTEID(int value) const { selectedUSLang2->VALUE3 = to_string(value); }
    string getUSDICTITEMS() const { return selectedUSLang2->VALUE4.get_value_or("0"); }
    void setUSDICTITEMS(const string& value) const { selectedUSLang2->VALUE4 = value; }
    int getUSDICTTRANSLATIONID() const { return stoi(selectedUSLang3->VALUE1.get_value_or("0")); }
    void setUSDICTTRANSLATIONID(int value) const { selectedUSLang3->VALUE1 = to_string(value); }
    int getUSMACVOICEID() const { return stoi(selectedUSLang3->VALUE2.get_value_or("0")); }
    void setUSMACVOICEID(int value) const { selectedUSLang3->VALUE2 = to_string(value); }
    int getUSUNITFROM() const { return stoi(selectedUSTextbook->VALUE1.get()); }
    void setUSUNITFROM(int value) const { selectedUSTextbook->VALUE1 = to_string(value); }
    int getUSPARTFROM() const { return stoi(selectedUSTextbook->VALUE2.get()); }
    void setUSPARTFROM(int value) const { selectedUSTextbook->VALUE2 = to_string(value); }
    int getUSUNITTO() const { return stoi(selectedUSTextbook->VALUE3.get()); }
    void setUSUNITTO(int value) const { selectedUSTextbook->VALUE3 = to_string(value); }
    int getUSPARTTO() const { return stoi(selectedUSTextbook->VALUE4.get()); }
    void setUSPARTTO(int value) const { selectedUSTextbook->VALUE4 = to_string(value); }
    vector<MLanguage> languages;
    int selectedLangIndex = 0;
    const MLanguage& getSelectedLang() const { return languages[selectedLangIndex]; }
    observable<string> setSelectedLang(int langIndex);
    vector<MVoice> macVoices;
    int selectedMacVoiceIndex = 0;
    const MVoice& getSelectedMacVoice() const { return macVoices[selectedMacVoiceIndex]; }
    void setSelectedMacVoice(int index);
    vector<MDictReference> dictsReference;
    vector<MDictItem> dictItems;
    int selectedDictItemIndex = 0;
    const MDictItem& getSelectedDictItem() const { return dictItems[selectedDictItemIndex]; }
    void setSelectedDictItem(int index);
    vector<MDictNote> dictsNote;
    int selectedDictNoteIndex = 0;
    const MDictNote& getSelectedDictNote() const { return dictsNote[selectedDictNoteIndex]; }
    void setSelectedDictNote(int index);
    vector<MDictTranslation> dictsTranslation;
    int selectedDictTranslationIndex = 0;
    const MDictTranslation& getSelectedDictTranslation() const { return dictsTranslation[selectedDictTranslationIndex]; }
    void setSelectedDictTranslation(int index);
    vector<MTextbook> textbooks;
    int selectedTextbookIndex = 0;
    const MTextbook& getSelectedTextbook() const { return textbooks[selectedTextbookIndex]; }
    void setSelectedTextbook(int index);

    const vector<MSelectItem>& getUnits() const { return getSelectedTextbook().units; }
    int getUnitCount() const { return getUnits().size(); }
    string getUnitsInAll() const { return (boost::format("(%1% in all)") % getUnitCount()).str(); }
    const vector<MSelectItem>& getParts() const { return getSelectedTextbook().parts; }
    int getPartCount() const { return getParts().size(); }
    bool isSingleUnit() const { return getUSUNITFROM() == getUSUNITTO() && getUSPARTFROM() == 1 && getUSPARTTO() == getPartCount(); }
    bool isSinglePart() const { return getPartCount() == 1; }

    vector<MAutoCorrect> autoCorrects;
    vector<MDictType> dictTypes;
    vector<string> toTypes = { "Unit", "Part", "To" };
    VMSettingsDelegate* delegate = nullptr;

    observable<string> getData();
    observable<string> updateLang();
    observable<string> updateDictItem();
    observable<string> updateDictNote();
    observable<string> updateDictTranslation();
    observable<string> updateTextbook();
    observable<string> updateMacVoice();
};

#endif // VMSETTINGS_H
