

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include "model.h"

// void Model::initialize_propagation(){
//     for (auto &constraint: cstrs){
//         for (auto &propagator: constraint.propagators){
//             propagator_queue.push(&propagator);
//         }
//     }
// };

void Model::add_var(const string &name, int LB, int UB)
{
    this->vars.emplace_back(name, LB, UB, trail);
}

void Model::worldPush()
{
    worldIndex += 1;
    std::vector<std::pair<IntVar *, int>> emptyVector;

    // Push the empty vector onto the trailStack
    trail.trailStack.push(emptyVector);
}
void Model::worldBack()
{
    worldIndex -= 1;
    trail.backtrack();
}

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
            //std::cout<<prop->x->name<<"  "<<prop->y->name<<std::endl;
            //std::cout<<&prop->x<<"  "<<&prop->y->name<<std::endl;
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
    if (allAssigned) {
        std::cout<<"mauvaise assignation"<<std::endl;
        return false;
    }
    // RandomVariableSelector varselector;
    MostConstrainedVarSelector varselector;
    //MinValueSelector valselector;
    RandomValueSelector valselector;
    // Select the first unassigned variable
    for (int i = 0; i < vars.size(); i++)
    {
        try
        {
            IntVar &var = varselector.selectVariable(vars);
            //if (&var == nullptr) return false;

            if (!var.isAssigned())
            {
                std::set<int> backup_values = var.values.setvalues; // Backup the current domain

                // Backup the states of all other variables
                /*    std::vector<std::set<int>> backup_domains(vars.size());
                   for (size_t i = 0; i < vars.size(); ++i)
                   {
                       backup_domains[i] = vars[i].values.setvalues;
                   } */
                std::set<int> var_domain_backup = var.values.setvalues;

                // Try each value in the domain
                while (!backup_values.empty())

                {
                    int min_val = valselector.selectValue(&var);

                    backup_values.erase(min_val);
                    // Assign the variable to this value

                    int trailLevel = trail.getCurrentLevel();

                    var.instantiateTo(min_val);
                    worldPush();
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

                    bool alltest = true;
                    for (auto &var : vars)
                    {
                        if (!var.isAssigned())
                        {
                            alltest = false;
                            break;
                        }
                    }
                    /* if (alltest)
                    {
                        bool check = are_constraints_entailed();
                        std::cout << check << std::endl;
                    }; */

                    if (valid && solve())
                    { // Recur
                        return true;
                    }

                    worldBack();
                    var.values.setvalues = backup_values;
                    // Restore the variable's values and all affected domains
                    /*                     var.values.setvalues = backup_values;*/ // Restore current variable's values
                                                                                   /*                     for (size_t i = 0; i < vars.size(); ++i)
                                                                                                       {
                                                                                                           if (&vars[i] != &var){
                                                                                                           if (vars[i].values.setvalues.size() != backup_domains[i].size()){
                                                                                                               std::cout<<"test";
                                                                                                           }
                                                                                                               //vars[i].values.setvalues = backup_domains[i];
                                                                                                               } // Restore other variables' domains
                                                                                                       } */
                }
                var.values.setvalues = var_domain_backup;
                return false; // Return false if no value works for the current variable
            }
        }
        catch (const std::runtime_error)
        {
            return false;
        }
    }

    return false; // Fallback return
}
