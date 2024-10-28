#pragma once
#include "variables/IntVar.h"
#include <vector>
#include <string>
#include <queue>
#include "constraints/Constraint.h"
#include "variables/IntVar.h"
#include "propagators/prop_x_not_y.h"
#include "propagators/prop_x_not_yc.h"
#include "decisions/selectors/values/minvalueselector.h"
#include "decisions/selectors/values/randomvalueselector.h"
#include "decisions/selectors/variables/most_constrained.h"
#include "decisions/selectors/variables/random.h"
#include "memory/trails.h"

using namespace std;

class Model
{
    MinValueSelector selector = MinValueSelector();

public:
    vector<IntVar> vars;
    Trail trail;
    int worldIndex = 0;
    void worldPush();
    void worldBack();
    vector<BinaryPropagator *> propagator_queue;
    void add_var(const string &name, int LB, int UB);
    IntVar* getVarbyName(const string &name);
    void add_binary_cstr(IntVar *i, IntVar *j);
    void add_binary_cstr2(IntVar *i, IntVar *j, int cste);
    void propagate_constraints();
    bool are_constraints_entailed();
    void AC3();
    bool solve();
    ~Model()
    {
        // Iterate through the propagator queue and delete each dynamically allocated propagator
        for (BinaryPropagator *propagator : propagator_queue)
        {
            delete propagator; // Free memory allocated for the propagator
        }
        // Optionally, clear the vector to ensure no dangling pointers remain
        propagator_queue.clear();
    }
};