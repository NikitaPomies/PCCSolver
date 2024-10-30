#pragma once

#include "valueselector.h"
#include <climits>

class LeastConstrainingValue : public ValueSelector
{
public:
    using ValueSelector::ValueSelector;
    int selectValue(IntVar *i) override;
};