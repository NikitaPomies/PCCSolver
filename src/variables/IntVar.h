

#pragma once
#ifndef INTVAR_H // Include guard
#define INTVAR_H
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept>

// Variable class
class IntVar
{

private:
    int LB;
    int UB;

public:
    std::string name;

    IntVar(const std::string &name, int lb, int ub);

    bool isAssigned();

    int getValue();

    bool contains(int value);
    int getLB() const;
    int getUB() const;
    void setLB(int value);
    void setUB(int value);
    bool updateLB(int value);
    bool updateUB(int value);

};

#endif