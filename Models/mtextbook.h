#ifndef MTEXTBOOK_H
#define MTEXTBOOK_H

#include "mcommon.h"

struct MTextbook
{
    int ID = 0;
    int LANGID = 0;
    string TEXTBOOKNAME;
    string UNITS;
    string PARTS;
};

struct MTextbooks
{
    vector<MTextbook> records;
};

#endif // MTEXTBOOK_H
