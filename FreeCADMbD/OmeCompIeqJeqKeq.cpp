#include "OmeCompIeqJeqKeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<OmeCompIeqJeqKeq> OmeCompIeqJeqKeq::With()
{
    auto inst = std::make_shared<OmeCompIeqJeqKeq>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeqJeqKeq> OmeCompIeqJeqKeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OmeCompIeqJeqKeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeqJeqKeq> OmeCompIeqJeqKeq::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    auto inst = std::make_shared<OmeCompIeqJeqKeq>(frmi, frmj, efrmK, axisK);
    inst->initialize();
    return inst;
}

void OmeCompIeqJeqKeq::initialize()
{
    OmeCompIeqJeKeq::initialize();
    pomeiIeJeKepEJ = FullRow<double>::With(4);
    pomeiIeJeKepEdotJ = FullRow<double>::With(4);
}

void OmeCompIeqJeqKeq::simUpdateAll()
{
    //omeIeJeO = omeOJeO - omeOIeO
    //omeIeJeKe = AKeO * omeIeJeO
    //omeiIeJeKe = ArowiKeO dot omeIeJeO = AcoljOKe dot omeIeJeO
    auto eFrmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto eFrmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto efrmKqc = std::static_pointer_cast<EndFrameq>(efrmK);
    aAjOKe = efrmKqc->aAjOe(axisK);
    omeIeJeO = eFrmJeq->omeOeO()->minusFullColumn(eFrmIeq->omeOeO());
    omeiIeJeKe = aAjOKe->dot(omeIeJeO);
    auto pAjOKepEK = efrmKqc->pAjOepE(axisK);
    pomeiIeJeKepEK = pAjOKepEK->dot(omeIeJeO);
    auto pomeIeJeOpEI = eFrmIeq->pomeOeOpE()->negated();
    auto pomeIeJeOpEdotI = eFrmIeq->pomeOeOpEdot()->negated();
    pomeiIeJeKepEI = pomeIeJeOpEI->dot(aAjOKe);
    pomeiIeJeKepEdotI = pomeIeJeOpEdotI->dot(aAjOKe);
    auto pomeIeJeOpEJ = eFrmJeq->pomeOeOpE();
    auto pomeIeJeOpEdotJ = eFrmJeq->pomeOeOpEdot();
    pomeiIeJeKepEJ = pomeIeJeOpEJ->dot(aAjOKe);
    pomeiIeJeKepEdotJ = pomeIeJeOpEdotJ->dot(aAjOKe);
}

FRowDsptr OmeCompIeqJeqKeq::pvaluepEJ()
{
    return pomeiIeJeKepEJ;
}

FRowDsptr OmeCompIeqJeqKeq::pvaluepEdotJ()
{
    return pomeiIeJeKepEdotJ;
}
