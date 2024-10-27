

#pragma once
#ifndef INTVAR_H // Include guard
#define INTVAR_H
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <set>

#include "../utils/OrderedSet.h"

class Trail;
// Variable class
class IntVar
{

private:
    int LB;
    int UB;

public:
    OrderedSet values;
    std::string name;

    Trail *trail;

    IntVar(const std::string &name, int lb, int ub);
    IntVar(const std::string &name, int lb, int ub, Trail &trail);

    bool isAssigned();

    int getValue();

    void instantiateTo(int value);

    bool contains(int value);
    int getLB() const;
    int getUB() const;
    void setLB(int value);
    void setUB(int value);
    bool updateLB(int value);
    bool updateUB(int value);
    bool removeValue(int value);
    std::string toString();
};

#endif