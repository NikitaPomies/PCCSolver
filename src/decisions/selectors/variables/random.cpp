#include "random.h"
#include <stdexcept>

IntVar& RandomVariableSelector::selectVariable(vector<IntVar> &v){
    for (auto &var: v){
        if (!var.isAssigned()){
            return var;
           
        }
    }
    throw std::runtime_error("No unassigned variable found");
}