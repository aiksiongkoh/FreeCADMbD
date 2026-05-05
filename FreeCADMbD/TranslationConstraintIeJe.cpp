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
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIeJe> TranslationConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    std::shared_ptr<TranslationConstraintIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<TranslationConstraintIeqtJeq>(frmi, frmj, axisi);
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
            inst = std::make_shared<TranslationConstraintIeqJeq>(frmi, frmj, axisi);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<TranslationConstraintIeqJe>(frmi, frmj, axisi);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<TranslationConstraintIetJeq>(frmi, frmj, axisi);
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
            inst = std::make_shared<TranslationConstraintIeJeq>(frmi, frmj, axisi);
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

void MbD::TranslationConstraintIeJe::useUniqueDispIeJeKe()
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

void MbD::TranslationConstraintIeJe::useUniqueDispIeJeO()
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

void MbD::TranslationConstraintIeJe::calcG()
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

void MbD::TranslationConstraintIeJe::fillVelICJacob(SpMatDsptr mat)
{
    //Do nothing.
}

void MbD::TranslationConstraintIeJe::fillAccICIterError(FColDsptr col)
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

void MbD::TranslationConstraintIeJe::preDyn()
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

void MbD::TranslationConstraintIeJe::fillpFpy(SpMatDsptr mat)
{
    //Do nothing.
}

void MbD::TranslationConstraintIeJe::fillpFpydot(SpMatDsptr mat)
{
    //Do nothing.
}

void MbD::TranslationConstraintIeJe::addToJointForceI(FColDsptr col)
{
    //Do nothing.
}

void MbD::TranslationConstraintIeJe::addToJointTorqueI(FColDsptr col)
{
    //Do nothing.
}

void MbD::TranslationConstraintIeJe::addToJointForceJ(FColDsptr col)
{
    //Do nothing.
}

void MbD::TranslationConstraintIeJe::addToJointTorqueJ(FColDsptr col)
{
    //Do nothing.
}

std::string TranslationConstraintIeJe::constraintSpec()
{
    return "TranslationConstraintIeJe";
}

void MbD::TranslationConstraintIeJe::fillPosICJacob(SpMatDsptr mat)
{
    //Do nothing.
}
