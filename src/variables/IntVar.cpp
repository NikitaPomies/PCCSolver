#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept>
#include "IntVar.h"

IntVar::IntVar(const std::string &name, int lb, int ub)
    : name(name), LB(lb), UB(ub) {} // -1 indicates unassigned

int IntVar::getLB() const { return LB; }
int IntVar::getUB() const { return UB; }
void IntVar::setLB(int value) { LB = value; }
void IntVar::setUB(int value) { UB = value; }

bool IntVar::isAssigned()
{
    return LB == UB;
}

int IntVar::getValue()
{
    if (!isAssigned())
    {
        throw std::runtime_error("getValue() can only be called on an instantiated variable. ");
    }
    else
    {
        return LB;
    }
}
bool IntVar::contains(int value)
{
    return ((value >= LB) && (value <= UB));
}
bool IntVar::updateLB(int value)
{
    int old_lb = this->getLB();
    if (old_lb < value)
    {
        int old_ub = this->getUB();
        if (value > old_ub)
        {
            throw std::runtime_error("new lower bound superior than actual upper bound ");
        }
        else
        {
            this->setLB(value);
        }
    }
    return false;
}

bool IntVar::updateUB(int value)
{
    int old_ub = this->getUB();
    if (old_ub > value)
    {
        int old_lb = this->getLB();
        if (value > old_lb)
        {
            throw std::runtime_error("new upper bound inferior than actual lower bound ");
        }
        else
        {
            this->setUB(value);
        }
    }
    return false;
}
