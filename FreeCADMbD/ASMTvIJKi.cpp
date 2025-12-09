#include "ASMTvIJKi.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTvIJKi> ASMTvIJKi::With()
{
    auto inst = std::make_shared<ASMTvIJKi>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTvIJKi::mbdClassNew()
{
    return std::shared_ptr<KinematicIJ>();
}

double ASMTvIJKi::asmtUnit()
{
    return asmtUnits()->velocity;
}
