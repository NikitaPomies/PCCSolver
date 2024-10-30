#pragma once
#include "../../../variables/IntVar.h"
using namespace std;

class Model;

class ValueSelector
{

public:
      Model *parent_model;
      ValueSelector(Model* model);
      virtual int selectValue(IntVar *i) = 0;
};