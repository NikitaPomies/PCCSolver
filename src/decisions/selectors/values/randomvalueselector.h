#pragma once

#include "valueselector.h"

class RandomValueSelector : public ValueSelector
{
public:
    using ValueSelector::ValueSelector;
    int selectValue(IntVar *i) override;
};