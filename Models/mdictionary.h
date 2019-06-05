#ifndef MDICTIONARY_H
#define MDICTIONARY_H

#include "mcommon.h"

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

struct MDictReference : MDictionary {

};

struct MDictsReference
{
    vector<MDictReference> records;
};

struct MDictNote : MDictionary {

};

struct MDictsNote
{
    vector<MDictNote> records;
};

struct MDictTranslation : MDictionary {

};

struct MDictsTranslation
{
    vector<MDictTranslation> records;
};

#endif // MDICTIONARY_H
