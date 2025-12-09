/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynSphericalHingeJoint.h"
#include "ASMTSphericalJoint.h"
#include "ASMTAssembly.h"

using namespace MbD;

std::shared_ptr<MBDynSphericalHingeJoint> MBDynSphericalHingeJoint::With()
{
    auto inst = std::make_shared<MBDynSphericalHingeJoint>();
    inst->initialize();
    return inst;
}

void MBDynSphericalHingeJoint::parseMBDyn(std::string line)
{
    MBDynJoint::parseMBDyn(line);
}

void MBDynSphericalHingeJoint::createASMT()
{
    auto asmtJoint = ASMTSphericalJoint::With();
    asmtAssembly()->addJoint(asmtJoint);
    asmtItem = asmtJoint;
    MBDynJoint::createASMT();
}
