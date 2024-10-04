

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept>

#include "model.h"

// void Model::initialize_propagation(){
//     for (auto &constraint: cstrs){
//         for (auto &propagator: constraint.propagators){
//             propagator_queue.push(&propagator);
//         }
//     }
// };

void Model::add_binary_cstr(IntVar *i, IntVar *j)
{

    propagator_queue.push_back(new PropXnotY(i, j));
}
void Model::add_binary_cstr2(IntVar *i, IntVar *j, int cste)
{

    propagator_queue.push_back(new PropXnotYC(i, j, cste));
}
void Model::propagate_constraints()
{
    for (auto prop : propagator_queue)
    {
        prop->propagate();
    }
}

bool Model::are_constraints_entailed()
{
    for (const auto &prop : propagator_queue)
    {
        if (!prop->isEntailed())
        {
            return false; // Return false if any propagator is not entailed
        }
    }
    return true; // All propagators are entailed
}
bool Model::solve()
{
    // Check if all variables are assigned
    bool allAssigned = true;
    for (auto &var : vars)
    {
        if (!var.isAssigned())
        {
            allAssigned = false;
            break;
        }
    }

    if (allAssigned and are_constraints_entailed())
    {
        return true;
    }
    RandomVariableSelector varselector = RandomVariableSelector();
    // Select the first unassigned variable
    for (int i = 0; i < vars.size(); i++)
    {   
        try {
        IntVar& var = varselector.selectVariable(vars);
        

        if (!var.isAssigned())
        {
            std::set<int> backup_values = var.values.setvalues; // Backup the current domain

            // Backup the states of all other variables
            std::vector<std::set<int>> backup_domains(vars.size());
            for (size_t i = 0; i < vars.size(); ++i)
            {
                backup_domains[i] = vars[i].values.setvalues;
            }

            // Try each value in the domain
            for (int val : backup_values)
            {
                // Assign the variable to this value
                var.instantiateTo(val);

                // Propagate constraints
                propagate_constraints();

                // Check for empty domains
                bool valid = true;
                for (auto &v : vars)
                {
                    if (v.values.setvalues.empty())
                    {
                        valid = false;
                        break;
                    }
                }

                if (valid && solve())
                { // Recur
                    return true;
                }

                // Restore the variable's values and all affected domains
                var.values.setvalues = backup_values; // Restore current variable's values
                for (size_t i = 0; i < vars.size(); ++i)
                {
                    vars[i].values.setvalues = backup_domains[i]; // Restore other variables' domains
                }
            }

            return false; // Return false if no value works for the current variable
        }}
        catch(const std::runtime_error){
            return false;
        }
    }

    return false; // Fallback return
}
