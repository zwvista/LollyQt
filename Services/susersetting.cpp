#include "susersetting.h"
#include <boost/format.hpp>

observable<vector<MUserSetting> > SUserSetting::getData(int userid)
{
    auto url = boost::wformat(L"USERSETTINGS?filter=USERID,eq,%1%") % userid;
    return apis.getObject(url.str()).map([](const MUserSettings& o){
        return o.records;
    });
}

observable<wstring> SUserSetting::updateObject(int id, const wstring &body)
{
    auto url = boost::wformat(L"USERSETTINGS/%1%") % id;
    return api.updateObject(url.str(), body);
}

observable<wstring> SUserSetting::updateObject(const MUserSettingInfo& info, int intValue)
{
    return updateObject(info, to_wstring(intValue));
}

observable<wstring> SUserSetting::updateObject(const MUserSettingInfo& info, const wstring& stringValue)
{
    wstring body;
    switch (info.VALUEID) {
    case 1: body = L"VALUE1=" + stringValue; break;
    case 2: body = L"VALUE2=" + stringValue; break;
    case 3: body = L"VALUE3=" + stringValue; break;
    case 4: body = L"VALUE4=" + stringValue; break;
    }
    return updateObject(info.USERSETTINGID, body);
}
