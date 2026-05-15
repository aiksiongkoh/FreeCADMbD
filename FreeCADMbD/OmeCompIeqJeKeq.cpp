#include "OmeCompIeqJeKeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<OmeCompIeqJeKeq> OmeCompIeqJeKeq::With()
{
    auto inst = std::make_shared<OmeCompIeqJeKeq>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeqJeKeq> OmeCompIeqJeKeq::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    auto inst = std::make_shared<OmeCompIeqJeKeq>(frmi, frmj, frmk, axisk);
    inst->initialize();
    return inst;
}

void OmeCompIeqJeKeq::initialize()
{
    OmeCompIeJeKe::initialize();
    pomeiIeJeKepEI = FullRow<double>::With(4);
    pomeiIeJeKepEdotI = FullRow<double>::With(4);
}

void OmeCompIeqJeKeq::simUpdateAll()
{
    //omeIeJeO = omeOJeO - omeOIeO
    //omeIeJeKe = AKeO * omeIeJeO
    //omeiIeJeKe = ArowiKeO dot omeIeJeO = AcoljOKe dot omeIeJeO
    aAjOKe = eFrmK->aAjOe(axisK);
    auto eFrmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto eFrmKeq = std::static_pointer_cast<EndFrameq>(eFrmK);
    omeIeJeO = eFrmIeq->omeOeO()->negated();    //omeOJeO is zero
    omeiIeJeKe = aAjOKe->dot(omeIeJeO);
    auto pAjOKepEK = eFrmKeq->pAjOepE(axisK);
    pomeiIeJeKepEK = pAjOKepEK->dot(omeIeJeO);
    auto pomeIeJeOpEI = eFrmIeq->pomeOeOpE()->negated();    //pomeOJeOpE is zero
    auto pomeIeJeOpEdotI = eFrmIeq->pomeOeOpEdot()->negated();    //pomeOJeOpEdot is zero
    pomeiIeJeKepEI = pomeIeJeOpEI->dot(aAjOKe);
    pomeiIeJeKepEdotI = pomeIeJeOpEdotI->dot(aAjOKe);
}

FRowDsptr OmeCompIeqJeKeq::pvaluepEI()
{
    return pomeiIeJeKepEI;
}

FRowDsptr OmeCompIeqJeKeq::pvaluepEdotI()
{
    return pomeiIeJeKepEdotI;
}
