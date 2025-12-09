#include "ForceBasicqccqComp.h"

using namespace MbD;

std::shared_ptr<ForceBasicqccqComp> ForceBasicqccqComp::With()
{
    auto inst = std::make_shared<ForceBasicqccqComp>();
    inst->initialize();
    return inst;
}
