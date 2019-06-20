#ifndef SELECTUNITSVIEWMODEL_H
#define SELECTUNITSVIEWMODEL_H

#include <QtSql>

class SelectUnitsViewModel
{
public:
    SelectUnitsViewModel();

    void setQueryUserSettings();
    void setQueryLang();
    void setQueryTextbook(int langid);

    QSqlQueryModel *mdlUserSettings, *mdlLang, *mdlTextBook;
};

#endif // SELECTUNITSVIEWMODEL_H
