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
    bool has_reduced = false;
    std::vector<int> values_to_remove;

    for (const int x_value : x->values.setvalues)
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
            values_to_remove.push_back(x_value);
            has_reduced = true;
        }
    }
    for (const int value : values_to_remove)
    {
        x->removeValue(value);
    }

    return has_reduced;
}
