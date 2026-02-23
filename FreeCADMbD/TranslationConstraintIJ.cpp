/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIqctJqc.h"
#include "TranslationConstraintIctJqc.h"
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIJ> TranslationConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
    std::shared_ptr<TranslationConstraintIJ> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<TranslationConstraintIqctJqc>(frmi, frmj, axisi);
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
            inst = std::make_shared<TranslationConstraintIqcJqc>(frmi, frmj, axisi);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<TranslationConstraintIqcJc>(frmi, frmj, axisi);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<TranslationConstraintIctJqc>(frmi, frmj, axisi);
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
            inst = std::make_shared<TranslationConstraintIcJqc>(frmi, frmj, axisi);
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

void TranslationConstraintIJ::initialize()
{
    ConstraintIJ::initialize();
    initriIeJeIe();
}

void TranslationConstraintIJ::initializeLocally()
{
    riIeJeIe->initializeLocally();
}

void TranslationConstraintIJ::initializeGlobally()
{
    riIeJeIe->initializeGlobally();
}

void TranslationConstraintIJ::initriIeJeIe()
{
    riIeJeIe = DispCompIecJecKec::With(eFrmI, eFrmJ, eFrmI, axisI);
}

void TranslationConstraintIJ::postInput()
{
    riIeJeIe->postInput();
    Constraint::postInput();
}

void TranslationConstraintIJ::simUpdateAll()
{
    aG = riIeJeIe->value() - aConstant;
}

void TranslationConstraintIJ::prePosIC()
{
    riIeJeIe->prePosIC();
    Constraint::prePosIC();
}

ConstraintType TranslationConstraintIJ::type()
{
    return displacement;
}

void TranslationConstraintIJ::postDynPredictor()
{
    riIeJeIe->postDynPredictor();
    Constraint::postDynPredictor();
}

void TranslationConstraintIJ::postDynCorrectorIteration()
{
    riIeJeIe->postDynCorrectorIteration();
    Constraint::postDynCorrectorIteration();
}

void TranslationConstraintIJ::preDynOutput()
{
    riIeJeIe->preDynOutput();
    Constraint::preDynOutput();
}

void TranslationConstraintIJ::postDynOutput()
{
    riIeJeIe->postDynOutput();
    Constraint::postDynOutput();
}

void TranslationConstraintIJ::postPosICIteration()
{
    riIeJeIe->postPosICIteration();
    Item::postPosICIteration();
}

void TranslationConstraintIJ::preVelIC()
{
    riIeJeIe->preVelIC();
    Item::preVelIC();
}

void TranslationConstraintIJ::preAccIC()
{
    riIeJeIe->preAccIC();
    Constraint::preAccIC();
}
