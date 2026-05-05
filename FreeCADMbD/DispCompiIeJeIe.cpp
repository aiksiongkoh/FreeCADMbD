/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <algorithm>

#include "DispCompiIeJeIe.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<DispCompiIeJeIe> DispCompiIeJeIe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompiIeJeIe>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompiIeJeIe::initialize()
{
    Kinematic::initialize();
    dispIeJeIe = DispIeJeKe::With(eFrmI, eFrmJ, eFrmI);
    dispIeJeIe->owner = this;
}

void MbD::DispCompiIeJeIe::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    //rIeJeIe = aAIeO * rIeJeO
    //riIeJeIe = aArowiIeO dot rIeJeO = aAcoljOIe dot rIeJeO
    // Do nothing. rIeJeIe is updated by rIeJeKe
}

void MbD::DispCompiIeJeIe::useUniqueDispIeJeKe()
{
    if (!dispIeJeIe)
        return;
    auto dispIeJeKes = root()->dispIeJeKes;
    auto it = std::find_if(dispIeJeKes->begin(), dispIeJeKes->end(), [&](auto disp)
                           { return disp->hasSameEndFrms(dispIeJeIe); });
    if (it == dispIeJeKes->end())
    {
        dispIeJeKes->push_back(dispIeJeIe);
    }
    else
    {
        dispIeJeIe = *it;
    }
}

double DispCompiIeJeIe::value()
{
    return dispIeJeIe->rIeJeKe->at(axis);
}

FRowDsptr MbD::DispCompiIeJeIe::pvaluepEI()
{
    // rIeJeIe = aAOIeT * rIeJeO
    // prIeJeIepEI = pAOIeTpEI * rIeJeO + aAOIeT * prIeJeOpEI
    auto term1 = componentRowFrom(kineVector()->getpVectorpEI());
    auto term2 = componentRowFrom(kineVector()->getpVectorpEK());
    return term1->plusFullRow(term2);
}

FMatDsptr MbD::DispCompiIeJeIe::ppvaluepXIpEI()
{
    // rIeJeIe = aAOIeT * rIeJeO
    // prIeJeIepXI = aAOIeT * prIeJeOpXI
    // pprIeJeIepXIpEI = pAOIeTpEI * prIeJeOpXI
    return componentMatrixFrom(kineVector()->getppVectorpXIpEK());
}

FMatDsptr MbD::DispCompiIeJeIe::ppvaluepEIpEI()
{
    // rIeJeIe = aAOIeT * rIeJeO
    // prIeJeIepEI = pAOIeTpEI * rIeJeO + aAOIeT * prIeJeOpEI
    // pprIeJeIepEIpEI = ppAOIeTpEIpEI * rIeJeO + pAOIeTpEI * prIeJeOpEI + (pAOIeTpEI * prIeJeOpEI)T + aAOIeT * pprIeJeOpEIpEI
    auto term1 = componentMatrixFrom(kineVector()->getppVectorpEIpEI());
    auto term2 = componentMatrixFrom(kineVector()->getppVectorpEIpEK());
    auto term3 = componentMatrixFrom(kineVector()->getppVectorpEKpEK());
    return term1->plusFullMatrix(term2)->plusFullMatrix(term2->transpose())->plusFullMatrix(term3);
}

FMatDsptr MbD::DispCompiIeJeIe::ppvaluepEIpXJ()
{
    // rIeJeIe = aAOIeT * rIeJeO
    // prIeJeIepXJ = aAOIeT * prIeJeOpXJ
    // pprIeJeIepEIpXJ = pAOIeTpEI * prIeJeOpXJ
    return componentMatrixFrom(kineVector()->getppVectorpXJpEK())->transpose();
}

FMatDsptr MbD::DispCompiIeJeIe::ppvaluepEIpEJ()
{
    // rIeJeIe = aAOIeT * rIeJeO
    // prIeJeIepEJ = aAOIeT * prIeJeOpEJ
    // pprIeJeIepEIpEJ = pAOIeTpEI * prIeJeOpEJ
    return componentMatrixFrom(kineVector()->getppVectorpEJpEK())->transpose();
}

FRowDsptr MbD::DispCompiIeJeIe::ppvaluepXIpt()
{
    // rIeJeIe = aAOIeT * rIeJeO
    // prIeJeIepXI = aAOIeT * prIeJeOpXI
    // prIeJeIepXIpt = pAOIeTpt * prIeJeOpXI
    return componentRowFrom(kineVector()->getppVectorpXIpt());
}

FRowDsptr MbD::DispCompiIeJeIe::ppvaluepEIpt()
{
    // rIeJeIe = aAOIeT * rIeJeO
    // prIeJeIepEI = pAOIeEI * rIeJeO + aAOIeT * prIeJeOpEI
    // prIeJeIepEIpt = ppAOIeEIpt * rIeJeO + pAOIeEI * prIeJeOpt +  + pAOIeTpt * prIeJeOpEI + aAOIeT * pprIeJeOpEIpt
    auto term1 = componentRowFrom(kineVector()->getppVectorpEIpt());
    auto term2 = componentRowFrom(kineVector()->getppVectorpEKpt());
    return term1->plusFullRow(term2);
}

std::shared_ptr<KinematicVectorIeJe> DispCompiIeJeIe::kineVector() const
{
    return dispIeJeIe;
}

FColDsptr DispCompiIeJeIe::currentVector() const
{
    return dispIeJeIe->rIeJeKe;
}
