#ifndef SUNITPHRASE_H
#define SUNITPHRASE_H

#include "Helpers/restapi.h"
#include "Models/munitphrase.h"

struct SUnitPhrase
{
    observable<vector<MUnitPhrase>> getDataByTextbookUnitPart(const MTextbook& textbook, int unitPartFrom, int unitPartTo);
    observable<vector<MUnitPhrase>> getDataByLang(int langid, const vector<MTextbook>& textbooks);
    observable<vector<MUnitPhrase>> getDataByLangPhrase(int Phraseid);
    observable<wstring> updateObject(int id, int seqnum);
    observable<wstring> updateObject(const MUnitPhrase& item);
    observable<wstring> createObject(const MUnitPhrase& item);
    observable<wstring> deleteObject(int id);

    RestApi<MUnitPhrase> api;
    RestApi<MUnitPhrases> apis;
};

#endif // SUNITPHRASE_H
