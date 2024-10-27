#pragma once
#include "../../../variables/IntVar.h"
using namespace std;

class ValueSelector
{
public:
    virtual int selectValue(const IntVar* i) = 0;
};