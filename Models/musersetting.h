#ifndef MUSERSETTING_H
#define MUSERSETTING_H

#include "mcommon.h"

struct MUserSetting
{
    int ID = 0;
    int USERID = 0;
    int KIND = 0;
    int ENTITYID = 0;
    boost::optional<string> VALUE1;
    boost::optional<string> VALUE2;
    boost::optional<string> VALUE3;
    boost::optional<string> VALUE4;
};

struct MUserSettings
{
    vector<MUserSetting> records;
};

void to_json(json& j, const MUserSetting& p);
void from_json(const json& j, MUserSetting& p);
void from_json(const json& j, MUserSettings& p);

#endif // MUSERSETTING_H
