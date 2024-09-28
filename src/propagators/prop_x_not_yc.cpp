#include "prop_x_not_yc.h"

PropXnotYC::PropXnotYC(IntVar *i, IntVar *j, int c)
{
    x = i;
    y = j;
    cste = c;
}

void PropXnotYC::propagate()
{
    if (x->isAssigned())
    {
        bool removed = y->removeValue(x->getValue() - cste);
    }
    else if (y->isAssigned())
    {
        bool removed = x->removeValue(y->getValue() + cste);
    }
}

bool PropXnotYC::isEntailed()
{
    return (x->getValue() != y->getValue() + cste);
}
