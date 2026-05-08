#include "OmeCompIeJeKe.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<OmeCompIeJeKe> OmeCompIeJeKe::With()
{
    auto inst = std::make_shared<OmeCompIeJeKe>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeJeKe> OmeCompIeJeKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OmeCompIeJeKe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void OmeCompIeJeKe::withFrmIFrmJFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis)
{
    eFrmI = frmi;
    eFrmJ = frmj;
    efrmK = frmk;
    axisK = axis;
}

double OmeCompIeJeKe::value()
{
    return omeiIeJeKe;
}

void OmeCompIeJeKe::simUpdateAll()
{
    //omeIeJeO = omeOJeO - omeOIeO
    //omeIeJeKe = AKeO * omeIeJeO
    //omeiIeJeKe = ArowiKeO dot omeIeJeO = AcoljOKe dot omeIeJeO
    throw SimulationStoppingError("Should not implemented.");
}
