/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RackPinJoint.h"
#include "System.h"
#include "RackPinConstraintIJ.h"

using namespace MbD;

std::shared_ptr<RackPinJoint> RackPinJoint::With()
{
    auto inst = std::make_shared<RackPinJoint>();
    inst->initialize();
    return inst;
}

std::shared_ptr<RackPinJoint> RackPinJoint::With(const std::string& str)
{
    auto inst = std::make_shared<RackPinJoint>(str);
    inst->initialize();
    return inst;
}

void RackPinJoint::initializeGlobally()
{
    if (constraints->empty())
    {
        auto rackPinIJ = RackPinConstraintIJ::With(eFrmI, eFrmJ);
        rackPinIJ->setConstant(std::numeric_limits<double>::min());
        rackPinIJ->pitchRadius = pitchRadius;
        addConstraint(rackPinIJ);
        root()->hasChanged = true;
    }
    else {
        JointIJ::initializeGlobally();
    }
}

void RackPinJoint::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    //"OODS J is on pinion. z axis is axis of pinion."
    //"OODS I is on rack. x axis is axis of rack. z axis is parallel to axis of pinion."
    //"Subsequent prescribed motions may make frmi, frmj become prescribed end frames."
    //"Use newCopyEndFrameqc to prevent efrms from becoming EndFrameqct."

    eFrmI = frmi->newCopyEndFrameqc();
    eFrmJ = frmj->newCopyEndFrameqc();
}
