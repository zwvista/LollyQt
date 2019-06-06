#ifndef SVOICE_H
#define SVOICE_H

#include "Helpers/restapi.h"
#include "Models/mvoice.h"

struct SVoice
{
    observable<vector<MVoice>> getDataByLang(int langid);

    RestApi<MVoices> apis;
};

#endif // SVOICE_H
