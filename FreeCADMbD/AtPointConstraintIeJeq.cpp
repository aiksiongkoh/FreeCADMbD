/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIeJeq.h"
#include "DispCompIeqcJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIeJeq> AtPointConstraintIeJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIeJeq>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIeJeq::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
}

void AtPointConstraintIeJeq::simUpdateAll()
{
    //riIeJeO = rOJeO - rOIeO;
    //aG = riIeJeO - C;
    ConstraintIeJe::simUpdateAll();
}

void MbD::AtPointConstraintIeJeq::calcG()
{
    auto rIeJeO = dispIeJeO->rIeJeO;
    aG = rIeJeO->at(axis) - aConstant;
}

void MbD::AtPointConstraintIeJeq::calcpGpXI()
{
    //pGpXI = [0];
    assert(!pGpXI);
}

void MbD::AtPointConstraintIeJeq::calcpGpEI()
{
    //pGpEI = [0];
    assert(!pGpEI);
}

void MbD::AtPointConstraintIeJeq::calcpGpXJ()
{
    //pGpXJ = [I];
    pGpXJ = dispIeJeO->getprIeJeOpXJ()->at(axis);
}

void MbD::AtPointConstraintIeJeq::calcpGpEJ()
{
    pGpEJ = dispIeJeO->getprIeJeOpEJ()->at(axis);
}

void MbD::AtPointConstraintIeJeq::calcppGpXIpXI()
{
    //ppGpXIpXI = [0];
    assert(!ppGpXIpXI);
}

void MbD::AtPointConstraintIeJeq::calcppGpXIpEI()
{
    //ppGpXIpEI = [0];
    assert(!ppGpXIpEI);
}

void MbD::AtPointConstraintIeJeq::calcppGpXIpXJ()
{
    //ppGpXIpXJ = [0];
    assert(!ppGpXIpXJ);
}

void MbD::AtPointConstraintIeJeq::calcppGpXIpEJ()
{
    //ppGpXIpEJ = [0];
    assert(!ppGpXIpEJ);
}

void MbD::AtPointConstraintIeJeq::calcppGpEIpEI()
{
    //ppGpEIpEI = [0];
    assert(!ppGpEIpEI);
}

void MbD::AtPointConstraintIeJeq::calcppGpEIpXJ()
{
    //ppGpEIpXJ = [0];
    assert(!ppGpEIpXJ);
}

void MbD::AtPointConstraintIeJeq::calcppGpEIpEJ()
{
    //ppGpEIpEJ = [0];
    assert(!ppGpEIpEJ);
}

void MbD::AtPointConstraintIeJeq::calcppGpXJpXJ()
{
    //ppGpXJpXJ = [0];
    assert(!ppGpXJpXJ);
}

void MbD::AtPointConstraintIeJeq::calcppGpXJpEJ()
{
    //ppGpXJpEJ = [0];
    assert(!ppGpXJpEJ);
}

void MbD::AtPointConstraintIeJeq::calcppGpEJpEJ()
{
    //ppGpEJpEJ is constant for EndFrameqc, but not for EndFrameqct.
    ppGpEJpEJ = dispIeJeO->getppriIeJeOpEJpEJ(axis);
}

void MbD::AtPointConstraintIeJeq::initialize()
{
    ConstraintIeJe::initialize();
    initriIeJeO();
}

void MbD::AtPointConstraintIeJeq::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
}

void AtPointConstraintIeJeq::useEquationNumbers()
{
    ConstraintIeJe::useEquationNumbers();
}

void AtPointConstraintIeJeq::fillpFpy(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);

    auto ppGpXJpEJlam = ppGpXJpEJ->times(lam);

    mat->atijplusFullMatrixtimes(iqXJ, iqXJ, ppGpXJpXJ, lam);
    mat->atijplusFullMatrix(iqXJ, iqEJ, ppGpXJpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqXJ, ppGpXJpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIeJeq::fillpFpydot(SpMatDsptr mat)
{
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

std::string AtPointConstraintIeJeq::constraintSpec()
{
    return "AtPointConstraintIJ";
}

void AtPointConstraintIeJeq::fillPosICError(FColDsptr col)
{
    Constraint::fillPosICError(col);
    col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AtPointConstraintIeJeq::fillPosICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());

    auto ppGpXJpEJlam = ppGpXJpEJ->times(lam);

    mat->atijplusFullMatrixtimes(iqXJ, iqXJ, ppGpXJpXJ, lam);
    mat->atijplusFullMatrix(iqXJ, iqEJ, ppGpXJpEJlam);
    mat->atijplusTransposeFullMatrix(iqEJ, iqXJ, ppGpXJpEJlam);
    mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIeJeq::fillVelICJacob(SpMatDsptr mat)
{
    mat->atijplusFullRow(iG, iqXJ, pGpXJ);
    mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
    mat->atijplusFullRow(iG, iqEJ, pGpEJ);
    mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIeJeq::fillAccICIterError(FColDsptr col)
{
    ConstraintIeJe::fillAccICIterError(col);
    col->atiplusNumber(iqXJ + axis, lam);
    col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(frmJe);
    auto qEdotJ = eFrmJqc->qEdot();
    auto sum = eFrmJqc->qXddot()->at(axis);
    sum += pGpEJ->timesFullColumn(eFrmJqc->qEddot());
    sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
    col->atiplusNumber(iG, sum);
}
