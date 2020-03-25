#ifndef MTEXTBOOK_H
#define MTEXTBOOK_H

#include "mcommon.h"
#include "mselectitem.h"

struct MTextbook
{
    int ID = 0;
    int LANGID = 0;
    wstring TEXTBOOKNAME;
    wstring UNITS;
    wstring PARTS;

    vector<MSelectItem> units;
    vector<MSelectItem> parts;

    wstring UNITSTR(int unit) const;
    wstring PARTSTR(int part) const;
};

struct MTextbooks
{
    vector<MTextbook> records;
};

void to_json(json& j, const MTextbook& p);
void from_json(const json& j, MTextbook& p);
void from_json(const json& j, MTextbooks& p);

#endif // MTEXTBOOK_H
