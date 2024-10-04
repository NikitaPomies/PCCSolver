#pragma once
#include "variables/IntVar.h"
#include <vector>
#include <string>
#include <queue>
#include "constraints/Constraint.h"
#include "variables/IntVar.h"
#include "propagators/prop_x_not_y.h"
#include "propagators/prop_x_not_yc.h"
#include "decisions/selectors/minvalueselector.h"
#include "decisions/selectors/variables/most_constrained.h"
#include "decisions/selectors/variables/random.h"

using namespace std;

class Model
{
    MinValueSelector selector = MinValueSelector();
public:
    vector<IntVar> vars;
    // vector<Constraint> cstrs;
    vector<BinaryPropagator *> propagator_queue;
    // void initialize_propagation();
    void add_binary_cstr(IntVar *i, IntVar *j);
    void add_binary_cstr2(IntVar *i, IntVar *j, int cste);
    void propagate_constraints();
    bool are_constraints_entailed();

    bool solve();
    ~Model() {
    // Iterate through the propagator queue and delete each dynamically allocated propagator
    for (BinaryPropagator* propagator : propagator_queue) {
        delete propagator;  // Free memory allocated for the propagator
    }
    // Optionally, clear the vector to ensure no dangling pointers remain
    propagator_queue.clear();
}


};