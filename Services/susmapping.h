#ifndef SUSMAPPING_H
#define SUSMAPPING_H

#include "Helpers/restapi.h"
#include "Models/musmapping.h"

struct SUSMapping
{
    observable<vector<MUSMapping>> getData();

    RestApi<MUSMappings> apis;
};

#endif // SUSMAPPING_H
