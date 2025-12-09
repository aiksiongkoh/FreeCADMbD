#include "ASMTrIJ.h"
#include "Units.h"
#include "DistIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTrIJ> ASMTrIJ::With()
{
    auto inst = std::make_shared<ASMTrIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTrIJ::mbdClassNew()
{
    return DistIeqcJeqc::With();
}

double ASMTrIJ::asmtUnit()
{
    return asmtUnits()->length;
}
