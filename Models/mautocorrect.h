#ifndef MAUTOCORRECT_H
#define MAUTOCORRECT_H

#include "mcommon.h"

struct MAutoCorrect
{
    int ID = 0;
    int LANGID = 0;
    int SEQNUM = 0;
    wstring INPUT;
    wstring EXTENDED;
    wstring BASIC;
};

struct MAutoCorrects
{
    vector<MAutoCorrect> records;
};

void to_json(json& j, const MAutoCorrect& p);
void from_json(const json& j, MAutoCorrect& p);
void from_json(const json& j, MAutoCorrects& p);

wstring autoCorrect(const wstring& text, const vector<MAutoCorrect>& autoCorrects,
                 function<wstring(const MAutoCorrect&)> f1, function<wstring(const MAutoCorrect&)> f2);

#endif // MAUTOCORRECT_H
