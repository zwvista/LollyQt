#ifndef MDICTIONARY_H
#define MDICTIONARY_H

#include "mcommon.h"
#include <boost/algorithm/string.hpp>

struct MDictionary
{
    int ID = 0;
    int DICTID = 0;
    int LANGIDFROM = 0;
    string LANGNAMEFROM;
    int LANGIDTO = 0;
    string LANGNAMETO;
    int SEQNUM = 0;
    int DICTTYPEID = 0;
    string DICTTYPENAME;
    string DICTNAME;
    boost::optional<string> URL;
    boost::optional<string> CHCONV;
    boost::optional<string> AUTOMATION;
    boost::optional<string> DICTTABLE;
    boost::optional<string> TRANSFORM_WIN;
    boost::optional<string> TRANSFORM;
    int WAIT = 0;
    boost::optional<string> TEMPLATE;
    boost::optional<string> TEMPLATE2;
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
    string DICTID;
    string DICTNAME;
    vector<string> dictids() {
        vector<string> result;
        boost::algorithm::split(result, DICTID, boost::is_any_of(","));
        return result;
    }
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
    int ID = 0;
    string NAME;
};

struct MDictTypes
{
    vector<MDictType> records;
};

void from_json(const json& j, MDictType& p);
void from_json(const json& j, MDictTypes& p);

#endif // MDICTIONARY_H
