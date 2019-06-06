#ifndef MLANGUAGE_H
#define MLANGUAGE_H

#include "mcommon.h"

struct MLanguage
{
    int ID = 0;
    string LANGNAME;
};

struct MLanguages
{
    vector<MLanguage> records;
};

void to_json(json& j, const MLanguage& p);
void from_json(const json& j, MLanguage& p);
void from_json(const json& j, MLanguages& p);

#endif // MLANGUAGE_H
