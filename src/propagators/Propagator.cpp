#include"Propagator.h"

bool BinaryPropagator::isStateLess() {return state == "NEW";}
bool BinaryPropagator::isActive() {return state == "ACTIVE";}
void BinaryPropagator::setActive(){state = "ACTIVE";}
