#include "MBDynRodJoint.h"
#include "ASMTAssembly.h"
#include "ASMTForceTorqueInLine.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynRodJoint> MBDynRodJoint::With()
{
    auto inst = std::make_shared<MBDynRodJoint>();
    inst->initialize();
    return inst;
}

void MBDynRodJoint::parseMBDyn(std::string line)
{
    jointString = line;
    arguments = collectArgumentsFor("joint", line);
    readLabel(arguments);
    readJointType(arguments);
    readMarkerI(arguments);
    readMarkerJ(arguments);
    readRodLength(arguments);
    readConstitutiveLaw(arguments);
}

void MBDynRodJoint::readMarkerI(std::vector<std::string>& args)
{
    mkr1 = MBDynMarker::With();
    mkr1->owner = this;
    mkr1->nodeStr = readStringNoSpacesOffTop(args);
    mkr1->rPmP = readPosition(args);
    mkr1->aAPm = FullMatrix<double>::identitysptr(3);
}

void MBDynRodJoint::readMarkerJ(std::vector<std::string>& args)
{
    mkr2 = MBDynMarker::With();
    mkr2->owner = this;
    mkr2->nodeStr = readStringNoSpacesOffTop(args);
    mkr2->rPmP = readPosition(args);
    mkr2->aAPm = FullMatrix<double>::identitysptr(3);
}

void MBDynRodJoint::readRodLength(std::vector<std::string>& args)
{
    if (lineHasTokens(args[0], "from", "nodes")) {
        popOffTop(args);
        auto rIJO = mkr2->rOmO()->minusFullColumn(mkr1->rOmO());
        rodLength = rIJO->length();
    }
    else {
        rodLength = readDoubleOffTop(args);
    }
}

void MBDynRodJoint::readConstitutiveLaw(std::vector<std::string>& args)
{
    if (lineHasTokens(args[0], "linear", "elastic")) {
        popOffTop(args);
        stiffness = readDoubleOffTop(args);
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

void MBDynRodJoint::createASMT()
{
    auto asmtForTor = ASMTForceTorqueInLine::With();
    std::stringstream ss;
    ss << std::setprecision(std::numeric_limits<double>::max_digits10);
    ss << stiffness << '*' << "(rIJ(self) - " << rodLength << ')';
    asmtForTor->tensionFunc = ss.str();
    asmtForTor->twistFunc = "0";
    asmtAssembly()->addForceTorque(asmtForTor);
    asmtItem = asmtForTor;
    MBDynJoint::createASMT();
}
