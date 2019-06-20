#ifndef WORDSONLINEVIEWMODEL_H
#define WORDSONLINEVIEWMODEL_H

#include <QtSql>

class WordsOnlineViewModel
{
public:
    WordsOnlineViewModel();

    void setQueryLang();
    void setQueryDict(int langid);

    QSqlQueryModel *mdlLang, *mdlDict;
};

#endif // WORDSONLINEVIEWMODEL_H
