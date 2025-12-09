#include "MBDynReference.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "EulerAngles.h"

using namespace MbD;

std::shared_ptr<MBDynReference> MBDynReference::With()
{
    auto inst = std::make_shared<MBDynReference>();
    inst->initialize();
    return inst;
}

void MBDynReference::initialize()
{
    //Do nothing.
}

void MBDynReference::parseMBDyn(std::string line)
{
    refString = line;
    arguments = collectArgumentsFor("reference", line);
    readLabel(arguments);
    readPosition(arguments);
    readOrientation(arguments);
    readVelocity(arguments);
    readOmega(arguments);
}

void MBDynReference::readPosition(std::vector<std::string>& args)
{
    rFfF = std::make_shared<FullColumn<double>>(3);
    if (args.empty()) return;
    if (args[0].find("position") != std::string::npos) {
        args.erase(args.begin());
        if (args[0].find("reference") != std::string::npos) {
            args.erase(args.begin());
            baseRefName = readStringNoSpacesOffTop(args);
            rFfF = readBasicPosition(args);
        }
    }
    else if (args[0].find("reference") != std::string::npos) {
        args.erase(args.begin());
        baseRefName = readStringNoSpacesOffTop(args);
        rFfF = readBasicPosition(args);
    }
    else if (args[0].find("offset") != std::string::npos) {
        args.erase(args.begin());
        rFfF = readBasicPosition(args);
    }
    else if (args[0].find("null") != std::string::npos) {
        args.erase(args.begin());
    }
    else {
        rFfF = readBasicPosition(args);
    }
}

void MBDynReference::readOrientation(std::vector<std::string>& args)
{
    aAFf = FullMatrix<double>::identitysptr(3);
    if (args.empty()) return;
    if (args[0].find("reference") != std::string::npos) {
        args.erase(args.begin());
        assert(baseRefName == readStringNoSpacesOffTop(args));
        aAFf = readBasicOrientation(args);
    }
    else if (args[0].find("hinge") != std::string::npos) {
        args.erase(args.begin());
        aAFf = readBasicOrientation(args);
    }
    else if (args[0].find("position") != std::string::npos) {
        if (args[0].find("orientation") != std::string::npos) {
            args.erase(args.begin());
            aAFf = readBasicOrientation(args);
        }
    }
    else if (args[0].find("orientation") != std::string::npos) {
        args.erase(args.begin());
        if (args[0].find("reference") != std::string::npos) {
            args.erase(args.begin());
            assert(baseRefName == readStringNoSpacesOffTop(args));
            aAFf = readBasicOrientation(args);
        }
    }
    else {
        aAFf = readBasicOrientation(args);
    }
}

void MBDynReference::readVelocity(std::vector<std::string>& args)
{
    auto parser = std::make_shared<SymbolicParser>();
    parser->variables = mbdynVariables();
    vFfF = std::make_shared<FullColumn<double>>(3);
    if (args[0].find("null") != std::string::npos) {
        args.erase(args.begin());
        return;
    }
    else if (args[0].find("velocity") != std::string::npos) {
        args.erase(args.begin());
        if (args[0].find("reference") != std::string::npos) {
            args.erase(args.begin());
            assert(baseRefName == readStringNoSpacesOffTop(args));
            vFfF = readVector3(args);
        }
    }
    else {
        vFfF = readVector3(args);
    }
}

void MBDynReference::readOmega(std::vector<std::string>& args)
{
    auto parser = std::make_shared<SymbolicParser>();
    parser->variables = mbdynVariables();
    omeFfF = std::make_shared<FullColumn<double>>(3);
    if (args[0].find("null") != std::string::npos) {
        args.erase(args.begin());
        return;
    }
    else if (lineHasTokens(args[0], "angular", "velocity")) {
        args.erase(args.begin());
        if (args[0].find("reference") != std::string::npos) {
            args.erase(args.begin());
            assert(baseRefName == readStringNoSpacesOffTop(args));
            omeFfF = readVector3(args);
        }
    }
    else {
        omeFfF = readVector3(args);
    }
}
