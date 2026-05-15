#include "ASMTvrIJ.h"
#include "Units.h"
#include "VelRadIeqJeq.h"

using namespace MbD;

std::shared_ptr<ASMTvrIJ> ASMTvrIJ::With()
{
    auto inst = std::make_shared<ASMTvrIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIeJe> ASMTvrIJ::mbdClassNew()
{
    return VelRadIeqJeq::With();
}

double ASMTvrIJ::asmtUnit()
{
    return asmtUnits()->velocity;
}
