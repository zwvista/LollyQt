#ifndef MAUTOCORRECT_H
#define MAUTOCORRECT_H

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
using namespace std;
using nlohmann::json;

struct MAutoCorrect
{
    int ID = 0;
    int LANGID = 0;
    int SEQNUM = 0;
    string INPUT;
    string EXTENDED;
    string BASIC;
};

struct MAutoCorrects
{
    vector<MAutoCorrect> records;
};

void to_json(json& j, const MAutoCorrect& p);
void from_json(const json& j, MAutoCorrect& p);
void from_json(const json& j, MAutoCorrects& p);

#endif // MAUTOCORRECT_H
