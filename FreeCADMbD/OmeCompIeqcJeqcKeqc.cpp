#include "OmeCompIeqcJeqcKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<OmeCompIeqcJeqcKeqc> OmeCompIeqcJeqcKeqc::With()
{
    auto inst = std::make_shared<OmeCompIeqcJeqcKeqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeqcJeqcKeqc> OmeCompIeqcJeqcKeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OmeCompIeqcJeqcKeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeqcJeqcKeqc> OmeCompIeqcJeqcKeqc::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    auto inst = std::make_shared<OmeCompIeqcJeqcKeqc>(frmi, frmj, efrmK, axisK);
    inst->initialize();
    return inst;
}

void OmeCompIeqcJeqcKeqc::initialize()
{
    OmeCompIeqcJecKeqc::initialize();
    pomeiIeJeKepEJ = FullRow<double>::With(4);
    pomeiIeJeKepEdotJ = FullRow<double>::With(4);
}

void OmeCompIeqcJeqcKeqc::simUpdateAll()
{
    //omeIeJeO = omeOJeO - omeOIeO
    //omeIeJeKe = AKeO * omeIeJeO
    //omeiIeJeKe = ArowiKeO dot omeIeJeO = AcoljOKe dot omeIeJeO
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto efrmKqc = std::static_pointer_cast<EndFrameqc>(efrmK);
    aAjOKe = efrmKqc->aAjOe(axisK);
    omeIeJeO = eFrmJqc->omeOeO()->minusFullColumn(eFrmIqc->omeOeO());
    omeiIeJeKe = aAjOKe->dot(omeIeJeO);
    auto pAjOKepEK = efrmKqc->pAjOepE(axisK);
    pomeiIeJeKepEK = pAjOKepEK->dot(omeIeJeO);
    auto pomeIeJeOpEI = eFrmIqc->pomeOeOpE()->negated();
    auto pomeIeJeOpEdotI = eFrmIqc->pomeOeOpEdot()->negated();
    pomeiIeJeKepEI = pomeIeJeOpEI->dot(aAjOKe);
    pomeiIeJeKepEdotI = pomeIeJeOpEdotI->dot(aAjOKe);
    auto pomeIeJeOpEJ = eFrmJqc->pomeOeOpE();
    auto pomeIeJeOpEdotJ = eFrmJqc->pomeOeOpEdot();
    pomeiIeJeKepEJ = pomeIeJeOpEJ->dot(aAjOKe);
    pomeiIeJeKepEdotJ = pomeIeJeOpEdotJ->dot(aAjOKe);
}

FRowDsptr OmeCompIeqcJeqcKeqc::pvaluepEJ()
{
    return pomeiIeJeKepEJ;
}

FRowDsptr OmeCompIeqcJeqcKeqc::pvaluepEdotJ()
{
    return pomeiIeJeKepEdotJ;
}
