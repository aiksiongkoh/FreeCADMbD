#include "VelRadIeqcJec.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<VelRadIeqcJec> VelRadIeqcJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIeqcJec>(frmi, frmj);
    inst->initialize();
    return inst;
}

void VelRadIeqcJec::initialize()
{
    VelRadIecJec::initialize();
    pvIeJepXI = FullRow<double>::With(3);
    pvIeJepEI = FullRow<double>::With(4);
    pvIeJepXdotI = FullRow<double>::With(3);
    pvIeJepEdotI = FullRow<double>::With(4);
}

void VelRadIeqcJec::calcPostDynCorrectorIteration()
{
    VelRadIecJec::calcPostDynCorrectorIteration();
    if (rIeJe == 0.0) return;
    auto muIeJeO = uIeJeO->negated();
    auto efrmqcI = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto& mprIeJeOpEI = efrmqcI->prOeOpE;
    auto mprIeJeOpEIT = mprIeJeOpEI->transpose();
    auto mpvIeJeOpEIT = efrmqcI->pvOeOpE()->transpose();
    auto muIeJeOT = muIeJeO->transpose();
    auto& prIeJepXI = muIeJeOT;
    auto prIeJepEI = muIeJeOT->timesFullMatrix(mprIeJeOpEI);
    for (size_t i = 0; i < 3; i++) {
        pvIeJepXI->atiput(i, (-vIeJe*prIeJepXI->at(i) - vIeJeO->at(i)) / rIeJe);
    }
    for (size_t i = 0; i < 4; i++) {
        pvIeJepEI->atiput(i, (-vIeJe*prIeJepEI->at(i) - mpvIeJeOpEIT->at(i)->dot(rIeJeO) - mprIeJeOpEIT->at(i)->dot(vIeJeO)) / rIeJe);
    }
    pvIeJepXdotI = prIeJepXI;
    pvIeJepEdotI = prIeJepEI;
}

FRowDsptr VelRadIeqcJec::pvaluepEdotI()
{
    return pvIeJepEdotI;
}

FRowDsptr VelRadIeqcJec::pvaluepEI()
{
    return pvIeJepEI;
}

FRowDsptr VelRadIeqcJec::pvaluepXdotI()
{
    return pvIeJepXdotI;
}

FRowDsptr VelRadIeqcJec::pvaluepXI()
{
    return pvIeJepXI;
}
