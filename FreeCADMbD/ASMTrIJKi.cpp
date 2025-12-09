#include "ASMTrIJKi.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTrIJKi> ASMTrIJKi::With()
{
    auto inst = std::make_shared<ASMTrIJKi>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTrIJKi::mbdClassNew()
{
    return std::shared_ptr<KinematicIJ>();
}

double ASMTrIJKi::asmtUnit()
{
    return asmtUnits()->length;
}
