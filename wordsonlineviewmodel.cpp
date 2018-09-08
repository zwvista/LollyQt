#include "wordsonlineviewmodel.h"

WordsOnlineViewModel::WordsOnlineViewModel()
{
    mdlLang = new QSqlQueryModel;
    mdlDict = new QSqlQueryModel;
}

void WordsOnlineViewModel::setQueryLang()
{
    mdlLang->setQuery("SELECT ID, NAME FROM LANGUAGES WHERE ID > 0");
}

void WordsOnlineViewModel::setQueryDict(int langid)
{
    mdlDict->setQuery(QString("SELECT DICTNAME, URL FROM VDICTIONARIES WHERE LANGIDFROM = %1").arg(langid));
}
