#ifndef MUNITPHRASE_H
#define MUNITPHRASE_H

#include "mcommon.h"
#include "mtextbook.h"

struct MUnitPhrase
{
    int ID = 0;
    int LANGID = 0;
    int TEXTBOOKID = 0;
    string TEXTBOOKNAME;
    int UNIT = 0;
    int PART = 0;
    int SEQNUM = 0;
    int PHRASEID = 0;
    string PHRASE;
    boost::optional<string> TRANSLATION;

    const MTextbook *pTextbook = nullptr;
};

struct MUnitPhrases
{
    vector<MUnitPhrase> records;
};

void to_json(json& j, const MUnitPhrase& p);
void from_json(const json& j, MUnitPhrase& p);
void from_json(const json& j, MUnitPhrases& p);

#endif // MUNITPHRASE_H
