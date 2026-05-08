#include "OmeCompIeJeqKe.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<OmeCompIeJeqKe> OmeCompIeJeqKe::With()
{
    auto inst = std::make_shared<OmeCompIeJeqKe>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeJeqKe> OmeCompIeJeqKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OmeCompIeJeqKe>(frmi, frmj);
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeJeqKe> OmeCompIeJeqKe::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    auto inst = std::make_shared<OmeCompIeJeqKe>(frmi, frmj, efrmK, axisK);
    inst->initialize();
    return inst;
}

void OmeCompIeJeqKe::initialize()
{
    OmeCompIeJeKe::initialize();
    pomeiIeJeKepEJ = FullRow<double>::With(4);
    pomeiIeJeKepEdotJ = FullRow<double>::With(4);
}

void OmeCompIeJeqKe::simUpdateAll()
{
    //omeIeJeO = omeOJeO - omeOIeO
    //omeIeJeKe = AKeO * omeIeJeO
    //omeiIeJeKe = ArowiKeO dot omeIeJeO = AcoljOKe dot omeIeJeO
    aAjOKe = efrmK->aAjOe(axisK);
    auto eFrmJqc = std::static_pointer_cast<EndFrameq>(eFrmJ);
    omeIeJeO = eFrmJqc->omeOeO(); //omeOIeO is zero
    omeiIeJeKe = aAjOKe->dot(omeIeJeO);
    auto pomeIeJeOpEJ = eFrmJqc->pomeOeOpE();
    auto pomeIeJeOpEdotJ = eFrmJqc->pomeOeOpEdot();
    pomeiIeJeKepEJ = pomeIeJeOpEJ->dot(aAjOKe);
    pomeiIeJeKepEdotJ = pomeIeJeOpEdotJ->dot(aAjOKe);
}

FRowDsptr OmeCompIeJeqKe::pvaluepEJ()
{
    return pomeiIeJeKepEJ;
}

FRowDsptr OmeCompIeJeqKe::pvaluepEdotJ()
{
    return pomeiIeJeKepEdotJ;
}
