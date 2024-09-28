#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept>
#include "IntVar.h"

IntVar::IntVar(const std::string &name, int lb, int ub)
    : name(name), LB(lb), UB(ub)
{

    for (int i = LB; i <= UB; ++i)
    {
        values.insert(i);
    }
} // -1 indicates unassigned

int IntVar::getLB() const { return LB; }
int IntVar::getUB() const { return UB; }
void IntVar::setLB(int value) { LB = value; }
void IntVar::setUB(int value) { UB = value; }

bool IntVar::isAssigned()
{
    //return LB == UB;
    return values.setvalues.size()==1;
}

int IntVar::getValue()
{
    if (!isAssigned())
    {
        throw std::runtime_error("getValue() can only be called on an instantiated variable. ");
    }
    else
    {
       return *values.setvalues.begin();
    }
}
bool IntVar::contains(int value)
{
    return  (values.contains(value));
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

bool IntVar::removeValue(int value)
{
    bool canremove = this->contains(value);
    if (canremove)
    {
        this->values.remove(value);

    }
    return canremove;
}

std::string IntVar::toString()
{
    std::string var_string = "{";
    for (auto it_value = (values.setvalues.begin()); it_value != values.setvalues.end(); ++it_value)
    {
        var_string += ' ';
        var_string += std::to_string(*it_value);
    }
    var_string += " }";
    return var_string;
}

void IntVar::instantiateTo(int value)
{
    values.setvalues.clear(); // Remove all elements
    values.setvalues.insert(value);
    LB = value;
    UB = value;
}


