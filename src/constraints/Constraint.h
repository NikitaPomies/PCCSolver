#pragma once
#include <vector>
#include "../propagators/Propagator.h"
using namespace std;

class Constraint
{

public:
    vector<BinaryPropagator> propagators;

    // Pure virtual function (makes this class abstract)
};