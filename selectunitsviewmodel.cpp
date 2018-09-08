#include "selectunitsviewmodel.h"

SelectUnitsViewModel::SelectUnitsViewModel()
{
    mdlUserSettings = new QSqlQueryModel;
    mdlLang = new QSqlQueryModel;
    mdlTextBook = new QSqlQueryModel;
}

void SelectUnitsViewModel::setQueryUserSettings()
{
    mdlUserSettings->setQuery("SELECT * FROM VUSERSETTINGS WHERE USERID = 1");
}

void SelectUnitsViewModel::setQueryLang()
{
    mdlLang->setQuery("SELECT * FROM VLANGUAGES WHERE ID > 0");
}

void SelectUnitsViewModel::setQueryTextbook(int langid)
{
    mdlTextBook->setQuery(QString("SELECT * FROM VTEXTBOOKS WHERE LANGID = %1").arg(langid));
}
