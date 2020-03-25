#ifndef MDICTIONARY_H
#define MDICTIONARY_H

#include "mcommon.h"

struct MDictionary
{
    int ID = 0;
    int DICTID = 0;
    int LANGIDFROM = 0;
    wstring LANGNAMEFROM;
    int LANGIDTO = 0;
    wstring LANGNAMETO;
    int SEQNUM = 0;
    int DICTTYPEID = 0;
    wstring DICTTYPENAME;
    wstring DICTNAME;
    boost::optional<wstring> URL;
    boost::optional<wstring> CHCONV;
    boost::optional<wstring> AUTOMATION;
    boost::optional<wstring> DICTTABLE;
    boost::optional<wstring> TRANSFORM_WIN;
    boost::optional<wstring> TRANSFORM;
    int WAIT = 0;
    boost::optional<wstring> TEMPLATE;
    boost::optional<wstring> TEMPLATE2;
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
    wstring DICTID;
    wstring DICTNAME;
    vector<wstring> dictids();
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
    wstring NAME;
};

struct MDictTypes
{
    vector<MDictType> records;
};

void from_json(const json& j, MDictType& p);
void from_json(const json& j, MDictTypes& p);

#endif // MDICTIONARY_H
