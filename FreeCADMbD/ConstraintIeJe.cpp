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
#include "System.h"

using namespace MbD;

std::shared_ptr<ConstraintIeJe> ConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<ConstraintIeJe>();
}

void ConstraintIeJe::initialize()
{
    Constraint::initialize();
    dispIeJeO = DispIeJeO::With(frmIe, frmJe);
    dispIeJeO->owner = this;
}

void MbD::ConstraintIeJe::initializeLocally()
{
    dispIeJeO->initializeLocally();
}

void MbD::ConstraintIeJe::initializeGlobally()
{
    // Not needed. Done by System.dispIeJeOs
    // dispIeJeO->initializeGlobally();
}

void ConstraintIeJe::useUniqueDispIeJeO()
{
    auto dispIeJeOs = root()->dispIeJeOs;
    auto it = std::find_if(dispIeJeOs->begin(), dispIeJeOs->end(), [&](auto disp) {return disp->hasSameEndFrms(dispIeJeO); });
    if (it == dispIeJeOs->end()) {
        dispIeJeOs->push_back(dispIeJeO);
    }
    else {
        dispIeJeO = *it;
    }
}

void MbD::ConstraintIeJe::useUniqueDispIeJeKe()
{
    //Do nothing.
}

void MbD::ConstraintIeJe::prePosIC()
{
    dispIeJeO->prePosIC();
    lam = 0.0;
    iG = SIZE_MAX;
    Constraint::prePosIC();
}

void MbD::ConstraintIeJe::postPosICIteration()
{
    dispIeJeO->postPosICIteration();
    Constraint::postPosICIteration();
}

void MbD::ConstraintIeJe::preVelIC()
{
    dispIeJeO->preVelIC();
    Constraint::preVelIC();
}

void MbD::ConstraintIeJe::preAccIC()
{
    dispIeJeO->preAccIC();
    Constraint::preAccIC();
}

void MbD::ConstraintIeJe::preDyn()
{
    dispIeJeO->preDyn();
    Constraint::preDyn();
}

void MbD::ConstraintIeJe::preDynOutput()
{
    dispIeJeO->preDynOutput();
    Constraint::preDynOutput();
}

void MbD::ConstraintIeJe::postInput()
{
    dispIeJeO->postInput();
    lam = 0.0;
    Constraint::postInput();
}

void MbD::ConstraintIeJe::simUpdateAll()
{
    //Update locally only.
    //Objects that Constraints depend on have already executed simUpdateAll().
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

void MbD::ConstraintIeJe::calcpGpXI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcpGpXI is not implemented.");
}

void MbD::ConstraintIeJe::calcpGpEI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcpGpEI is not implemented.");
}

void MbD::ConstraintIeJe::calcpGpXJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcpGpXJ is not implemented.");
}

void MbD::ConstraintIeJe::calcpGpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcpGpEJ is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpXIpXI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXIpXI is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpXIpEI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXIpEI is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpXIpXJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXIpXJ is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpXIpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXIpEJ is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpEIpEI()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpEIpEI is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpEIpXJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpEIpXJ is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpEIpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpEIpEJ is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpXJpXJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXJpXJ is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpXJpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpXJpEJ is not implemented.");
}

void MbD::ConstraintIeJe::calcppGpEJpEJ()
{
    throw SimulationStoppingError("ConstraintIeJe::calcppGpEJpEJ is not implemented.");
}

std::string ConstraintIeJe::constraintSpec()
{
    return "ConstraintIeJe";
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
