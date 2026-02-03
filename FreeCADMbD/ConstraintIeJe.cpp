/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstraintIeJe.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ConstraintIeJe> ConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<ConstraintIeJe>();
}

void ConstraintIeJe::initialize()
{
    Item::initialize();
    dispIeJeO = DispIecJecO::With(frmIe, frmJe);
    aConstant = 0.0;
}

void MbD::ConstraintIeJe::initializeLocally()
{
    dispIeJeO->initializeLocally();
}

void MbD::ConstraintIeJe::initializeGlobally()
{
    dispIeJeO->initializeGlobally();
}

void MbD::ConstraintIeJe::useEquationNumbers()
{
    iqXI = frmIe->iqX();
    iqEI = frmIe->iqE();
    iqXJ = frmJe->iqX();
    iqEJ = frmJe->iqE();
}

void MbD::ConstraintIeJe::simUpdateAll()
{
    dispIeJeO->simUpdateAll();
    calcG();
    calcpGpXI();
    calcpGpEI();
    calcpGpXJ();
    calcpGpEJ();
    calcppGpXIpXI();
    calcppGpXIpEI();
    calcppGpXIpXJ();
    calcppGpXIpEJ();
    calcppGpEIpEI();
    calcppGpEIpXJ();
    calcppGpEIpEJ();
    calcppGpXJpXJ();
    calcppGpXJpEJ();
    calcppGpEJpEJ();
}

std::string ConstraintIeJe::constraintSpec()
{
    return "ConstraintIeJe";
}

void ConstraintIeJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIeJe::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIeJe::addToJointForceJ(FColDsptr col)
{
    //aFJeO = lam * pGpXJ
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIeJe::addToJointTorqueJ(FColDsptr col)
{
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - prOJeOpEJT * aFJeO)
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr ConstraintIeJe::getrIeJeO()
{
    return frmJe->rOeO->minusFullColumn(frmIe->rOeO);
}
