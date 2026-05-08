#include "OmeCompIeqcJecKeqc.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<OmeCompIeqcJecKeqc> OmeCompIeqcJecKeqc::With()
{
    auto inst = std::make_shared<OmeCompIeqcJecKeqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeqcJecKeqc> OmeCompIeqcJecKeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OmeCompIeqcJecKeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void OmeCompIeqcJecKeqc::initialize()
{
    OmeCompIecJecKec::initialize();
    pomeiIeJeKepEI = FullRow<double>::With(4);
    pomeiIeJeKepEdotI = FullRow<double>::With(4);
}

void OmeCompIeqcJecKeqc::simUpdateAll()
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

FRowDsptr OmeCompIeqcJecKeqc::pvaluepEI()
{
    return pomeiIeJeKepEI;
}

FRowDsptr OmeCompIeqcJecKeqc::pvaluepEdotI()
{
    return pomeiIeJeKepEdotI;
}
