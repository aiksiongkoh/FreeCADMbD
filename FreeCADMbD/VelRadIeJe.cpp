#include "VelRadIeJe.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<VelRadIeJe> VelRadIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIeJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void VelRadIeJe::simUpdateAll()
{
    rIeJeO = dispIeJeO->rIeJeO;
    rIeJe = rIeJeO->length();
    if (rIeJe == 0.0) return;
    uIeJeO = rIeJeO->times(1.0 / rIeJe);
    vIeJeO = eFrmJ->vOeO()->minusFullColumn(eFrmI->vOeO());
    vIeJe = vIeJeO->dot(uIeJeO);
}

double VelRadIeJe::value()
{
    return vIeJe;
}
