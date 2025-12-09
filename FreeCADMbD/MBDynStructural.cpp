#include "MBDynStructural.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "EulerAngles.h"
#include "Constant.h"
#include "MBDynReference.h"
#include "ASMTPart.h"
#include "ASMTAssembly.h"
#include "MBDynStructuralDummy.h"
#include "MBDynStructuralDynamic.h"
#include "MBDynStructuralStatic.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void MBDynStructural::initialize()
{
    MBDynNode::initialize();
    rOfO = std::make_shared<FullColumn<double>>(3);
    aAOf = FullMatrix<double>::identitysptr(3);
    vOfO = std::make_shared<FullColumn<double>>(3);
    omeOfO = std::make_shared<FullColumn<double>>(3);
}

std::shared_ptr<MBDynStructural> MBDynStructural::newStructural(std::string statement)
{
    if (lineHasTokens(statement, "dummy")) {
        return MBDynStructuralDummy::With();
    }
    if (lineHasTokens(statement, "dynamic")) {
        return MBDynStructuralDynamic::With();
    }
    if (lineHasTokens(statement, "static")) {
        return MBDynStructuralStatic::With();
    }
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<MBDynStructural>();
}

void MBDynStructural::parseMBDyn(std::string line)
{
    throw SimulationStoppingError("To be implemented.");
}

void MBDynStructural::readPosition(std::vector<std::string>& args)
{
    rOfO = std::make_shared<FullColumn<double>>(3);
    if (args.empty()) return;
    if (args[0].find("reference") != std::string::npos) {
        args.erase(args.begin());
        baseRefName = readStringNoSpacesOffTop(args);
        auto& ref = mbdynReferences()->at(baseRefName);
        auto rFfF = readBasicPosition(args);
        auto& rOFO = ref->rFfF;
        auto& aAOF = ref->aAFf;
        rOfO = rOFO->plusFullColumn(aAOF->timesFullColumn(rFfF));
    }
    else if (args[0].find("null") != std::string::npos) {
        args.erase(args.begin());
    }
    else {
        rOfO = readBasicPosition(args);
    }
}

void MBDynStructural::readOrientation(std::vector<std::string>& args)
{
    aAOf = FullMatrix<double>::identitysptr(3);
    if (args.empty()) return;
    if (args[0].find("reference") != std::string::npos) {
        args.erase(args.begin());
        assert(baseRefName == readStringNoSpacesOffTop(args));
        auto& ref = mbdynReferences()->at(baseRefName);
        auto aAFf = readBasicOrientation(args);
        auto& aAOF = ref->aAFf;
        aAOf = aAOF->timesFullMatrix(aAFf);
    }
    else if (args[0].find("position") != std::string::npos) {
        if (args[0].find("orientation") != std::string::npos) {
            args.erase(args.begin());
            aAOf = readBasicOrientation(args);
        }
    }
    else if (args[0].find("orientation") != std::string::npos) {
        args.erase(args.begin());
        if (args[0].find("reference") != std::string::npos) {
            args.erase(args.begin());
            assert(baseRefName == readStringNoSpacesOffTop(args));
            aAOf = readBasicOrientation(args);
        }
    }
    else {
        aAOf = readBasicOrientation(args);
    }
}

void MBDynStructural::readVelocity(std::vector<std::string>& args)
{
    vOfO = std::make_shared<FullColumn<double>>(3);
    if (args[0].find("null") != std::string::npos) {
        args.erase(args.begin());
        return;
    }
    else if (args[0].find("reference") != std::string::npos) {
        args.erase(args.begin());
        assert(baseRefName == readStringNoSpacesOffTop(args));
        assert(args[0].find("null") != std::string::npos);    //ToDo: for not null.
        vOfO = readVector3(args);
    }
    else {
        vOfO = readVector3(args);
    }
}

void MBDynStructural::readOmega(std::vector<std::string>& args)
{
    omeOfO = std::make_shared<FullColumn<double>>(3);
    if (args[0].find("null") != std::string::npos) {
        args.erase(args.begin());
        return;
    }
    else if (args[0].find("reference") != std::string::npos) {
        args.erase(args.begin());
        assert(baseRefName == readStringNoSpacesOffTop(args));
        assert(args[0].find("null") != std::string::npos);    //ToDo: for not null.
        omeOfO = readVector3(args);
    }
    else {
        omeOfO = readVector3(args);
    }
}

void MBDynStructural::createASMT()
{
    auto asmtPart = ASMTPart::With();
    asmtPart->principalMassMarker->zeroMass();
    asmtItem = asmtPart;
    asmtPart->setName(label);
    asmtPart->setPosition3D(rOfO);
    asmtPart->setRotationMatrix(aAOf);
    asmtPart->setVelocity3D(vOfO);
    asmtPart->setOmega3D(omeOfO);
    asmtAssembly()->addPart(asmtPart);
}
