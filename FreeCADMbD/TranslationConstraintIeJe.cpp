/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <algorithm>

#include "TranslationConstraintIeJe.h"
#include "DispCompiIeJeIe.h"
#include "TranslationConstraintIeqtJeq.h"
#include "TranslationConstraintIetJeq.h"
#include "System.h"
#include "EndFrameqt.h"
#include "EndFrameq.h"
#include "EndFramet.h"
#include "EndFrame.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIeJe> TranslationConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    std::shared_ptr<TranslationConstraintIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<TranslationConstraintIeqtJeq>(frmi, frmj, axisi);
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
            inst = std::make_shared<TranslationConstraintIeqJeq>(frmi, frmj, axisi);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = std::make_shared<TranslationConstraintIeqJe>(frmi, frmj, axisi);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<TranslationConstraintIetJeq>(frmi, frmj, axisi);
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
            inst = std::make_shared<TranslationConstraintIeJeq>(frmi, frmj, axisi);
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

void TranslationConstraintIeJe::simUpdateAll()
{
    ConstraintIeJe::simUpdateAll();
}

void TranslationConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    dispIeJeIe = DispIeJeKe::With(eFrmI, eFrmJ, eFrmI);
    dispIeJeIe->owner = this;
    initriIeJeIe();
}

void TranslationConstraintIeJe::useUniqueDispIeJeKe()
{
    if (!dispIeJeIe) return;
    auto dispIeJeKes = root()->dispIeJeKes;
    auto it = std::find_if(dispIeJeKes->begin(), dispIeJeKes->end(), [&](auto disp) { return disp->hasSameEndFrms(dispIeJeIe); });
    if (it == dispIeJeKes->end()) {
        dispIeJeKes->push_back(dispIeJeIe);
    }
    else {
        dispIeJeIe = *it;
    }
    riIeJeIe->useUniqueDispIeJeKe();
}

void TranslationConstraintIeJe::initializeLocally()
{
    riIeJeIe->initializeLocally();
}

void TranslationConstraintIeJe::initializeGlobally()
{
    riIeJeIe->initializeGlobally();
}

void TranslationConstraintIeJe::useUniqueDispIeJeO()
{
    dispIeJeIe->useUniqueDispIeJeO();
    riIeJeIe->useUniqueDispIeJeO();
}

void TranslationConstraintIeJe::initriIeJeIe()
{
    riIeJeIe = DispCompiIeJeIe::With(eFrmI, eFrmJ, axisI);
    riIeJeIe->owner = this;
}

void TranslationConstraintIeJe::postInput()
{
    riIeJeIe->postInput();
    ConstraintIeJe::postInput();
}

void TranslationConstraintIeJe::calcG()
{
    // aG = riIeJeIe->value() - aConstant;
    auto rIeJeIe = dispIeJeIe->rIeJeKe;
    aG = rIeJeIe->at(axisI) - aConstant;
}

void TranslationConstraintIeJe::prePosIC()
{
    riIeJeIe->prePosIC();
    ConstraintIeJe::prePosIC();
}

void TranslationConstraintIeJe::fillVelICJacob(SpMatDsptr mat)
{
    //Do nothing.
}

void TranslationConstraintIeJe::fillAccICIterError(FColDsptr col)
{
    //Do nothing.
}

ConstraintType TranslationConstraintIeJe::type()
{
    return displacement;
}

void TranslationConstraintIeJe::postDynPredictor()
{
    riIeJeIe->postDynPredictor();
    ConstraintIeJe::postDynPredictor();
}

void TranslationConstraintIeJe::postDynCorrectorIteration()
{
    riIeJeIe->postDynCorrectorIteration();
    ConstraintIeJe::postDynCorrectorIteration();
}

void TranslationConstraintIeJe::preDynOutput()
{
    riIeJeIe->preDynOutput();
    ConstraintIeJe::preDynOutput();
}

void TranslationConstraintIeJe::preDyn()
{
    //Do nothing.
}

void TranslationConstraintIeJe::postDynOutput()
{
    riIeJeIe->postDynOutput();
    ConstraintIeJe::postDynOutput();
}

void TranslationConstraintIeJe::postPosICIteration()
{
    riIeJeIe->postPosICIteration();
    Item::postPosICIteration();
}

void TranslationConstraintIeJe::preVelIC()
{
    riIeJeIe->preVelIC();
    Item::preVelIC();
}

void TranslationConstraintIeJe::preAccIC()
{
    riIeJeIe->preAccIC();
    ConstraintIeJe::preAccIC();
}

void TranslationConstraintIeJe::fillpFpy(SpMatDsptr mat)
{
    //Do nothing.
}

void TranslationConstraintIeJe::fillpFpydot(SpMatDsptr mat)
{
    //Do nothing.
}

void TranslationConstraintIeJe::addToJointForceI(FColDsptr col)
{
    //Do nothing.
}

void TranslationConstraintIeJe::addToJointTorqueI(FColDsptr col)
{
    //Do nothing.
}

void TranslationConstraintIeJe::addToJointForceJ(FColDsptr col)
{
    //Do nothing.
}

void TranslationConstraintIeJe::addToJointTorqueJ(FColDsptr col)
{
    //Do nothing.
}

std::string TranslationConstraintIeJe::constraintSpec()
{
    return "TranslationConstraintIeJe";
}

void TranslationConstraintIeJe::fillPosICJacob(SpMatDsptr mat)
{
    //Do nothing.
}
