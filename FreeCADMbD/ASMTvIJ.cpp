#include "ASMTvIJ.h"
#include "Units.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTvIJ> ASMTvIJ::With()
{
    auto inst = std::make_shared<ASMTvIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTvIJ::mbdClassNew()
{
    return std::shared_ptr<KinematicIJ>();
}

void ASMTvIJ::createMbD()
{
    throw SimulationStoppingError("To be implemented.");
}

double ASMTvIJ::asmtUnit()
{
    return asmtUnits()->velocity;
}
