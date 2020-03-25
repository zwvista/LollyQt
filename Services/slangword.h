#ifndef SLANGWORD_H
#define SLANGWORD_H

#include "Helpers/restapi.h"
#include "Models/mlangword.h"

struct SLangWord
{
    observable<vector<MLangWord>> getDataByLang(int langid);
    observable<vector<MLangWord>> getDataByLangWord(int langid, wstring word);
    observable<vector<MLangWord>> getDataById(int id);
    observable<wstring> updateObject(int id, wstring note);
    observable<wstring> updateObject(const MLangWord& item);
    observable<wstring> createObject(const MLangWord& item);
    observable<wstring> deleteObject(int id);

    RestApi<MLangWord> api;
    RestApi<MLangWords> apis;
};

#endif // SLANGWORD_H
