/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynRevolutePinJoint.h"
#include "ASMTJoint.h"
#include "ASMTAssembly.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynRevolutePinJoint> MBDynRevolutePinJoint::With()
{
    auto inst = std::make_shared<MBDynRevolutePinJoint>();
    inst->initialize();
    return inst;
}

void MBDynRevolutePinJoint::parseMBDyn(std::string line)
{
    MBDynJoint::parseMBDyn(line);
}

void MBDynRevolutePinJoint::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
    auto asmtJoint = ASMTJoint::With();
    asmtAssembly()->addJoint(asmtJoint);
    asmtItem = asmtJoint;
    MBDynJoint::createASMT();
}
