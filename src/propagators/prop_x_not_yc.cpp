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

bool PropXnotYC::ArcSupport()
{
    bool has_reduced;
    for (const auto x_value : x->values.setvalues)
    {
        bool have_support = false;
        for (const auto y_value : y->values.setvalues)
        {
            if (x_value != y_value + cste)
            {
                have_support = true;
                break;
            }
        }
        if (!have_support)
        {
            x->removeValue(x_value);
            has_reduced = true;
        }
    }
    return has_reduced;
}
