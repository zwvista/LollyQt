#ifndef SUNITPHRASE_H
#define SUNITPHRASE_H

#include "Helpers/restapi.h"
#include "Models/munitphrase.h"

struct SUnitPhrase
{
    observable<vector<MUnitPhrase>> getDataByTextbookUnitPart(const MTextbook& textbook, int unitPartFrom, int unitPartTo);
    observable<vector<MUnitPhrase>> getDataByLang(int langid, const vector<MTextbook>& textbooks);
    observable<vector<MUnitPhrase>> getDataByLangPhrase(int Phraseid);
    observable<string> updateObject(int id, int seqnum);
    observable<string> updateObject(const MUnitPhrase& item);
    observable<string> createObject(const MUnitPhrase& item);
    observable<string> deleteObject(int id);

    RestApi<MUnitPhrase> api;
    RestApi<MUnitPhrases> apis;
};

#endif // SUNITPHRASE_H
