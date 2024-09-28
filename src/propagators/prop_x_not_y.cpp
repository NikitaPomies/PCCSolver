
#include "prop_x_not_y.h"

PropXnotY::PropXnotY(IntVar *i, IntVar *j){
    x = i;
    y = j;
}

void PropXnotY::propagate()
{
    if (x->isAssigned())
    {
        bool removed = y->removeValue(x->getValue());
    }
    else if (y->isAssigned())
    {
        bool removed = x->removeValue(y->getValue());
    }

}

bool PropXnotY::isEntailed()
{
    return (x->getValue() != y->getValue());
}
