#include "ASMTSymbolicFunction.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunction> ASMTSymbolicFunction::With()
{
    auto inst = std::make_shared<ASMTSymbolicFunction>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Units> ASMTSymbolicFunction::mbdUnits()
{
    return owner->mbdUnits();
}

std::shared_ptr<Units> ASMTSymbolicFunction::asmtUnits()
{
    return owner->asmtUnits();
}

std::shared_ptr<System> ASMTSymbolicFunction::mbdSys()
{
    return owner->mbdSys();
}
