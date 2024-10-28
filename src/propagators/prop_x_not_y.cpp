
#include "prop_x_not_y.h"

PropXnotY::PropXnotY(IntVar *i, IntVar *j)
{
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

bool PropXnotY::ArcSupport()
{
    bool has_reduced = false;
    std::vector<int> values_to_remove;

    for (const int x_value : x->values.setvalues)
    {
        bool have_support = false;
        for (const auto y_value : y->values.setvalues)
        {
            if (x_value != y_value)
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
