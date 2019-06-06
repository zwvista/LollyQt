#ifndef STEXTBOOK_H
#define STEXTBOOK_H

#include "Helpers/restapi.h"
#include "Models/mtextbook.h"

struct STextbook
{
    observable<vector<MTextbook>> getDataByLang(int langid);

    RestApi<MTextbooks> apis;
};

#endif // STEXTBOOK_H
