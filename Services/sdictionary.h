#ifndef SDICTIONARY_H
#define SDICTIONARY_H

#include "Helpers/restapi.h"
#include "Models/mdictionary.h"

struct SDictionary
{

    observable<vector<MDictionary>> getDictsReferenceByLang(int langid);
    observable<vector<MDictionary>> getDictsNoteByLang(int langid);
    observable<vector<MDictionary>> getDictsTranslationByLang(int langid);
    RestApi<MDictionary> api;
    RestApi<MDictionaries> apis;
};

struct SDictType
{
    observable<vector<MDictType>> getData();
    RestApi<MDictTypes> apis;
};

#endif // SDICTIONARY_H
