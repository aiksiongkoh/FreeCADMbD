/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "FullMotion.h"
#include "System.h"
#include "TranslationConstraintIJ.h"
#include "DirectionCosineConstraintIJ.h"
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
        addConstraint(TranslationConstraintIJ::With(eFrmI, eFrmJ, 0));
        addConstraint(TranslationConstraintIJ::With(eFrmI, eFrmJ, 1));
        addConstraint(TranslationConstraintIJ::With(eFrmI, eFrmJ, 2));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 1, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 0));
        addConstraint(DirectionCosineConstraintIJ::With(eFrmI, eFrmJ, 2, 1));
        root()->hasChanged = true;
    }
    else {
        PrescribedMotion::initializeGlobally();
    }
}

void FullMotion::initMotions()
{
    auto eFrmIt = std::static_pointer_cast<EndFrameqct>(eFrmI);
    eFrmIt->rmemBlks = frIJI;
    eFrmIt->phiThePsiBlks = fangIJJ;
}
