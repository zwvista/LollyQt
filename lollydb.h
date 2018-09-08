#ifndef LOLLYDB_H
#define LOLLYDB_H

#include <QtSql>

class LollyDB
{
public:
    LollyDB();
    ~LollyDB();
private:
    QSqlDatabase db;
};

#endif // LOLLYDB_H
