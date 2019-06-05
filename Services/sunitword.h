#ifndef SUNITWORD_H
#define SUNITWORD_H

#include "Helpers/restapi.h"
#include "Models/munitword.h"
#include "Models/mtextbook.h"

struct SUnitWord
{
    observable<vector<MUnitWord>> getDataByTextbookUnitPart(const MTextbook& textbook, int unitPartFrom, int unitPartTo);

    RestApi<MUnitWord> api;
    RestApi<MUnitWords> apis;
};

#endif // SUNITWORD_H
