#ifndef SUNITWORD_H
#define SUNITWORD_H

#include "Helpers/restapi.h"
#include "Models/munitword.h"
#include "Models/mtextbook.h"

struct SUnitWord
{
    observable<vector<MUnitWord>> getDataByTextbookUnitPart(const MTextbook& textbook, int unitPartFrom, int unitPartTo);
    observable<vector<MUnitWord>> getDataByLang(int langid, const vector<MTextbook>& textbooks);
    observable<vector<MUnitWord>> getDataByLangWord(int wordid);
    observable<string_t> updateObject(int id, int seqnum);
    observable<string_t> updateObject(const MUnitWord& item);
    observable<string_t> createObject(const MUnitWord& item);
    observable<string_t> deleteObject(int id);

    RestApi<MUnitWord> api;
    RestApi<MUnitWords> apis;
};

#endif // SUNITWORD_H
