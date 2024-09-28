#pragma once
#include "variables/IntVar.h"
#include <vector>
#include <string>
#include <queue>
#include "constraints/Constraint.h"
#include "variables/IntVar.h"
#include "propagators/prop_x_not_y.h"
using namespace std;

class Model
{
public:
    vector<IntVar> vars;
    // vector<Constraint> cstrs;
    queue<BinaryPropagator *> propagator_queue;
    // void initialize_propagation();
    void add_binary_cstr(IntVar *i, IntVar *j);
};