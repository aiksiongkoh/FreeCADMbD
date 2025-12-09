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
    KinematicDotIJ::calcPostDynCorrectorIteration();
    aAjOKe = efrmK->aAjOe(axisK);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    omeIeJeO = eFrmJqc->omeOeO()->minusFullColumn(eFrmIqc->omeOeO());
    omeiIeJeKe = aAjOKe->dot(omeIeJeO);
}
