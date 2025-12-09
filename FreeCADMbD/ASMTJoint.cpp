/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>    

#include "ASMTJoint.h"
#include "JointIJ.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<ASMTJoint> ASMTJoint::With()
{
    auto inst = std::make_shared<ASMTJoint>();
    inst->initialize();
    return inst;
}

void ASMTJoint::readJointSeries(std::vector<std::string>& lines)
{
    std::string str = lines[0];
    std::string substr = "JointSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    assert(fullName("") == seriesName);
    lines.erase(lines.begin());
    readFXonIs(lines);
    readFYonIs(lines);
    readFZonIs(lines);
    readTXonIs(lines);
    readTYonIs(lines);
    readTZonIs(lines);
}

void ASMTJoint::storeOnLevel(std::ofstream& os, size_t level)
{
    auto jointType = classname();
    jointType = jointType.substr(4, jointType.size() - 4);    //Remove ASMT in name
    storeOnLevelString(os, level, jointType);
    storeOnLevelString(os, level + 1, "Name");
    storeOnLevelString(os, level + 2, name);
    ASMTItemIJ::storeOnLevel(os, level);
}

void ASMTJoint::storeOnTimeSeries(std::ofstream& os)
{
    std::string label = typeid(*this).name();
    label = label.substr(15, label.size() - 15);
    os << label << "Series\t" << fullName("") << std::endl;
    ASMTItemIJ::storeOnTimeSeries(os);
}

bool ASMTJoint::isJoint()
{
    return true;
}

void ASMTJoint::createMbD()
{
    ASMTConstraintSet::createMbD();
    auto mbdJt = std::static_pointer_cast<JointIJ>(mbdObject);
    mbdSys()->addJoint(mbdJt);
}
