/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIeqtJeq.h"
#include "DirectionCosineIeqctJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeqtJeq> DirectionCosineConstraintIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIeqtJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIeqtJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqctJeqc::With(frmIe, frmJe, axisI, axisJ);
}

void DirectionCosineConstraintIeqtJeq::fillpFpy(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIeqtJeq::fillpFpydot(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIeqtJeq::fillPosKineJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIeqtJeq::fillVelICJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIeqtJeq::fillAccICIterError(FColDsptr col)
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

void MbD::DirectionCosineConstraintIeqtJeq::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
    aAijIeJe->initializeLocally();
}

void MbD::DirectionCosineConstraintIeqtJeq::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
    aAijIeJe->initializeGlobally();
}
