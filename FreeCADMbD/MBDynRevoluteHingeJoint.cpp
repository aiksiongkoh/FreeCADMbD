/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynRevoluteHingeJoint.h"
#include "ASMTRevoluteJoint.h"
#include "ASMTAssembly.h"

using namespace MbD;

std::shared_ptr<MBDynRevoluteHingeJoint> MBDynRevoluteHingeJoint::With()
{
    auto inst = std::make_shared<MBDynRevoluteHingeJoint>();
    inst->initialize();
    return inst;
}

void MBDynRevoluteHingeJoint::parseMBDyn(std::string line)
{
    MBDynJoint::parseMBDyn(line);
}

void MBDynRevoluteHingeJoint::createASMT()
{
    auto asmtJoint = ASMTRevoluteJoint::With();
    asmtAssembly()->addJoint(asmtJoint);
    asmtItem = asmtJoint;
    MBDynJoint::createASMT();
}
