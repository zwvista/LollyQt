#ifndef MUNITWORD_H
#define MUNITWORD_H

#include "Shared/commonapi.h"
#include "mtextbook.h"

struct MUnitWord
{
    int ID = 0;
    int LANGID = 0;
    int TEXTBOOKID = 0;
    wstring TEXTBOOKNAME;
    int UNIT = 0;
    int PART = 0;
    int SEQNUM = 0;
    int WORDID = 0;
    wstring WORD;
    boost::optional<wstring> NOTE;
    int FAMIID = 0;
    int LEVEL = 0;
    int CORRECT = 0;
    int TOTAL = 0;

    const MTextbook *pTextbook = nullptr;

    wstring UNITSTR() const { return pTextbook->UNITSTR(UNIT); }
    wstring PARTSTR() const { return pTextbook->PARTSTR(PART); }
    wstring ACCURACY() const { return CommonApi::getAccuracy(CORRECT, TOTAL); }
};

struct MUnitWords
{
    vector<MUnitWord> records;
};

void to_json(json& j, const MUnitWord& p);
void from_json(const json& j, MUnitWord& p);
void from_json(const json& j, MUnitWords& p);

#endif // MUNITWORD_H
