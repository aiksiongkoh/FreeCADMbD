#include "ASMTAtPointJoint.h"

using namespace MbD;

std::shared_ptr<ASMTAtPointJoint> ASMTAtPointJoint::With()
{
    auto inst = std::make_shared<ASMTAtPointJoint>();
    inst->initialize();
    return inst;
}
