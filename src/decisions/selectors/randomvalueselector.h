#pragma once

#include "valueselector.h"

class RandomValueSelector : public ValueSelector
{
public:
    int selectValue(const IntVar *i) override;
};