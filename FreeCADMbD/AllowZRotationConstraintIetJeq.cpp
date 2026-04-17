/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <numbers>
#include "AllowZRotationConstraintIetJeq.h"
#include "MarkerFramec.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "Symbolic.h"
#include "Constant.h"
#include "EulerAngles.h"
#include "SimulationStoppingError.h"

using namespace MbD;

AllowZRotationConstraintIetJeq::AllowZRotationConstraintIetJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) :
    DirectionCosineConstraintIetJeq(frmi, frmj, axisi, axisj)
{
    //Do nothing.
}

std::shared_ptr<AllowZRotationConstraintIetJeq> AllowZRotationConstraintIetJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<AllowZRotationConstraintIetJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void AllowZRotationConstraintIetJeq::postInput()
{
    auto ectI = std::static_pointer_cast<EndFramect>(frmIe);
    auto aAImJe = ectI->getMarkerFrame()->aAOm->transposeTimesFullMatrix(frmJe->aAOe);
    auto aEulerAngles = aAImJe->eulerAngles();
    auto the2y = aEulerAngles->at(1);
    auto the3z = aEulerAngles->at(2);
    if (std::abs(the2y) < (std::numbers::pi / 2.0)) {
        ectI->the1x2y3zBlks->at(2) = std::make_shared<Constant>(the3z);
    }
    else {
        ectI->the1x2y3zBlks->at(2) = std::make_shared<Constant>(std::numbers::pi + the3z);
    }
    ectI->postInput();
    DirectionCosineConstraintIetJeq::postInput();
}

void AllowZRotationConstraintIetJeq::postPosIC()
{
    //self becomeRedundantConstraint
    throw SimulationStoppingError("To be implemented.");
}

std::string AllowZRotationConstraintIetJeq::constraintSpec()
{
    return "AllowZRotationConstraintIJ";
}
