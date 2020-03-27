#ifndef SLANGPHRASE_H
#define SLANGPHRASE_H

#include "Helpers/restapi.h"
#include "Models/mlangphrase.h"

struct SLangPhrase
{
    observable<vector<MLangPhrase>> getDataByLang(int langid);
    observable<vector<MLangPhrase>> getDataByLangPhrase(int langid, string_t phrase);
    observable<vector<MLangPhrase>> getDataById(int id);
    observable<string_t> updateObject(int id, string_t translation);
    observable<string_t> updateObject(const MLangPhrase& item);
    observable<string_t> createObject(const MLangPhrase& item);
    observable<string_t> deleteObject(int id);

    RestApi<MLangPhrase> api;
    RestApi<MLangPhrases> apis;
};

#endif // SLANGPHRASE_H
