#ifndef VMSETTINGS_H
#define VMSETTINGS_H

#include <vector>
#include <map>
#include "Models/musersetting.h"
#include "Models/mlanguage.h"
#include "Models/mvoice.h"
#include "Models/mdictionary.h"
#include "Models/mtextbook.h"
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
    MDictItem* selectedDictItem = nullptr;
    MDictNote* selectedDictNote = nullptr;
    MDictTranslation* selectedDictTranslation = nullptr;
    MTextbook* selectedTextbook = nullptr;
public:
    vector<MUserSetting> userSettings;
    vector<int> getUSROWSPERPAGEOPTIONS() const;
    int getUSROWSPERPAGED() const { return stoi(selectedUSUser0->VALUE3.get()); }
    map<int, vector<string>> USLEVELCOLORS;
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
    MLanguage* selectedLang = nullptr;
    vector<MVoice> macVoices;
    MVoice* selectedMacVoice = nullptr;
    vector<MDictReference> dictsReference;
    vector<MDictItem> dictItems;
    MDictItem* getSelectedDictItem() { return selectedDictItem; }
    void setSelectedDictItem(MDictItem* value) {
        selectedDictItem = value;
        setUSDICTITEM(value->DICTID);
    }
    vector<MDictNote> dictsNote;
    MDictNote* getSelectedDictNote() { return selectedDictNote; }
    void setSelectedDictNote(MDictNote* value) {
        selectedDictNote = value;
        setUSDICTNOTEID(value->DICTID);
    }
    vector<MDictTranslation> dictsTranslation;
    MDictTranslation* getSelectedDictTranslation() { return selectedDictTranslation; }
    void setSelectedDictTranslation(MDictTranslation* value) {
        selectedDictTranslation = value;
        setUSDICTTRANSLATIONID(value->DICTID);
    }
    vector<MTextbook> textbooks;
    MTextbook* getSelectedTextbook() { return selectedTextbook; }
    void setSelectedTextbook(MTextbook* value) {
        selectedTextbook = value;
        setUSTEXTBOOKID(value->ID);
    }
};

#endif // VMSETTINGS_H
