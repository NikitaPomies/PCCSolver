#include "prop_equal_x_y.h"
PropEqualXY::PropEqualXY(IntVar *i, IntVar *j)
{
    x = i;
    y = j;
}

void PropEqualXY::updateBounds()
{
    try
    {
        while (x->updateLB(y->getLB()) || y->updateLB(x->getLB()))
        {
            // Loop until no further lower bound updates can be made
        }
        while (x->updateUB(y->getUB()) || y->updateUB(x->getUB()))
        {
            // Loop until no further upper bound updates can be made
        }
    }
    catch (const std::runtime_error)
    {
        // Handle exceptions here, if needed
        // e->g->, throw ContradictionException("Bound update caused contradiction->");
        throw std::runtime_error("Contradiction detected during bounds update->");
    }
}

void PropEqualXY::propagate()
{
    updateBounds();
}

bool PropEqualXY::isEntailed()
{
    return (x->getValue() == y->getValue());
}
