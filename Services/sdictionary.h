#ifndef SDICTIONARY_H
#define SDICTIONARY_H

#include "Helpers/restapi.h"
#include "Models/mdictionary.h"

struct SDictionary
{

};

struct SDictReference
{
    observable<vector<MDictReference>> getDataByLang(int langid);
    RestApi<MDictReference> api;
    RestApi<MDictsReference> apis;
};

struct SDictNote
{
    observable<vector<MDictNote>> getDataByLang(int langid);
    RestApi<MDictNote> api;
    RestApi<MDictsNote> apis;
};

struct SDictTranslation
{
    observable<vector<MDictTranslation>> getDataByLang(int langid);
    RestApi<MDictTranslation> api;
    RestApi<MDictsTranslation> apis;
};

#endif // SDICTIONARY_H
