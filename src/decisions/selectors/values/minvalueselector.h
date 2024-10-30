#pragma once

#include "valueselector.h"

class MinValueSelector : public ValueSelector
{
public:
    int selectValue( IntVar *i) override;
};