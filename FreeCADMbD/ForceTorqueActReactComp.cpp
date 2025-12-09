#include "ForceTorqueActReactComp.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActReactComp> ForceTorqueActReactComp::With()
{
    auto inst = std::make_shared<ForceTorqueActReactComp>();
    inst->initialize();
    return inst;
}
