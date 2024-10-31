

#include <vector>
#include <string>
#include <functional>

#include <iostream>
#include <stdexcept>
#include <cassert>
#include "model.h"

Model::Model() : valselector(this) {}

void Model::add_var(const string &name, int LB, int UB)
{
    this->vars.emplace_back(name, LB, UB, trail);
}

IntVar *Model::getVarbyName(const string &name)
{
    for (auto &var : vars)
    {
        if (var.name == name)
        {

            return &var;
        }
    }

    throw std::runtime_error("Model does not contain var called  " + name);
}

void Model::AC3()
{
    cout << "Starting Ac3" << endl;
    std::queue<BinaryPropagator *> ac_queue;
    std::unordered_set<BinaryPropagator *> visited; // Set to track visited propagators
    for (BinaryPropagator *propagator : propagator_queue)
    {
        ac_queue.push(propagator);
        visited.insert(propagator);
    }

    while (!ac_queue.empty())
    {

        BinaryPropagator *bp = ac_queue.front();
        ac_queue.pop();
        bool has_been_reduced = bp->ArcSupport();
        if (bp->x->values.setvalues.size() == 0)
        {
            break;
        }
        // throw std::runtime_error("Contradiction detected during bounds update->");

        if (has_been_reduced)
        {
            // cout << "Presolving making effective reduction" << endl;
            for (BinaryPropagator *propagator : propagator_queue)
            {
                // Be careful here ?
                if (propagator->x == bp->x and propagator->y != bp->y)
                {
                    if (visited.find(propagator) == visited.end()) // Check if not visited
                    {
                        ac_queue.push(propagator);
                        visited.insert(propagator); // Mark as visited
                    }
                }
                if (propagator->x == bp->y and propagator->y != bp->x)
                {
                    if (visited.find(propagator) == visited.end()) // Check if not visited
                    {
                        ac_queue.push(propagator);
                        visited.insert(propagator); // Mark as visited
                    }
                }
            }
        }
    }
    // cout << "Ending Ac3" << endl;
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
    for (const auto &prop : propagator_queue)
    {
        prop->propagate();
    }
}

void Model::forward_checking(const IntVar *var)
{

    for (const auto &propagator : propagator_queue)
    {
        // Be careful here ?
        if (propagator->x == var or propagator->y == var)
        {
            propagator->propagate();
        }
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
    if (allAssigned)
    {
        std::cout << "mauvaise assignation" << std::endl;
        return false;
    }

    // Select the first unassigned variable
    for (int i = 0; i < vars.size(); i++)
    {
        try
        {
            IntVar &var = varselector.selectVariable(vars);
            // if (&var == nullptr) return false;

            if (!var.isAssigned())
            {
                std::set<int> backup_values = var.values.setvalues; // Backup the current domain

                std::set<int> var_domain_backup = var.values.setvalues;

                // Try each value in the domain
                while (!backup_values.empty())

                {
                    int min_val = valselector.selectValue(&var);

                    stats.incrementNode();
                    stats.increaseDepth();

                    backup_values.erase(min_val);
                    // Assign the variable to this value


                    var.instantiateTo(min_val);
                    worldPush();
                    // Propagate constraints
                    propagate_constraints();
                    // forward_checking(&var);
                    // AC3();

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
                    stats.incrementBacktrack();
                    stats.decreaseDepth();
                    worldBack();
                    var.values.setvalues = backup_values;
                }
                var.values.setvalues = var_domain_backup;
                return false; // Return false if no value works for the current variable
            }
        }
        catch (const std::runtime_error)
        {
            cout << "Error detected during search" << endl;
            return false;
        }
    }

    return false; // Fallback return
}

bool Model::findSolution()
{

    // Initialization

    std::srand(std::time(0));

    stats.startTimer();
    // Resolution
    bool solved = solve();

    // Statistiques

    stats.display();

    return solved;
}