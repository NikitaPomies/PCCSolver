#pragma once

#include "valueselector.h"

class MinValueSelector : public ValueSelector
{
public:
    int selectValue(const IntVar *i) override;
};