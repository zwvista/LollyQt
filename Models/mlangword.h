#ifndef MLANGWORD_H
#define MLANGWORD_H

#include "mcommon.h"

struct MLangWord
{
    int ID = 0;
    int LANGID = 0;
    string WORD;
    boost::optional<string> NOTE;
    int FAMIID = 0;
    int LEVEL = 0;
    int CORRECT = 0;
    int TOTAL = 0;
};

struct MLangWords
{
    vector<MLangWord> records;
};

void to_json(json& j, const MLangWord& p);
void from_json(const json& j, MLangWord& p);
void from_json(const json& j, MLangWords& p);

#endif // MLANGWORD_H
