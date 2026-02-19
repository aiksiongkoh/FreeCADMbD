/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstraintIJ.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ConstraintIJ> ConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<ConstraintIJ>();
}

void ConstraintIJ::initialize()
{
    Constraint::initialize();
}

std::string ConstraintIJ::constraintSpec()
{
    return "ConstraintIJ";
}

void ConstraintIJ::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIJ::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIJ::addToJointForceJ(FColDsptr col)
{
    //aFJeO = lam * pGpXJ
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIJ::addToJointTorqueJ(FColDsptr col)
{
    //aTJeO = 0.5 * aBOJp * (lam * pGpEJ - prOJeOpEJT * aFJeO)
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr ConstraintIJ::getrIeJeO()
{
    return eFrmJ->rOeO->minusFullColumn(eFrmI->rOeO);
}
