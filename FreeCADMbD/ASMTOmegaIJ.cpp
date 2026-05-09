#include "ASMTOmegaIJ.h"
#include "Units.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTOmegaIJ> ASMTOmegaIJ::With()
{
    auto inst = std::make_shared<ASMTOmegaIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIeJe> ASMTOmegaIJ::mbdClassNew()
{
    return std::shared_ptr<KinematicIeJe>();
}

void ASMTOmegaIJ::createMbD()
{
    throw SimulationStoppingError("To be implemented.");
}

double ASMTOmegaIJ::asmtUnit()
{
    return asmtUnits()->omega;
}
