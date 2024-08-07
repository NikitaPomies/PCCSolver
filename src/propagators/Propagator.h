#pragma once
#include "../variables/IntVar.h"
#include <string>
using namespace std;

class BinaryPropagator
{
protected:
    IntVar x;
    IntVar y;
    string state = "NEW";

public:
    virtual void propagate() = 0;
    // Another pure virtual function
    virtual bool isEntailed() = 0;
    bool isStateLess();
    bool isActive();
    void setActive();
};