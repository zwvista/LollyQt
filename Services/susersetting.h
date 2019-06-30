#ifndef SUSERSETTING_H
#define SUSERSETTING_H

#include "Helpers/restapi.h"
#include "Models/musersetting.h"

struct SUserSetting
{
    observable<vector<MUserSetting>> getData(int userid);
    observable<string> updateObject(int id, const string& body);
    observable<string> updateObject(const MUserSettingInfo& info, int intValue);
    observable<string> updateObject(const MUserSettingInfo& info, const string& stringValue);

    RestApi<MUserSettings> apis;
    RestApi<MUserSetting> api;
};

#endif // SUSERSETTING_H
