#include "OmeCompIeqcJecKeqc.h"
#include "EndFrameqc.h"

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
    OmeCompIecJecKeqc::initialize();
    pomeiIeJeKepEI = FullRow<double>::With(4);
    pomeiIeJeKepEdotI = FullRow<double>::With(4);
}

void OmeCompIeqcJecKeqc::calcPostDynCorrectorIteration()
{
    OmeCompIecJecKeqc::calcPostDynCorrectorIteration();
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto mpomeIeJeOpEI = eFrmIqc->pomeOeOpE();
    auto mpomeIeJeOpEdotI = eFrmIqc->pomeOeOpEdot();
    auto mAjOKe = aAjOKe->negated();
    pomeiIeJeKepEI = mpomeIeJeOpEI->dot(mAjOKe);
    pomeiIeJeKepEdotI = mpomeIeJeOpEdotI->dot(mAjOKe);
}

FRowDsptr OmeCompIeqcJecKeqc::pvaluepEI()
{
    return pomeiIeJeKepEI;
}

FRowDsptr OmeCompIeqcJecKeqc::pvaluepEdotI()
{
    return pomeiIeJeKepEdotI;
}
