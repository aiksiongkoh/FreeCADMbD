#include "OmeCompIecJecKec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<OmeCompIecJecKec> OmeCompIecJecKec::With()
{
    auto inst = std::make_shared<OmeCompIecJecKec>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIecJecKec> OmeCompIecJecKec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OmeCompIecJecKec>(frmi, frmj);
    inst->initialize();
    return inst;
}

void OmeCompIecJecKec::withFrmIFrmJFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis)
{
    eFrmI = frmi;
    eFrmJ = frmj;
    efrmK = frmk;
    axisK = axis;
}

double OmeCompIecJecKec::value()
{
    return omeiIeJeKe;
}

void OmeCompIecJecKec::calcPostDynCorrectorIteration()
{
    //omeIeJeO = omeOJeO - omeOIeO
    //omeIeJeKe = AKeO * omeIeJeO
    //omeiIeJeKe = ArowiKeO dot omeIeJeO = AcoljOKe dot omeIeJeO
    throw SimulationStoppingError("Should not implemented.");
}
