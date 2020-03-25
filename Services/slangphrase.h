#ifndef SLANGPHRASE_H
#define SLANGPHRASE_H

#include "Helpers/restapi.h"
#include "Models/mlangphrase.h"

struct SLangPhrase
{
    observable<vector<MLangPhrase>> getDataByLang(int langid);
    observable<vector<MLangPhrase>> getDataByLangPhrase(int langid, wstring phrase);
    observable<vector<MLangPhrase>> getDataById(int id);
    observable<wstring> updateObject(int id, wstring translation);
    observable<wstring> updateObject(const MLangPhrase& item);
    observable<wstring> createObject(const MLangPhrase& item);
    observable<wstring> deleteObject(int id);

    RestApi<MLangPhrase> api;
    RestApi<MLangPhrases> apis;
};

#endif // SLANGPHRASE_H
