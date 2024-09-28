#pragma once
#include "Propagator.h"

class PropEqualXY : public BinaryPropagator
{

    PropEqualXY(IntVar *i, IntVar *j);
    void propagate() override;
    bool isEntailed() override;

    void updateBounds();
};