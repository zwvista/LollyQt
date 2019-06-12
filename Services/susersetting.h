#ifndef SUSERSETTING_H
#define SUSERSETTING_H

#include "Helpers/restapi.h"
#include "Models/musersetting.h"

struct SUserSetting
{
    observable<vector<MUserSetting>> getData(int userid);
    observable<string> updateObject(int id, const string& body);
    observable<string> updateLang(int id, int langid);
    observable<string> updateTextbook(int id, int textbookid);
    observable<string> updateDictItem(int id, const string& dictitem);
    observable<string> updateDictNote(int id, int dictnoteid);
    observable<string> updateDictTranslation(int id, int dicttranslationid);
    observable<string> updateUnitFrom(int id, int unitfrom);
    observable<string> updatePartFrom(int id, int partfrom);
    observable<string> updateUnitTo(int id, int unitto);
    observable<string> updatePartTo(int id, int partto);
    observable<string> updateVoice(int id, int voiceid);

    RestApi<MUserSettings> apis;
    RestApi<MUserSetting> api;
};

#endif // SUSERSETTING_H
