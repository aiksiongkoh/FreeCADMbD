#include "ForceTorqueActionComp.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActionComp> ForceTorqueActionComp::With()
{
    auto inst = std::make_shared<ForceTorqueActionComp>();
    inst->initialize();
    return inst;
}
