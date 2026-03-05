/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <numbers>
#include "AllowZRotationConstraintIctJqc.h"
#include "MarkerFramec.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "Symbolic.h"
#include "Constant.h"
#include "EulerAngles.h"
#include "SimulationStoppingError.h"

using namespace MbD;

AllowZRotationConstraintIctJqc::AllowZRotationConstraintIctJqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) :
    DirectionCosineConstraintIctJqc(frmi, frmj, axisi, axisj)
{
    //Do nothing.
}

std::shared_ptr<AllowZRotationConstraintIctJqc> AllowZRotationConstraintIctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<AllowZRotationConstraintIctJqc>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void AllowZRotationConstraintIctJqc::postInput()
{
    auto ectI = std::static_pointer_cast<EndFramect>(eFrmI);
    auto aAImJe = ectI->getMarkerFrame()->aAOm->transposeTimesFullMatrix(eFrmJ->aAOe);
    auto aEulerAngles = aAImJe->eulerAngles();
    auto the1z = aEulerAngles->at(1);
    auto the2x = aEulerAngles->at(2);
    if (std::abs(the2x) < (std::numbers::pi / 2.0)) {
        ectI->phiThePsiBlks->at(1) = std::make_shared<Constant>(the1z);
    }
    else {
        ectI->phiThePsiBlks->at(1) = std::make_shared<Constant>(std::numbers::pi + the1z);
    }
    ectI->postInput();
    DirectionCosineConstraintIctJqc::postInput();
}

void AllowZRotationConstraintIctJqc::postPosIC()
{
    //self becomeRedundantConstraint
    throw SimulationStoppingError("To be implemented.");
}

std::string AllowZRotationConstraintIctJqc::constraintSpec()
{
    return "AllowZRotationConstraintIJ";
}
