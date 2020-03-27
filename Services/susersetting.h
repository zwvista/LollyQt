#ifndef SUSERSETTING_H
#define SUSERSETTING_H

#include "Helpers/restapi.h"
#include "Models/musersetting.h"

struct SUserSetting
{
    observable<vector<MUserSetting>> getData(int userid);
    observable<string_t> updateObject(int id, const string_t& body);
    observable<string_t> updateObject(const MUserSettingInfo& info, int intValue);
    observable<string_t> updateObject(const MUserSettingInfo& info, const string_t& stringValue);

    RestApi<MUserSettings> apis;
    RestApi<MUserSetting> api;
};

#endif // SUSERSETTING_H
