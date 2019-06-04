#ifndef MUNITWORD_H
#define MUNITWORD_H

#include <vector>
#include <string>
#include "Helpers/optional2json.h"
#include <nlohmann/json.hpp>
using namespace std;
using nlohmann::json;

struct MUnitWord
{
    int ID = 0;
    int LANGID = 0;
    int TEXTBOOKID = 0;
    string TEXTBOOKNAME;
    int UNIT = 0;
    int PART = 0;
    int SEQNUM = 0;
    int WORDID = 0;
    string WORD;
    boost::optional<string> NOTE;
    int FAMIID = 0;
    int LEVEL = 0;
    int CORRECT = 0;
    int TOTAL = 0;
};

struct MUnitWords
{
    vector<MUnitWord> records;
};

void to_json(json& j, const MUnitWord& p);
void from_json(const json& j, MUnitWords& p);
void from_json(const json& j, MUnitWords& p);

#endif // MUNITWORD_H
