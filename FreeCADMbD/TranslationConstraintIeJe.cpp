/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIeJe.h"
#include "TranslationConstraintIeqtJeq.h"
#include "TranslationConstraintIetJeq.h"
#include "DispCompIeqctJeqcKeqct.h"
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"
#include "System.h"

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

void TranslationConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    initriIeJeIe();
}

void TranslationConstraintIeJe::initializeLocally()
{
    riIeJeIe->initializeLocally();
}

void TranslationConstraintIeJe::initializeGlobally()
{
    riIeJeIe->initializeGlobally();
}

void TranslationConstraintIeJe::initriIeJeIe()
{
    riIeJeIe = DispCompIecJecKec::With(frmIe, frmJe, frmIe, axisI);
}

void MbD::TranslationConstraintIeJe::useUniqueDispIeJeO()
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

void MbD::TranslationConstraintIeJe::useUniqueDispIeJeKe()
{
}

void TranslationConstraintIeJe::postInput()
{
    riIeJeIe->postInput();
    Constraint::postInput();
}

void MbD::TranslationConstraintIeJe::calcG()
{
    aG = riIeJeIe->value() - aConstant;
}

void MbD::TranslationConstraintIeJe::calcpGpXI()
{
    //pGpXI = [0];
    assert(!pGpXI);
}

void MbD::TranslationConstraintIeJe::calcpGpEI()
{
    //pGpEI = [0];
    assert(!pGpEI);
}

void MbD::TranslationConstraintIeJe::calcpGpXJ()
{
    //pGpXJ = [0];
    assert(!pGpXJ);
}

void MbD::TranslationConstraintIeJe::calcpGpEJ()
{
    //pGpEJ = [0];
    assert(!pGpEJ);
}

void MbD::TranslationConstraintIeJe::calcppGpXIpXI()
{
    //ppGpXIpXI = [0];
    assert(!ppGpXIpXI);
}

void MbD::TranslationConstraintIeJe::calcppGpXIpEI()
{
    //ppGpXIpEI = [0];
    assert(!ppGpXIpEI);
}

void MbD::TranslationConstraintIeJe::calcppGpXIpXJ()
{
    //ppGpXIpXJ = [0];
    assert(!ppGpXIpXJ);
}

void MbD::TranslationConstraintIeJe::calcppGpXIpEJ()
{
    //ppGpXIpEJ = [0];
    assert(!ppGpXIpEJ);
}

void MbD::TranslationConstraintIeJe::calcppGpEIpEI()
{
    //ppGpEIpEI = [0];
    assert(!ppGpEIpEI);
}

void MbD::TranslationConstraintIeJe::calcppGpEIpXJ()
{
    //ppGpEIpXJ = [0];
    assert(!ppGpEIpXJ);
}

void MbD::TranslationConstraintIeJe::calcppGpEIpEJ()
{
    //ppGpEIpEJ = [0];
    assert(!ppGpEIpEJ);
}

void MbD::TranslationConstraintIeJe::calcppGpXJpXJ()
{
    //ppGpXJpXJ = [0];
    assert(!ppGpXJpXJ);
}

void MbD::TranslationConstraintIeJe::calcppGpXJpEJ()
{
    //ppGpXJpEJ = [0];
    assert(!ppGpXJpEJ);
}

void MbD::TranslationConstraintIeJe::calcppGpEJpEJ()
{
    //ppGpEJpEJ = [0];
    assert(!ppGpEJpEJ);
}

void TranslationConstraintIeJe::prePosIC()
{
    riIeJeIe->prePosIC();
    Constraint::prePosIC();
}

ConstraintType TranslationConstraintIeJe::type()
{
    return displacement;
}

void TranslationConstraintIeJe::postDynPredictor()
{
    riIeJeIe->postDynPredictor();
    Constraint::postDynPredictor();
}

void TranslationConstraintIeJe::postDynCorrectorIteration()
{
    riIeJeIe->postDynCorrectorIteration();
    Constraint::postDynCorrectorIteration();
}

void TranslationConstraintIeJe::preDynOutput()
{
    riIeJeIe->preDynOutput();
    Constraint::preDynOutput();
}

void TranslationConstraintIeJe::postDynOutput()
{
    riIeJeIe->postDynOutput();
    Constraint::postDynOutput();
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
    Constraint::preAccIC();
}

std::string TranslationConstraintIeJe::constraintSpec()
{
    return "TranslationConstraintIeJe";
}
