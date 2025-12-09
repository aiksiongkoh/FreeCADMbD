#include "OmeCompIecJecKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<OmeCompIecJecKeqc> OmeCompIecJecKeqc::With()
{
    auto inst = std::make_shared<OmeCompIecJecKeqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIecJecKeqc> OmeCompIecJecKeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<OmeCompIecJecKeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void OmeCompIecJecKeqc::initialize()
{
    OmeCompIecJecKec::initialize();
    pomeiIeJeKepEK = FullRow<double>::With(4);
}

void OmeCompIecJecKeqc::calcPostDynCorrectorIteration()
{
    OmeCompIecJecKec::calcPostDynCorrectorIteration();
    auto efrmKqc = std::static_pointer_cast<EndFrameqc>(efrmK);
    auto pAjOKepEK = efrmKqc->pAjOepE(axisK);
    pomeiIeJeKepEK = pAjOKepEK->dot(omeIeJeO);
}

FRowDsptr OmeCompIecJecKeqc::pvaluepEK()
{
    return FRowDsptr();
}
