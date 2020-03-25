#ifndef SUSERSETTING_H
#define SUSERSETTING_H

#include "Helpers/restapi.h"
#include "Models/musersetting.h"

struct SUserSetting
{
    observable<vector<MUserSetting>> getData(int userid);
    observable<wstring> updateObject(int id, const wstring& body);
    observable<wstring> updateObject(const MUserSettingInfo& info, int intValue);
    observable<wstring> updateObject(const MUserSettingInfo& info, const wstring& stringValue);

    RestApi<MUserSettings> apis;
    RestApi<MUserSetting> api;
};

#endif // SUSERSETTING_H
