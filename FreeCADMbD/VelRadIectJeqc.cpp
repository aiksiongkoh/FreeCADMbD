#include "VelRadIectJeqc.h"

using namespace MbD;

VelRadIectJeqc::VelRadIectJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIecJeqc(frmi, frmj)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<VelRadIectJeqc> VelRadIectJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIectJeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}
