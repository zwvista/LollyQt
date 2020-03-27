#ifndef SLANGWORD_H
#define SLANGWORD_H

#include "Helpers/restapi.h"
#include "Models/mlangword.h"

struct SLangWord
{
    observable<vector<MLangWord>> getDataByLang(int langid);
    observable<vector<MLangWord>> getDataByLangWord(int langid, string_t word);
    observable<vector<MLangWord>> getDataById(int id);
    observable<string_t> updateObject(int id, string_t note);
    observable<string_t> updateObject(const MLangWord& item);
    observable<string_t> createObject(const MLangWord& item);
    observable<string_t> deleteObject(int id);

    RestApi<MLangWord> api;
    RestApi<MLangWords> apis;
};

#endif // SLANGWORD_H
