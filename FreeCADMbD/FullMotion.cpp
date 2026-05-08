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
#include "EndFramet.h"
#include "EndFrameqt.h"
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
    std::static_pointer_cast<EndFrameq>(eFrmI)->initEndFrameqt2();
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
    auto eFrmIct = std::dynamic_pointer_cast<EndFramet>(eFrmI);
    auto eFrmIqt = std::dynamic_pointer_cast<EndFrameqt>(eFrmI);
    if (eFrmIct && !eFrmIqt) {
        eFrmIct->rmemBlks = frIJI;
        eFrmIct->the1x2y3zBlks = fangIJJ;
    }
    else if (!eFrmIct && eFrmIqt) {
        eFrmIqt->rmemBlks = frIJI;
        eFrmIqt->the1x2y3zBlks = fangIJJ;
    }
}
