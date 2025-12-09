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

void OmeCompIeqcJeqcKeqc::initialize()
{
    OmeCompIeqcJecKeqc::initialize();
    pomeiIeJeKepEJ = FullRow<double>::With(4);
    pomeiIeJeKepEdotJ = FullRow<double>::With(4);
}

void OmeCompIeqcJeqcKeqc::calcPostDynCorrectorIteration()
{
    OmeCompIeqcJecKeqc::calcPostDynCorrectorIteration();
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
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
