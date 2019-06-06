#ifndef MTEXTBOOK_H
#define MTEXTBOOK_H

#include "mcommon.h"
#include "mselectitem.h"

struct MTextbook
{
    int ID = 0;
    int LANGID = 0;
    string TEXTBOOKNAME;
    string UNITS;
    string PARTS;

    vector<MSelectItem> units;
    vector<MSelectItem> parts;
};

struct MTextbooks
{
    vector<MTextbook> records;
};

#endif // MTEXTBOOK_H
