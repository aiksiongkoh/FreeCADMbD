#include "VelRadIecJec.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<VelRadIecJec> VelRadIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIecJec>(frmi, frmj);
    inst->initialize();
    return inst;
}

void VelRadIecJec::calcPostDynCorrectorIteration()
{
    rIeJeO = eFrmJ->rOeO->minusFullColumn(eFrmI->rOeO);
    rIeJe = rIeJeO->length();
    if (rIeJe == 0.0) return;
    uIeJeO = rIeJeO->times(1.0 / rIeJe);
    vIeJeO = eFrmJ->vOeO()->minusFullColumn(eFrmI->vOeO());
    vIeJe = vIeJeO->dot(uIeJeO);
}

double VelRadIecJec::value()
{
    return vIeJe;
}
