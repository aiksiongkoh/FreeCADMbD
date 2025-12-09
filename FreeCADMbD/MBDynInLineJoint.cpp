/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynInLineJoint.h"
#include "ASMTPointInLineJoint.h"
#include "ASMTAssembly.h"

using namespace MbD;

std::shared_ptr<MBDynInLineJoint> MBDynInLineJoint::With()
{
    auto inst = std::make_shared<MBDynInLineJoint>();
    inst->initialize();
    return inst;
}

void MBDynInLineJoint::parseMBDyn(std::string line)
{
    MBDynJoint::parseMBDyn(line);
}

void MBDynInLineJoint::createASMT()
{
    auto asmtJoint = ASMTPointInLineJoint::With();
    asmtAssembly()->addJoint(asmtJoint);
    asmtItem = asmtJoint;
    MBDynJoint::createASMT();
}
