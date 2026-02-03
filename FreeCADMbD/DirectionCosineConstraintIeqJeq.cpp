/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIeqJeq.h"
#include "DirectionCosineIeqcJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeqJeq> DirectionCosineConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIeqJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIeqJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqcJeqc::With(frmIe, frmJe, axisI, axisJ);
}

std::string MbD::DirectionCosineConstraintIeqJeq::constraintSpec()
{
    return "DirectionCosineConstraintIeJe";
}

void DirectionCosineConstraintIeqJeq::simUpdateAll()
{
    //aG = aAijIeJe - aConstant;
    ConstraintIeJe::simUpdateAll();
    auto aAijIeqJqe = std::static_pointer_cast<DirectionCosineIeqcJeqc>(aAijIeJe);
    pGpEJ = aAijIeqJqe->pAijIeJepEJ;
    ppGpEIpEJ = aAijIeqJqe->ppAijIeJepEIpEJ;
    ppGpEJpEJ = aAijIeqJqe->ppAijIeJepEJpEJ;
}

void DirectionCosineConstraintIeqJeq::calcG()
{
    //aG = aAijIeJe - aConstant;
    aG = aAijIeJe->value() - aConstant;
}

void DirectionCosineConstraintIeqJeq::calcpGpXI()
{
    //pGpXI = [0];
    assert(!pGpXI);
}

void DirectionCosineConstraintIeqJeq::calcpGpEI()
{
    pGpEI = aAijIeJe->pvaluepEI();
}

void DirectionCosineConstraintIeqJeq::calcpGpXJ()
{
    //pGpXJ = [0];
    assert(!pGpXJ);
}

void DirectionCosineConstraintIeqJeq::calcpGpEJ()
{
    pGpEJ = aAijIeJe->pvaluepEJ();
}

void DirectionCosineConstraintIeqJeq::calcppGpXIpXI()
{
    //ppGpXIpXI = [0];
    assert(!ppGpXIpXI);
}

void DirectionCosineConstraintIeqJeq::calcppGpXIpEI()
{
    //ppGpXIpEI = [0];
    assert(!ppGpXIpEI);
}

void DirectionCosineConstraintIeqJeq::calcppGpXIpXJ()
{
    //ppGpXIpXJ = [0];
    assert(!ppGpXIpXJ);
}

void DirectionCosineConstraintIeqJeq::calcppGpXIpEJ()
{
    //ppGpXIpEJ = [0];
    assert(!ppGpXIpEJ);
}

void DirectionCosineConstraintIeqJeq::calcppGpEIpEI()
{
    ppGpEIpEI = aAijIeJe->ppvaluepEIpEI();
}

void DirectionCosineConstraintIeqJeq::calcppGpEIpXJ()
{
    //ppGpEIpXJ = [0];
    assert(!ppGpEIpXJ);
}

void DirectionCosineConstraintIeqJeq::calcppGpEIpEJ()
{
    ppGpEIpEJ = aAijIeJe->ppvaluepEIpEJ();
}

void DirectionCosineConstraintIeqJeq::calcppGpXJpXJ()
{
    //ppGpXJpXJ = [0];
    assert(!ppGpXJpXJ);
}

void DirectionCosineConstraintIeqJeq::calcppGpXJpEJ()
{
    //ppGpXJpEJ = [0];
    assert(!ppGpXJpEJ);
}

void DirectionCosineConstraintIeqJeq::calcppGpEJpEJ()
{
    ppGpEJpEJ = aAijIeJe->ppvaluepEJpEJ();
}

void DirectionCosineConstraintIeqJeq::useEquationNumbers()
{
    ConstraintIeJe::useEquationNumbers();
}

void DirectionCosineConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpy(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpydot(mat);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    ConstraintIeJe::fillPosICError(col);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void DirectionCosineConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillPosICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
    auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
    mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIeqJeq::fillPosKineJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillPosKineJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillVelICJacob(mat);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIeqJeq::fillAccICIterError(FColDsptr col)
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

void MbD::DirectionCosineConstraintIeqJeq::initialize()
{
    ConstraintIeJe::initialize();
    initaAijIeJe();
}

void MbD::DirectionCosineConstraintIeqJeq::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
    aAijIeJe->initializeLocally();
}

void MbD::DirectionCosineConstraintIeqJeq::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
    aAijIeJe->initializeGlobally();
}
