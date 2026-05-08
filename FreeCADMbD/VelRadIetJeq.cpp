#include "VelRadIetJeq.h"

using namespace MbD;

VelRadIetJeq::VelRadIetJeq(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIeJeq(frmi, frmj)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<VelRadIetJeq> VelRadIetJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIetJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}
