#ifndef COMMONAPI_H
#define COMMONAPI_H

#include "Models/mcommon.h"

enum class UnitPartToType {
    UNIT,
    PART,
    TO,
};

struct CommonApi
{
    static string_t getAccuracy(int CORRECT, int TOTAL);
};

struct LollyInterface {
    virtual void settingsChanged() = 0;
    virtual ~LollyInterface() = default;
};

#endif // COMMONAPI_H
