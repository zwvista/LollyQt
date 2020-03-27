#ifndef MLANGPHRASE_H
#define MLANGPHRASE_H

#include "mcommon.h"

struct MLangPhrase
{
    int ID = 0;
    int LANGID = 0;
    string_t PHRASE;
    boost::optional<string_t> TRANSLATION;
};

struct MLangPhrases
{
    vector<MLangPhrase> records;
};

void to_json(json& j, const MLangPhrase& p);
void from_json(const json& j, MLangPhrase& p);
void from_json(const json& j, MLangPhrases& p);

#endif // MLANGPHRASE_H
