
#pragma once
#include "Propagator.h"

class PropXnotYC : public BinaryPropagator
{
protected:
    int cste;

public:
    PropXnotYC(IntVar *i, IntVar *j, int c);
    void propagate() override;
    bool isEntailed() override;
    bool ArcSupport() override;
};