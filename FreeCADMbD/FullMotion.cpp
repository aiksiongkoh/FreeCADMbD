/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "FullMotion.h"
#include "System.h"
#include "TranslationConstraintIeJe.h"
#include "DirectionCosineConstraintIeJe.h"
#include "EndFramect.h"
#include "EndFrameqct.h"
#include "SimulationStoppingError.h"

using namespace MbD;

FullMotion::FullMotion(const std::string&)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<FullMotion> FullMotion::With()
{
    auto inst = std::make_shared<FullMotion>();
    inst->initialize();
    return inst;
}

std::shared_ptr<FullMotion> FullMotion::With(const std::string& str)
{
    auto inst = std::make_shared<FullMotion>(str);
    inst->initialize();
    return inst;
}

void FullMotion::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    ConstraintSet::connectsItoJ(frmi, frmj);
    std::static_pointer_cast<EndFrameqc>(eFrmI)->initEndFrameqct2();
}

void FullMotion::initializeGlobally()
{
    if (constraints->empty()) {
        initMotions();
        addConstraint(TranslationConstraintIeJe::With(eFrmI, eFrmJ, 0));
        addConstraint(TranslationConstraintIeJe::With(eFrmI, eFrmJ, 1));
        addConstraint(TranslationConstraintIeJe::With(eFrmI, eFrmJ, 2));
        addConstraint(DirectionCosineConstraintIeJe::With(eFrmI, eFrmJ, 1, 0));
        addConstraint(DirectionCosineConstraintIeJe::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIeJe::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        PrescribedMotion::initializeGlobally();
    }
}

void FullMotion::initMotions()
{
    auto eFrmIct = std::dynamic_pointer_cast<EndFramect>(eFrmI);
    auto eFrmIqct = std::dynamic_pointer_cast<EndFrameqct>(eFrmI);
    if (eFrmIct && !eFrmIqct) {
        eFrmIct->rmemBlks = frIJI;
        eFrmIct->phiThePsiBlks = fangIJJ;
    }
    else if (!eFrmIct && eFrmIqct) {
        eFrmIqct->rmemBlks = frIJI;
        eFrmIqct->phiThePsiBlks = fangIJJ;
    }
}
