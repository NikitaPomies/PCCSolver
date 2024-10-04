#pragma once
#include "../../../variables/IntVar.h"
using namespace std;

class VariableSelector
{
public:
    virtual IntVar& selectVariable(vector<IntVar> &v) = 0;
    
};
