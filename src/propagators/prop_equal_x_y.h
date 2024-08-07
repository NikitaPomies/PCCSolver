#pragma once
#include "Propagator.h"


class PropEqualXY : public BinaryPropagator {

    void propagate() override ;
    bool isEntailed() override;
    void updateBounds(){

    }


} ;