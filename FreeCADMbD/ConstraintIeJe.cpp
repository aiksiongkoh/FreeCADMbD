/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ConstraintIeJe.h"
#include "EndFrameq.h"
#include "SimulationStoppingError.h"
#include "System.h"

using namespace MbD;

void ConstraintIeJe::preStatic()
{
    Constraint::preStatic();
}

std::shared_ptr<ConstraintIeJe> ConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    // Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<ConstraintIeJe>();
}

void ConstraintIeJe::initialize()
{
    Constraint::initialize();
    dispIeJeO = DispIeJeO::With(eFrmI, eFrmJ);
    dispIeJeO->owner = this;
}

void ConstraintIeJe::initializeLocally()
{
}

void ConstraintIeJe::initializeGlobally()
{
}

void ConstraintIeJe::useUniqueDispIeJeO()
{
    auto dispIeJeOs = root()->dispIeJeOs;
    auto it = std::find_if(dispIeJeOs->begin(), dispIeJeOs->end(), [&](auto disp)
                           { return disp->hasSameEndFrms(dispIeJeO); });
    if (it == dispIeJeOs->end())
    {
        dispIeJeOs->push_back(dispIeJeO);
    }
    else
    {
        dispIeJeO = *it;
    }
}

void ConstraintIeJe::useUniqueDispIeJeKe()
{
    // Do nothing.
}

void ConstraintIeJe::prePosIC()
{
    Constraint::prePosIC();
    lam = 0.0;
    iG = SIZE_MAX;
}

void ConstraintIeJe::postPosICIteration()
{
    Constraint::postPosICIteration();
}

void ConstraintIeJe::preVelIC()
{
    Constraint::preVelIC();
}

void ConstraintIeJe::preAccIC()
{
    Constraint::preAccIC();
}

void ConstraintIeJe::preDyn()
{
    Constraint::preDyn();
}

void ConstraintIeJe::preDynOutput()
{
    Constraint::preDynOutput();
}

void ConstraintIeJe::postInput()
{
    lam = 0.0;
    Constraint::postInput();
}

void ConstraintIeJe::simUpdateAll()
{
    // Update locally only.
    // Objects that Constraints depend on have already executed simUpdateAll().
    rIeJeO = dispIeJeO->rIeJeO;
    calcG();
    // calcpGpXI();
    // calcpGpEI();
    // calcpGpXJ();
    // calcpGpEJ();
    // calcppGpXIpXI();
    // calcppGpXIpEI();
    // calcppGpXIpXJ();
    // calcppGpXIpEJ();
    // calcppGpEIpEI();
    // calcppGpEIpXJ();
    // calcppGpEIpEJ();
    // calcppGpXJpXJ();
    // calcppGpXJpEJ();
    // calcppGpEJpEJ();
}

void ConstraintIeJe::calcG()
{
    throw SimulationStoppingError("ConstraintIeJe::calcG is not implemented.");
}

void ConstraintIeJe::calcpGpXI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcpGpXI is not implemented.");
}

void ConstraintIeJe::calcpGpEI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcpGpEI is not implemented.");
}

void ConstraintIeJe::calcpGpXJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcpGpXJ is not implemented.");
}

void ConstraintIeJe::calcpGpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcpGpEJ is not implemented.");
}

void ConstraintIeJe::calcppGpXIpXI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXIpXI is not implemented.");
}

void ConstraintIeJe::calcppGpXIpEI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXIpEI is not implemented.");
}

void ConstraintIeJe::calcppGpXIpXJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXIpXJ is not implemented.");
}

void ConstraintIeJe::calcppGpXIpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXIpEJ is not implemented.");
}

void ConstraintIeJe::calcppGpEIpEI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpEIpEI is not implemented.");
}

void ConstraintIeJe::calcppGpEIpXJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpEIpXJ is not implemented.");
}

void ConstraintIeJe::calcppGpEIpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpEIpEJ is not implemented.");
}

void ConstraintIeJe::calcppGpXJpXJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXJpXJ is not implemented.");
}

void ConstraintIeJe::calcppGpXJpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXJpEJ is not implemented.");
}

void ConstraintIeJe::calcppGpEJpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpEJpEJ is not implemented.");
}

std::string ConstraintIeJe::constraintSpec()
{
    return "ConstraintIeJe";
}

ConstraintType ConstraintIeJe::type()
{
    return Constraint::type();
}

void ConstraintIeJe::addToJointForceJ(FColDsptr col)
{
    // aFJeO = lam * pGpXJ
    throw SimulationStoppingError("To be implemented.");
}

void ConstraintIeJe::addToJointTorqueJ(FColDsptr col)
{
    // aTJeO = 0.5 * aBOJp * (lam * pGpEJ - prOJeOpEJT * aFJeO)
    throw SimulationStoppingError("To be implemented.");
}
