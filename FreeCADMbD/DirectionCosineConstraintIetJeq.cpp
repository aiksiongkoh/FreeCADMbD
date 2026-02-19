/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIetJeq.h"
#include "DirectionCosineIectJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIetJeq> DirectionCosineConstraintIetJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIetJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIetJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIectJeqc::With(frmIe, frmJe, axisI, axisJ);
}

void DirectionCosineConstraintIetJeq::fillpFpy(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIetJeq::fillpFpydot(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIetJeq::fillPosKineJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIetJeq::fillVelICJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIetJeq::fillAccICIterError(FColDsptr col)
{
    ConstraintIeJe::fillAccICIterError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(frmIe);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(frmJe);
    auto qEdotI = eFrmIqc->qEdot();
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ))) * 2.0;
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}

void MbD::DirectionCosineConstraintIetJeq::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
    aAijIeJe->initializeLocally();
}

void MbD::DirectionCosineConstraintIetJeq::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
    aAijIeJe->initializeGlobally();
}
