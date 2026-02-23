/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
//#include "DirectionCosineConstraintIJ.h"
#include "DirectionCosineConstraintIqctJqc.h"
#include "DirectionCosineConstraintIctJqc.h"
#include "DirectionCosineIecJec.h"
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIJ> DirectionCosineConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    std::shared_ptr<DirectionCosineConstraintIJ> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIqctJqc>(frmi, frmj, axisi, axisj);
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
            inst = std::make_shared<DirectionCosineConstraintIqcJqc>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIqcJc>(frmi, frmj, axisi, axisj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIctJqc>(frmi, frmj, axisi, axisj);
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
            inst = std::make_shared<DirectionCosineConstraintIcJqc>(frmi, frmj, axisi, axisj);
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

void DirectionCosineConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
    initaAijIeJe();
}

void DirectionCosineConstraintIJ::initializeLocally()
{
    aAijIeJe->initializeLocally();
}

void DirectionCosineConstraintIJ::initializeGlobally()
{
    aAijIeJe->initializeGlobally();
}

void DirectionCosineConstraintIJ::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIecJec::With(eFrmI, eFrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIJ::postInput()
{
    aAijIeJe->postInput();
    ConstraintIJ::postInput();
}

void DirectionCosineConstraintIJ::simUpdateAll()
{
    //aG = aAijIeJe - aConstant;
    aG = aAijIeJe->aAijIeJe - aConstant;
}

void MbD::DirectionCosineConstraintIJ::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //aFIeO = lam * zero
    //Do nothing.
}

void DirectionCosineConstraintIJ::prePosIC()
{
    aAijIeJe->prePosIC();
    ConstraintIJ::prePosIC();
}

void DirectionCosineConstraintIJ::postPosICIteration()
{
    aAijIeJe->postPosICIteration();
    ConstraintIJ::postPosICIteration();
}

ConstraintType DirectionCosineConstraintIJ::type()
{
    return perpendicular;
}

void DirectionCosineConstraintIJ::postDynPredictor()
{
    aAijIeJe->postDynPredictor();
    ConstraintIJ::postDynPredictor();
}

void DirectionCosineConstraintIJ::postDynCorrectorIteration()
{
    aAijIeJe->postDynCorrectorIteration();
    ConstraintIJ::postDynCorrectorIteration();
}

void DirectionCosineConstraintIJ::preDynOutput()
{
    aAijIeJe->preDynOutput();
    ConstraintIJ::preDynOutput();
}

void DirectionCosineConstraintIJ::postDynOutput()
{
    aAijIeJe->postDynOutput();
    ConstraintIJ::postDynOutput();
}

void DirectionCosineConstraintIJ::preVelIC()
{
    aAijIeJe->preVelIC();
    ConstraintIJ::preVelIC();
}

void DirectionCosineConstraintIJ::preAccIC()
{
    aAijIeJe->preAccIC();
    ConstraintIJ::preAccIC();
}
