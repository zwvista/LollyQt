#include "susersetting.h"
#include <boost/format.hpp>

observable<vector<MUserSetting> > SUserSetting::getData(int userid)
{
    auto url = boost::format_t(_XPLATSTR("USERSETTINGS?filter=USERID,eq,%1%")) % userid;
    return apis.getObject(url.str()).map([](const MUserSettings& o){
        return o.records;
    });
}

observable<string_t> SUserSetting::updateObject(int id, const string_t &body)
{
    auto url = boost::format_t(_XPLATSTR("USERSETTINGS/%1%")) % id;
    return api.updateObject(url.str(), body);
}

observable<string_t> SUserSetting::updateObject(const MUserSettingInfo& info, int intValue)
{
    return updateObject(info, to_string_t(intValue));
}

observable<string_t> SUserSetting::updateObject(const MUserSettingInfo& info, const string_t& stringValue)
{
    string_t body;
    switch (info.VALUEID) {
    case 1: body = _XPLATSTR("VALUE1=") + stringValue; break;
    case 2: body = _XPLATSTR("VALUE2=") + stringValue; break;
    case 3: body = _XPLATSTR("VALUE3=") + stringValue; break;
    case 4: body = _XPLATSTR("VALUE4=") + stringValue; break;
    }
    return updateObject(info.USERSETTINGID, body);
}
