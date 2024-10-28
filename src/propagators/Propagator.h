#pragma once
#include "../variables/IntVar.h"
#include <string>
using namespace std;

class BinaryPropagator
{

public:
    IntVar *x;
    IntVar *y;
    virtual void propagate() = 0;
    // Another pure virtual function
    virtual bool isEntailed() = 0;
    virtual bool ArcSupport() = 0;
};