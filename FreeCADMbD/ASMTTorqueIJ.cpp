#include "ASMTTorqueIJ.h"
#include "Units.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTTorqueIJ> ASMTTorqueIJ::With()
{
    auto inst = std::make_shared<ASMTTorqueIJ>();
    inst->initialize();
    return inst;
}

void ASMTTorqueIJ::createMbD()
{
    throw SimulationStoppingError("To be implemented.");
}

double ASMTTorqueIJ::asmtUnit()
{
    return asmtUnits()->torque;
}
