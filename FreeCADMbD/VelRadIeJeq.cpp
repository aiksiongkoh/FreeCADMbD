#include "VelRadIeJeq.h"
#include "EndFrameqt.h"

using namespace MbD;

std::shared_ptr<VelRadIeJeq> VelRadIeJeq::With()
{
    auto inst = std::make_shared<VelRadIeJeq>();
    inst->initialize();
    return inst;
}

std::shared_ptr<VelRadIeJeq> VelRadIeJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<VelRadIeJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void VelRadIeJeq::initialize()
{
    VelRadIeJe::initialize();
    pvIeJepXJ = FullRow<double>::With(3);
    pvIeJepEJ = FullRow<double>::With(4);
    pvIeJepXdotJ = FullRow<double>::With(3);
    pvIeJepEdotJ = FullRow<double>::With(4);
}

void VelRadIeJeq::simUpdateAll()
{
    VelRadIeJe::simUpdateAll();
    if (rIeJe == 0.0) return;
    auto eFrmJeq = std::static_pointer_cast<EndFrameq>(eFrmJ);
    auto prIeJeOpEJ = eFrmJeq->prOeOpE;
    auto prIeJeOpEJT = prIeJeOpEJ->transpose();
    auto pvIeJeOpEJT = eFrmJeq->pvOeOpE()->transpose();
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

FRowDsptr VelRadIeJeq::pvaluepEdotJ()
{
    return pvIeJepEdotJ;
}

FRowDsptr VelRadIeJeq::pvaluepEJ()
{
    return pvIeJepEJ;
}

FRowDsptr VelRadIeJeq::pvaluepXdotJ()
{
    return pvIeJepXdotJ;
}

FRowDsptr VelRadIeJeq::pvaluepXJ()
{
    return pvIeJepXJ;
}
