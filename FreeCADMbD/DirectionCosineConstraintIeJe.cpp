/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineConstraintIeqJeq.h"
#include "EndFramet.h"
#include "EndFrameq.h"
#include "EndFrameqt.h"
#include "DirectionCosineConstraintIeqtJeq.h"
#include "DirectionCosineConstraintIetJeq.h"
#include "DirectionCosineConstraintIeJe.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeJe> DirectionCosineConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    std::shared_ptr<DirectionCosineConstraintIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeqtJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameq>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeqJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeqJe>(frmi, frmj, axisi, axisj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIetJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    else if (std::dynamic_pointer_cast<EndFrame>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    assert(inst);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIeJe::simUpdateAll()
{
    ConstraintIeJe::simUpdateAll();
}

void DirectionCosineConstraintIeJe::calcG()
{
    //aG = aAijIeJe - aConstant;
    aG = aAijIeJe->value() - aConstant;
}

void DirectionCosineConstraintIeJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //aFIeO = lam * zero
    //Do nothing.
}

void DirectionCosineConstraintIeJe::addToJointForceJ(FColDsptr col)
{
    //aFJeO = lam * pGpXJ
    //aFJeO = lam * zero
    //Do nothing.
}

void DirectionCosineConstraintIeJe::addToJointTorqueI(FColDsptr col)
{
    //Do nothing.
}

void DirectionCosineConstraintIeJe::addToJointTorqueJ(FColDsptr col)
{
    //Do nothing.
}

ConstraintType DirectionCosineConstraintIeJe::type()
{
    return perpendicular;
}

std::string DirectionCosineConstraintIeJe::constraintSpec()
{
    return "DirectionCosineConstraintIeJe";
}

void DirectionCosineConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    aAijIeJe = DirectionCosineIeJe::With(eFrmI, eFrmJ, axisI, axisJ);
    aAijIeJe->owner = this;
}

void DirectionCosineConstraintIeJe::initializeLocally()
{
    ConstraintIeJe::initializeLocally();
    aAijIeJe->initializeLocally();
}

void DirectionCosineConstraintIeJe::initializeGlobally()
{
    ConstraintIeJe::initializeGlobally();
    aAijIeJe->initializeGlobally();
}

void DirectionCosineConstraintIeJe::postInput()
{
    aAijIeJe->postInput();
    ConstraintIeJe::postInput();
}

void DirectionCosineConstraintIeJe::prePosIC()
{
    aAijIeJe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void DirectionCosineConstraintIeJe::postPosICIteration()
{
    aAijIeJe->postPosICIteration();
    ConstraintIeJe::postPosICIteration();
}

void DirectionCosineConstraintIeJe::preVelIC()
{
    aAijIeJe->preVelIC();
    ConstraintIeJe::preVelIC();
}

void DirectionCosineConstraintIeJe::fillVelICJacob(SpMatDsptr mat)
{
    //Do nothing.
}

void DirectionCosineConstraintIeJe::preAccIC()
{
    aAijIeJe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void DirectionCosineConstraintIeJe::fillAccICIterError(FColDsptr col)
{
    //Do nothing.
}

void DirectionCosineConstraintIeJe::preDyn()
{
    aAijIeJe->preDyn();
    ConstraintIeJe::preDyn();
}

void DirectionCosineConstraintIeJe::preDynOutput()
{
    aAijIeJe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void DirectionCosineConstraintIeJe::postDynOutput()
{
    aAijIeJe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}

void DirectionCosineConstraintIeJe::postDynPredictor()
{
    aAijIeJe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void DirectionCosineConstraintIeJe::postDynCorrectorIteration()
{
    aAijIeJe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void DirectionCosineConstraintIeJe::fillpFpy(SpMatDsptr mat)
{
    //Do nothing.
}

void DirectionCosineConstraintIeJe::fillpFpydot(SpMatDsptr mat)
{
    //Do nothing.
}

void DirectionCosineConstraintIeJe::fillPosICJacob(SpMatDsptr mat)
{
    //Do nothing.
}
