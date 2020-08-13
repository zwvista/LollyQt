#include "lollydb.h"

LollyDB::LollyDB()
{
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(R"(C:\zw\backup\LollyDB\LollyCore.db)");
//    db.setDatabaseName("/Users/zhaowei/Documents/Programs/Lolly/LollyDB/LollyCore.db");
//    db.setDatabaseName(R"(E:\Education\Lolly\Lolly.db)");
//    if(!db.open()){
//        qDebug() << db.lastError();
//        qFatal("Failed to connect.");
//    }
}

LollyDB::~LollyDB()
{
    db.close();
}
