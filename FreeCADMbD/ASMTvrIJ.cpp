#include "ASMTvrIJ.h"
#include "Units.h"
#include "VelRadIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTvrIJ> ASMTvrIJ::With()
{
    auto inst = std::make_shared<ASMTvrIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTvrIJ::mbdClassNew()
{
    return VelRadIeqcJeqc::With();
}

double ASMTvrIJ::asmtUnit()
{
    return asmtUnits()->velocity;
}
