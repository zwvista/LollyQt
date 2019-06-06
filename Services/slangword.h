#ifndef SLANGWORD_H
#define SLANGWORD_H

#include "Helpers/restapi.h"
#include "Models/mlangword.h"

struct SLangWord
{
    observable<vector<MLangWord>> getDataByLang(int langid);
    observable<vector<MLangWord>> getDataByLangWord(int langid, string word);
    observable<vector<MLangWord>> getDataById(int id);
    observable<string> updateObject(int id, string note);
    observable<string> updateObject(const MLangWord& item);
    observable<string> createObject(const MLangWord& item);
    observable<string> deleteObject(int id);

    RestApi<MLangWord> api;
    RestApi<MLangWords> apis;
};

#endif // SLANGWORD_H
