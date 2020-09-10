#ifndef MWORDFAMI_H
#define MWORDFAMI_H

#include "mcommon.h"

struct MWordFami
{
    int ID = 0;
    int USERID = 0;
    int WORDID = 0;
    int CORRECT = 0;
    int TOTAL = 0;
};

struct MWordsFami
{
    vector<MWordFami> records;
};

void to_json(json& j, const MWordFami& p);
void from_json(const json& j, MWordFami& p);
void from_json(const json& j, MWordsFami& p);

#endif // MWORDFAMI_H
