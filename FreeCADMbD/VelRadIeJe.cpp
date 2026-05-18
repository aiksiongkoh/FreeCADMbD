#include "VelRadIeJe.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<VelRadIeJe> VelRadIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIeJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void MbD::VelRadIeJe::initialize()
{
    dispIeJeO = DispIeJeO::With(eFrmI, eFrmJ);
    dispIeJeO->owner = this;
}

void MbD::VelRadIeJe::useUniqueDispIeJeO()
{
    auto dispIeJeOs = root()->dispIeJeOs;
    auto it = std::find_if(dispIeJeOs->begin(), dispIeJeOs->end(), [&](auto disp) {return disp->hasSameEndFrms(dispIeJeO); });
    if (it == dispIeJeOs->end()) {
        dispIeJeOs->push_back(dispIeJeO);
    }
    else {
        dispIeJeO = *it;
    }
}

void MbD::VelRadIeJe::useUniqueDispIeJeKe()
{
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
