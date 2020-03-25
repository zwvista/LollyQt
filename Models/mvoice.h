#ifndef MVOICE_H
#define MVOICE_H

#include "mcommon.h"

struct MVoice
{
    int ID = 0;
    int LANGID = 0;
    int VOICETYPEID = 0;
    boost::optional<wstring> VOICELANG;
    wstring VOICENAME;
};

struct MVoices
{
    vector<MVoice> records;
};

void to_json(json& j, const MVoice& p);
void from_json(const json& j, MVoice& p);
void from_json(const json& j, MVoices& p);

#endif // MVOICE_H
