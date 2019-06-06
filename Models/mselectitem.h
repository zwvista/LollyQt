#ifndef MSELECTITEM_H
#define MSELECTITEM_H

#include <string>
using namespace std;

struct MSelectItem
{
    int value = 0;
    string label;

    MSelectItem(int value, const string& label) : value(value), label(label) {}
};

#endif // MSELECTITEM_H
