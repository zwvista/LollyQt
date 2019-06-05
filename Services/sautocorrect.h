#ifndef SAUTOCORRECT_H
#define SAUTOCORRECT_H

#include "Helpers/restapi.h"
#include "Models/mautocorrect.h"

struct SAutoCorrect
{
    observable<vector<MAutoCorrect>> getDataByLang(int langid);

    RestApi<MAutoCorrects> apis;
};

#endif // SAUTOCORRECT_H
