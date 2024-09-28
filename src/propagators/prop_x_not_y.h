

#pragma once
#include "Propagator.h"

class PropXnotY : public BinaryPropagator
{
public:
    PropXnotY(IntVar *i, IntVar *j);
    void propagate() override;
    bool isEntailed() override;
};