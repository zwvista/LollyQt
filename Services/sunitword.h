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
    observable<wstring> updateObject(int id, int seqnum);
    observable<wstring> updateObject(const MUnitWord& item);
    observable<wstring> createObject(const MUnitWord& item);
    observable<wstring> deleteObject(int id);

    RestApi<MUnitWord> api;
    RestApi<MUnitWords> apis;
};

#endif // SUNITWORD_H
