#include "ASMTOmegaIJKi.h"
#include "Units.h"
#include "OmeCompIeqcJeqcKeqc.h"

using namespace MbD;

std::shared_ptr<ASMTOmegaIJKi> ASMTOmegaIJKi::With()
{
    auto inst = std::make_shared<ASMTOmegaIJKi>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTOmegaIJKi::mbdClassNew()
{
    return OmeCompIeqcJeqcKeqc::With();
}

double ASMTOmegaIJKi::asmtUnit()
{
    return asmtUnits()->omega;
}
