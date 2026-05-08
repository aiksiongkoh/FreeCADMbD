#include "VelRadIeqtJeq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<VelRadIeqtJeq> VelRadIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIeqtJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}
