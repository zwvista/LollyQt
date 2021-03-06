#ifndef MUSERSETTING_H
#define MUSERSETTING_H

#include "mcommon.h"

struct MUserSetting
{
    int ID = 0;
    int USERID = 0;
    int KIND = 0;
    int ENTITYID = 0;
    boost::optional<string_t> VALUE1;
    boost::optional<string_t> VALUE2;
    boost::optional<string_t> VALUE3;
    boost::optional<string_t> VALUE4;
};

struct MUserSettings
{
    vector<MUserSetting> records;
};

void to_json(json& j, const MUserSetting& p);
void from_json(const json& j, MUserSetting& p);
void from_json(const json& j, MUserSettings& p);

struct MUserSettingInfo
{
    int USERSETTINGID = 0;
    int VALUEID = 0;
};

#endif // MUSERSETTING_H
