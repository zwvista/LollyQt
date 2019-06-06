#ifndef SLANGPHRASE_H
#define SLANGPHRASE_H

#include "Helpers/restapi.h"
#include "Models/mlangphrase.h"

struct SLangPhrase
{
    observable<vector<MLangPhrase>> getDataByLang(int langid);
    observable<vector<MLangPhrase>> getDataByLangPhrase(int langid, string phrase);
    observable<vector<MLangPhrase>> getDataById(int id);
    observable<string> updateObject(int id, string translation);
    observable<string> updateObject(const MLangPhrase& item);
    observable<string> createObject(const MLangPhrase& item);
    observable<string> deleteObject(int id);

    RestApi<MLangPhrase> api;
    RestApi<MLangPhrases> apis;
};

#endif // SLANGPHRASE_H
