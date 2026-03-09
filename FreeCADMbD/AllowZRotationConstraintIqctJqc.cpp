/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <numbers>
#include "AllowZRotationConstraintIqctJqc.h"
#include "MarkerFramec.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "Symbolic.h"
#include "Constant.h"
#include "EulerAngles.h"
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
    auto aEulerAngles = aAImJe->eulerAngles();
    auto the2y = aEulerAngles->at(1);
    auto the3z = aEulerAngles->at(2);
    if (std::abs(the2y) < (std::numbers::pi / 2.0)) {
        eqctI->the1x2y3zBlks->at(2) = std::make_shared<Constant>(the3z);
    }
    else {
        eqctI->the1x2y3zBlks->at(2) = std::make_shared<Constant>(std::numbers::pi + the3z);
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
