#include "VelRadIeqctJeqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<VelRadIeqctJeqc> VelRadIeqctJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIeqctJeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}
