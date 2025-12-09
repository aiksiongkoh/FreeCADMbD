#include "MBDynBody.h"
#include "MBDynReference.h"
#include "MBDynStructural.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "ASMTPart.h"
#include "ASMTAssembly.h"
#include "MomentOfInertiaSolver.h"

using namespace MbD;

std::shared_ptr<MBDynBody> MBDynBody::With()
{
    auto inst = std::make_shared<MBDynBody>();
    inst->initialize();
    return inst;
}

void MBDynBody::initialize()
{
    masses = std::make_shared<std::vector<double>>();
    rPcmPs = std::make_shared<std::vector<FColDsptr>>();
    aJmats = std::make_shared<std::vector<FMatDsptr>>();
    aAPcms = std::make_shared<std::vector<FMatDsptr>>();
}

void MBDynBody::parseMBDyn(std::string line)
{
    bodyString = line;
    arguments = collectArgumentsFor("body", line);
    readLabel(arguments);
    nodeName = readStringNoSpacesOffTop(arguments);
    if (arguments[0].find("condense") != std::string::npos) {
        arguments.erase(arguments.begin());
        auto str = readStringNoSpacesOffTop(arguments);
        auto num_masses = readInt(str);
        assert(num_masses == 1);
        for (size_t i = 0; i < num_masses; i++)
        {
            readMassProps(arguments);
        }
    }
    else {
        readMassProps(arguments);
    }
}

void MBDynBody::readMass(std::vector<std::string>& args)
{
    auto parser = std::make_shared<SymbolicParser>();
    parser->variables = mbdynVariables();
    auto userFunc = std::make_shared<BasicUserFunction>(popOffTop(args), 1.0);
    parser->parseUserFunction(userFunc);
    auto sym = parser->stack->top();
    mass = sym->getValue();
    masses->push_back(mass);
}

void MBDynBody::readPositionCM(std::vector<std::string>& args)
{
    rPcmP = readPosition(args);
    rPcmPs->push_back(rPcmP);
}

void MBDynBody::readInertiaMatrix(std::vector<std::string>& args)
{
    auto parser = std::make_shared<SymbolicParser>();
    parser->variables = mbdynVariables();
    aJmat = FullMatrix<double>::With(3, 3);
    auto str = args.at(0);    //Must copy string
    if (str.find("diag") != std::string::npos) {
        args.erase(args.begin());
        for (size_t i = 0; i < 3; i++)
        {
            auto userFunc = std::make_shared<BasicUserFunction>(popOffTop(args), 1.0);
            parser->parseUserFunction(userFunc);
            auto sym = parser->stack->top();
            aJmat->at(i)->at(i) = sym->getValue();
        }
    }
    else if (str.find("eye") != std::string::npos) {
        args.erase(args.begin());
        aJmat->identity();
    }
    else {
        aJmat = readBasicOrientation(args);
    }
    aJmats->push_back(aJmat);
}

void MBDynBody::readOrientationCM(std::vector<std::string>& args)
{
    aAPcm = readOrientation(args);
    aAPcms->push_back(aAPcm);
}

void MBDynBody::readMassProps(std::vector<std::string>& args)
{
    readMass(args);
    readPositionCM(args);
    readInertiaMatrix(args);
    readOrientationCM(args);
}

void MBDynBody::createASMT()
{
    auto asmtMassMarker = ASMTPrincipalMassMarker::With();
    asmtItem = asmtMassMarker;
    asmtMassMarker->setMass(mass);
    if (aJmat->isDiagonalToWithin(1.0e-6)) {
        asmtMassMarker->setMomentOfInertias(aJmat->asDiagonalMatrix());
        asmtMassMarker->setPosition3D(rPcmP);
        asmtMassMarker->setRotationMatrix(aAPcm);
        auto asmtPart = asmtAssembly()->partPartialNamed(nodeName);
        asmtPart->setPrincipalMassMarker(asmtMassMarker);
    }
    else {
        auto solver = std::make_shared<MomentOfInertiaSolver>();
        solver->setm(mass);
        solver->setJPP(aJmat);
        solver->setrPoP(rPcmP);
        solver->setAPo(aAPcm);
        solver->setrPcmP(rPcmP);
        solver->calc();
        asmtMassMarker->setMomentOfInertias(solver->aJpp);
        asmtMassMarker->setPosition3D(rPcmP);
        asmtMassMarker->setRotationMatrix(solver->aAPp);
        auto asmtPart = asmtAssembly()->partPartialNamed(nodeName);
        asmtPart->setPrincipalMassMarker(asmtMassMarker);
    }
}
