
#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include "../variables/IntVar.h"

class Trail
{
public:
    Trail()
    {
        std::cout << "Trail created." << std::endl;
    }
    ~Trail()
    {
        std::cout << "Trail destroyed." << std::endl;
    }

    // Stack to store variable domain changes and assignments
    std::stack<std::vector<std::pair<IntVar *, int>>> trailStack;

    // Save the changes to the variable's domain (which values are removed)
    void saveDomainChange(IntVar *var, int removedValue);

    // Undo the last recorded domain change
    void backtrack();

    // Get the current trail levelF
    int getCurrentLevel() const;
};