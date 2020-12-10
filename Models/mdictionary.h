#ifndef MDICTIONARY_H
#define MDICTIONARY_H

#include "mcommon.h"

struct MDictionary
{
    int ID = 0;
    int DICTID = 0;
    int LANGIDFROM = 0;
    string_t LANGNAMEFROM;
    int LANGIDTO = 0;
    string_t LANGNAMETO;
    int SEQNUM = 0;
    int DICTTYPEID = 0;
    string_t DICTTYPENAME;
    string_t DICTNAME;
    string_t URL;
    string_t CHCONV;
    string_t AUTOMATION;
    string_t DICTTABLE;
    string_t TRANSFORM;
    int WAIT = 0;
    string_t TEMPLATE;
    string_t TEMPLATE2;
};

void to_json(json& j, const MDictionary& p);
void from_json(const json& j, MDictionary& p);

struct MDictionaries
{
    vector<MDictionary> records;
};

void from_json(const json& j, MDictionaries& p);

struct MDictType
{
    int CODE = 0;
    string_t NAME;
};

struct MDictTypes
{
    vector<MDictType> records;
};

void from_json(const json& j, MDictType& p);
void from_json(const json& j, MDictTypes& p);

#endif // MDICTIONARY_H
