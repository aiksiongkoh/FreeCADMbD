/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIeqJeq.h"
#include "DispCompIeqcJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIeqJeq> AtPointConstraintIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIeqJeq>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIeqJeq::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
}

void AtPointConstraintIeqJeq::simUpdateAll()
{
    //riIeJeO = rOJeO - rOIeO;
    //aG = riIeJeO - C;
    ConstraintIeJe::simUpdateAll();
}

void MbD::AtPointConstraintIeqJeq::calcG()
{
    auto rIeJeO = dispIeJeO->rIeJeO;
    aG = rIeJeO->at(axis) - aConstant;
}

void MbD::AtPointConstraintIeqJeq::calcpGpXI()
{
    //pGpXI = [-I];
    pGpXI = dispIeJeO->getprIeJeOpXI()->at(axis);
}

void MbD::AtPointConstraintIeqJeq::calcpGpEI()
{
    pGpEI = dispIeJeO->getprIeJeOpEI()->at(axis);
}

void MbD::AtPointConstraintIeqJeq::calcpGpXJ()
{
    //pGpXJ = [I];
    pGpXJ = dispIeJeO->getprIeJeOpXJ()->at(axis);
}

void MbD::AtPointConstraintIeqJeq::calcpGpEJ()
{
    pGpEJ = dispIeJeO->getprIeJeOpEJ()->at(axis);
}

void MbD::AtPointConstraintIeqJeq::calcppGpXIpXI()
{
    //ppGpXIpXI = [0];
    assert(!ppGpXIpXI);
}

void MbD::AtPointConstraintIeqJeq::calcppGpXIpEI()
{
    //ppGpXIpEI = [0];
    assert(!ppGpXIpEI);
}

void MbD::AtPointConstraintIeqJeq::calcppGpXIpXJ()
{
    //ppGpXIpXJ = [0];
    assert(!ppGpXIpXJ);
}

void MbD::AtPointConstraintIeqJeq::calcppGpXIpEJ()
{
    //ppGpXIpEJ = [0];
    assert(!ppGpXIpEJ);
}

void MbD::AtPointConstraintIeqJeq::calcppGpEIpEI()
{
    //ppGpEIpEI is constant for EndFrameqc, but not for EndFrameqct.
    ppGpEIpEI = dispIeJeO->getppriIeJeOpEIpEI(axis);
}

void MbD::AtPointConstraintIeqJeq::calcppGpEIpXJ()
{
    //ppGpEIpXJ = [0];
    assert(!ppGpEIpXJ);
}

void MbD::AtPointConstraintIeqJeq::calcppGpEIpEJ()
{
    //ppGpEIpEJ = [0];
    assert(!ppGpEIpEJ);
}

void MbD::AtPointConstraintIeqJeq::calcppGpXJpXJ()
{
    //ppGpXJpXJ = [0];
    assert(!ppGpXJpXJ);
}

void MbD::AtPointConstraintIeqJeq::calcppGpXJpEJ()
{
    //ppGpXJpEJ = [0];
    assert(!ppGpXJpEJ);
}

void MbD::AtPointConstraintIeqJeq::calcppGpEJpEJ()
{
    //ppGpEJpEJ is constant for EndFrameqc, but not for EndFrameqct.
    ppGpEJpEJ = dispIeJeO->getppriIeJeOpEJpEJ(axis);
}

void MbD::AtPointConstraintIeqJeq::initialize()
{
    ConstraintIeJe::initialize();
    initriIeJeO();
}

void MbD::AtPointConstraintIeqJeq::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
}

void AtPointConstraintIeqJeq::useEquationNumbers()
{
    ConstraintIeJe::useEquationNumbers();
}

void AtPointConstraintIeqJeq::fillpFpy(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpy(mat);
}

void AtPointConstraintIeqJeq::fillpFpydot(SpMatDsptr mat)
{
    ConstraintIeJe::fillpFpydot(mat);
}

std::string AtPointConstraintIeqJeq::constraintSpec()
{
    return "AtPointConstraintIJ";
}

void AtPointConstraintIeqJeq::fillPosICError(FColDsptr col)
{
    ConstraintIeJe::fillPosICError(col);
}

void AtPointConstraintIeqJeq::fillPosICJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillPosICJacob(mat);
}

void AtPointConstraintIeqJeq::fillPosKineJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillPosKineJacob(mat);
}

void AtPointConstraintIeqJeq::fillVelICJacob(SpMatDsptr mat)
{
    ConstraintIeJe::fillVelICJacob(mat);
}

void AtPointConstraintIeqJeq::fillAccICIterError(FColDsptr col)
{
    ConstraintIeJe::fillAccICIterError(col);
}
