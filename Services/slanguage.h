#ifndef SLANGUAGE_H
#define SLANGUAGE_H

#include "Helpers/restapi.h"
#include "Models/mlanguage.h"

struct SLanguage
{
    observable<vector<MLanguage>> getData();

    RestApi<MLanguages> apis;
};

#endif // SLANGUAGE_H
