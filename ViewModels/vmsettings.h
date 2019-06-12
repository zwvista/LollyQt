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
using namespace std;

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
    SVoice svoice;
    SDictReference sdictreference;
    SDictNote sdictnote;
    SDictTranslation sdicttranslation;
    STextbook stextbook;
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
    void setSelectedMacVoice(int index) {
        selectedMacVoiceIndex = index;
        setUSMACVOICEID(getSelectedMacVoice().ID);
    }
    vector<MDictReference> dictsReference;
    vector<MDictItem> dictItems;
    int selectedDictItemIndex = 0;
    const MDictItem& getSelectedDictItem() const { return dictItems[selectedDictItemIndex]; }
    void setSelectedDictItem(int index) {
        selectedDictItemIndex = index;
        setUSDICTITEM(getSelectedDictItem().DICTID);
    }
    vector<MDictNote> dictsNote;
    int selectedDictNoteIndex = 0;
    const MDictNote& getSelectedDictNote() const { return dictsNote[selectedDictNoteIndex]; }
    void setSelectedDictNote(int index) {
        selectedDictNoteIndex = index;
        setUSDICTNOTEID(getSelectedDictNote().DICTID);
    }
    vector<MDictTranslation> dictsTranslation;
    int selectedDictTranslationIndex = 0;
    const MDictTranslation& getSelectedDictTranslation() const { return dictsTranslation[selectedDictTranslationIndex]; }
    void setSelectedDictTranslation(int index) {
        selectedDictTranslationIndex = index;
        setUSDICTTRANSLATIONID(getSelectedDictTranslation().DICTID);
    }
    vector<MTextbook> textbooks;
    int selectedTextbookIndex = 0;
    const MTextbook& getSelectedTextbook() const { return textbooks[selectedTextbookIndex]; }
    void setSelectedTextbook(int index) {
        selectedTextbookIndex = index;
        setUSTEXTBOOKID(getSelectedTextbook().ID);
    }

    observable<string> getData();
};

#endif // VMSETTINGS_H
