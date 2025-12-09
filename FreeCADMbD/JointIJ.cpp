/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>
#include <memory>
#include <typeinfo>

#include "JointIJ.h"
#include "Constraint.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "RedundantConstraint.h"
#include "MarkerFrame.h"
#include "ForceTorqueData.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<JointIJ> JointIJ::With()
{
    auto inst = std::make_shared<JointIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<JointIJ> JointIJ::With(const std::string& str)
{
    auto inst = std::make_shared<JointIJ>(str);
    inst->initialize();
    return inst;
}
