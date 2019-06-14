#include "susersetting.h"
#include <boost/format.hpp>

observable<vector<MUserSetting> > SUserSetting::getData(int userid)
{
    auto url = boost::format("USERSETTINGS?filter=USERID,eq,%1%") % userid;
    return apis.getObject(url.str()).map([](const MUserSettings& o){
        return o.records;
    });
}

observable<string> SUserSetting::updateObject(int id, const string &body)
{
    auto url = boost::format("USERSETTINGS/%1%") % id;
    return api.updateObject(url.str(), body);
}

observable<string> SUserSetting::updateLang(int id, int langid)
{
    auto body = boost::format("VALUE1=%1%") % langid;
    return updateObject(id, body.str());
}

observable<string> SUserSetting::updateTextbook(int id, int textbookid)
{
    auto body = boost::format("VALUE1=%1%") % textbookid;
    return updateObject(id, body.str());
}

observable<string> SUserSetting::updateDictItem(int id, const string &dictitem)
{
    auto body = boost::format("VALUE2=%1%") % dictitem;
    return updateObject(id, body.str());
}

observable<string> SUserSetting::updateDictNote(int id, int dictnoteid)
{
    auto body = boost::format("VALUE3=%1%") % dictnoteid;
    return updateObject(id, body.str());
}

observable<string> SUserSetting::updateDictTranslation(int id, int dicttranslationid)
{
    auto body = boost::format("VALUE1=%1%") % dicttranslationid;
    return updateObject(id, body.str());
}

observable<string> SUserSetting::updateUnitFrom(int id, int unitfrom)
{
    auto body = boost::format("VALUE1=%1%") % unitfrom;
    return updateObject(id, body.str());
}

observable<string> SUserSetting::updatePartFrom(int id, int partfrom)
{
    auto body = boost::format("VALUE2=%1%") % partfrom;
    return updateObject(id, body.str());
}

observable<string> SUserSetting::updateUnitTo(int id, int unitto)
{
    auto body = boost::format("VALUE3=%1%") % unitto;
    return updateObject(id, body.str());
}

observable<string> SUserSetting::updatePartTo(int id, int partto)
{
    auto body = boost::format("VALUE4=%1%") % partto;
    return updateObject(id, body.str());
}

observable<string> SUserSetting::updateMacVoice(int id, int voiceid)
{
    auto body = boost::format("VALUE2=%1%") % voiceid;
    return updateObject(id, body.str());
}
