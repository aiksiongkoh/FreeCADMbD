#include "VelRadIeqcJeqc.h"
#include "EndFrameqct.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<VelRadIeqcJeqc> VelRadIeqcJeqc::With()
{
    auto inst = std::make_shared<VelRadIeqcJeqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<VelRadIeqcJeqc> VelRadIeqcJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIeqcJeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void VelRadIeqcJeqc::initialize()
{
    VelRadIeqcJec::initialize();
    pvIeJepXJ = FullRow<double>::With(3);
    pvIeJepEJ = FullRow<double>::With(4);
    pvIeJepXdotJ = FullRow<double>::With(3);
    pvIeJepEdotJ = FullRow<double>::With(4);
}

void VelRadIeqcJeqc::calcPostDynCorrectorIteration()
{
    VelRadIeqcJec::calcPostDynCorrectorIteration();
    if (rIeJe == 0.0) return;
    auto efrmqcJ = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto prIeJeOpEJ = efrmqcJ->prOeOpE;
    auto prIeJeOpEJT = prIeJeOpEJ->transpose();
    auto pvIeJeOpEJT = efrmqcJ->pvOeOpE()->transpose();
    auto uIeJeOT = uIeJeO->transpose();
    auto prIeJepXJ = uIeJeOT;
    auto prIeJepEJ = uIeJeOT->timesFullMatrix(prIeJeOpEJ);
    for (size_t i = 0; i < 3; i++) {
        pvIeJepXJ->atiput(i, (vIeJeO->at(i) - vIeJe * prIeJepXJ->at(i)) / rIeJe);
    }
    for (size_t i = 0; i < 4; i++) {
        pvIeJepEJ->atiput(i, (pvIeJeOpEJT->at(i)->dot(rIeJeO) + prIeJeOpEJT->at(i)->dot(vIeJeO) - vIeJe * prIeJepEJ->at(i)) / rIeJe);
    }
    pvIeJepXdotJ = prIeJepXJ;
    pvIeJepEdotJ = prIeJepEJ;
}

FRowDsptr VelRadIeqcJeqc::pvaluepEdotJ()
{
    return pvIeJepEdotJ;
}

FRowDsptr VelRadIeqcJeqc::pvaluepEJ()
{
    return pvIeJepEJ;
}

FRowDsptr VelRadIeqcJeqc::pvaluepXdotJ()
{
    return pvIeJepXdotJ;
}

FRowDsptr VelRadIeqcJeqc::pvaluepXJ()
{
    return pvIeJepXJ;
}
