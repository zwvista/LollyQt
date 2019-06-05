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
    observable<string> updateObject(int id, int seqnum);
    observable<string> updateObject(const MUnitWord& item);
    observable<string> createObject(const MUnitWord& item);
    observable<string> deleteObject(int id);

    RestApi<MUnitWord> api;
    RestApi<MUnitWords> apis;
};

#endif // SUNITWORD_H
