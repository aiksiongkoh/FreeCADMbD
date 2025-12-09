/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <numbers>
#include "AllowZRotationConstraintIqctJqc.h"
#include "MarkerFrame.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "Symbolic.h"
#include "Constant.h"
#include "EulerAngleszxz.h"
#include "SimulationStoppingError.h"

using namespace MbD;

AllowZRotationConstraintIqctJqc::AllowZRotationConstraintIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) :
    DirectionCosineConstraintIqctJqc(frmi, frmj, axisi, axisj)
{
    //Do nothing.
}

std::shared_ptr<AllowZRotationConstraintIqctJqc> AllowZRotationConstraintIqctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<AllowZRotationConstraintIqctJqc>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void AllowZRotationConstraintIqctJqc::postInput()
{
    auto eqctI = std::static_pointer_cast<EndFrameqct>(eFrmI);
    auto aAImJe = eqctI->getMarkerFrame()->aAOm->transposeTimesFullMatrix(eFrmJ->aAOe);
    auto aEulerAngleszxz = aAImJe->eulerAngleszxz();
    auto the1z = aEulerAngleszxz->at(1);
    auto the2x = aEulerAngleszxz->at(2);
    if (std::abs(the2x) < (std::numbers::pi / 2.0)) {
        eqctI->phiThePsiBlks->at(1) = std::make_shared<Constant>(the1z);
    }
    else {
        eqctI->phiThePsiBlks->at(1) = std::make_shared<Constant>(std::numbers::pi + the1z);
    }
    eqctI->postInput();
    DirectionCosineConstraintIqctJqc::postInput();
}

void AllowZRotationConstraintIqctJqc::postPosIC()
{
    //self becomeRedundantConstraint
    throw SimulationStoppingError("To be implemented.");
}

std::string AllowZRotationConstraintIqctJqc::constraintSpec()
{
    return "AllowZRotationConstraintIJ";
}
