#include "OmeCompIeqJeKeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<OmeCompIeqJeKeq> OmeCompIeqJeKeq::With()
{
    auto inst = std::make_shared<OmeCompIeqJeKeq>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeqJeKeq> OmeCompIeqJeKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OmeCompIeqJeKeq>(frmi, frmj);
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
    aAjOKe = efrmK->aAjOe(axisK);
    auto eFrmIqc = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto efrmKqc = std::static_pointer_cast<EndFrameq>(efrmK);
    omeIeJeO = eFrmIqc->omeOeO()->negated();    //omeOJeO is zero
    omeiIeJeKe = aAjOKe->dot(omeIeJeO);
    auto pAjOKepEK = efrmKqc->pAjOepE(axisK);
    pomeiIeJeKepEK = pAjOKepEK->dot(omeIeJeO);
    auto pomeIeJeOpEI = eFrmIqc->pomeOeOpE()->negated();    //pomeOJeOpE is zero
    auto pomeIeJeOpEdotI = eFrmIqc->pomeOeOpEdot()->negated();    //pomeOJeOpEdot is zero
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
