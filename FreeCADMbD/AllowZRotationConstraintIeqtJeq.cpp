/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <numbers>
#include "AllowZRotationConstraintIeqtJeq.h"
#include "MarkerFrame.h"
#include "EndFrameq.h"
#include "EndFrameqt.h"
#include "Symbolic.h"
#include "Constant.h"
#include "EulerAngles.h"
#include "SimulationStoppingError.h"

using namespace MbD;

AllowZRotationConstraintIeqtJeq::AllowZRotationConstraintIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) :
    DirectionCosineConstraintIeqtJeq(frmi, frmj, axisi, axisj)
{
    //Do nothing.
}

std::shared_ptr<AllowZRotationConstraintIeqtJeq> AllowZRotationConstraintIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<AllowZRotationConstraintIeqtJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void AllowZRotationConstraintIeqtJeq::postInput()
{
    auto eqtI = std::static_pointer_cast<EndFrameqt>(eFrmI);
    auto aAImJe = eqtI->getMarkerFrame()->aAOm->transposeTimesFullMatrix(eFrmJ->aAOe);
    auto aEulerAngles = aAImJe->eulerAngles();
    auto the2y = aEulerAngles->at(1);
    auto the3z = aEulerAngles->at(2);
    if (std::abs(the2y) < (std::numbers::pi / 2.0)) {
        eqtI->the1x2y3zBlks->at(2) = std::make_shared<Constant>(the3z);
    }
    else {
        eqtI->the1x2y3zBlks->at(2) = std::make_shared<Constant>(std::numbers::pi + the3z);
    }
    eqtI->postInput();
    DirectionCosineConstraintIeqtJeq::postInput();
}

void AllowZRotationConstraintIeqtJeq::postPosIC()
{
    //self becomeRedundantConstraint
    throw SimulationStoppingError("To be implemented.");
}

std::string AllowZRotationConstraintIeqtJeq::constraintSpec()
{
    return "AllowZRotationConstraintIJ";
}
