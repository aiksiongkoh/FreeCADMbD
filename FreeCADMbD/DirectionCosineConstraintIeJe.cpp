/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineConstraintIeqJeq.h"
#include "EndFramect.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "DirectionCosineConstraintIeqtJeq.h"
#include "DirectionCosineConstraintIetJeq.h"
#include "DirectionCosineConstraintIeJe.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeJe> DirectionCosineConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    std::shared_ptr<DirectionCosineConstraintIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeqtJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameqc>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeqJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeqJe>(frmi, frmj, axisi, axisj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIetJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    else if (std::dynamic_pointer_cast<EndFramec>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    assert(inst);
    inst->initialize();
    return inst;
}

void MbD::DirectionCosineConstraintIeJe::simUpdateAll()
{
    ConstraintIeJe::simUpdateAll();
}

void MbD::DirectionCosineConstraintIeJe::calcG()
{
    //aG = aAijIeJe - aConstant;
    aG = aAijIeJe->value() - aConstant;
}

void MbD::DirectionCosineConstraintIeJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //aFIeO = lam * zero
    //Do nothing.
}

void MbD::DirectionCosineConstraintIeJe::addToJointForceJ(FColDsptr col)
{
    //aFJeO = lam * pGpXJ
    //aFJeO = lam * zero
    //Do nothing.
}

void MbD::DirectionCosineConstraintIeJe::addToJointTorqueI(FColDsptr col)
{
    //Do nothing.
}

void MbD::DirectionCosineConstraintIeJe::addToJointTorqueJ(FColDsptr col)
{
    //Do nothing.
}

ConstraintType MbD::DirectionCosineConstraintIeJe::type()
{
    return perpendicular;
}

std::string MbD::DirectionCosineConstraintIeJe::constraintSpec()
{
    return "DirectionCosineConstraintIeJe";
}

void MbD::DirectionCosineConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    aAijIeJe = DirectionCosineIecJec::With(frmIe, frmJe, axisI, axisJ);
}

void MbD::DirectionCosineConstraintIeJe::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
    aAijIeJe->initializeLocally();
}

void MbD::DirectionCosineConstraintIeJe::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
    aAijIeJe->initializeGlobally();
}

void MbD::DirectionCosineConstraintIeJe::postInput()
{
    aAijIeJe->postInput();
    ConstraintIeJe::postInput();
}

void MbD::DirectionCosineConstraintIeJe::prePosIC()
{
    aAijIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void MbD::DirectionCosineConstraintIeJe::postPosICIteration()
{
    aAijIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void MbD::DirectionCosineConstraintIeJe::preVelIC()
{
    aAijIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

void MbD::DirectionCosineConstraintIeJe::fillVelICJacob(SpMatDsptr mat)
{
    //Do nothing.
}

void MbD::DirectionCosineConstraintIeJe::preAccIC()
{
    aAijIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void MbD::DirectionCosineConstraintIeJe::fillAccICIterError(FColDsptr col)
{
    //Do nothing.
}

void MbD::DirectionCosineConstraintIeJe::preDyn()
{
    aAijIeJe->preDyn();
    ConstraintIeJe::preDyn();
}

void MbD::DirectionCosineConstraintIeJe::preDynOutput()
{
    aAijIeJe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void MbD::DirectionCosineConstraintIeJe::postDynOutput()
{
    aAijIeJe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}

void MbD::DirectionCosineConstraintIeJe::postDynPredictor()
{
    aAijIeJe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void DirectionCosineConstraintIeJe::postDynCorrectorIteration()
{
    aAijIeJe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void MbD::DirectionCosineConstraintIeJe::fillpFpy(SpMatDsptr mat)
{
    //Do nothing.
}

void MbD::DirectionCosineConstraintIeJe::fillpFpydot(SpMatDsptr mat)
{
    //Do nothing.
}

void MbD::DirectionCosineConstraintIeJe::fillPosICJacob(SpMatDsptr mat)
{
    //Do nothing.
}
