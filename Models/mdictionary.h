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
    boost::optional<string_t> URL;
    boost::optional<string_t> CHCONV;
    boost::optional<string_t> AUTOMATION;
    boost::optional<string_t> DICTTABLE;
    boost::optional<string_t> TRANSFORM_WIN;
    boost::optional<string_t> TRANSFORM;
    int WAIT = 0;
    boost::optional<string_t> TEMPLATE;
    boost::optional<string_t> TEMPLATE2;
};

void to_json(json& j, const MDictionary& p);
void from_json(const json& j, MDictionary& p);

struct MDictReference : MDictionary {

};

struct MDictsReference
{
    vector<MDictReference> records;
};

struct MDictItem
{
    string_t DICTID;
    string_t DICTNAME;
    vector<string_t> dictids();
};

void from_json(const json& j, MDictsReference& p);

struct MDictNote : MDictionary {

};

struct MDictsNote
{
    vector<MDictNote> records;
};

void from_json(const json& j, MDictsNote& p);

struct MDictTranslation : MDictionary {

};

struct MDictsTranslation
{
    vector<MDictTranslation> records;
};

void from_json(const json& j, MDictsTranslation& p);

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
