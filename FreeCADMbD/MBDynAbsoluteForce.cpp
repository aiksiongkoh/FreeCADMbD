#include <regex>

#include "MBDynAbsoluteForce.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynAbsoluteForce> MBDynAbsoluteForce::With()
{
    auto inst = std::make_shared<MBDynAbsoluteForce>();
    inst->initialize();
    return inst;
}

void MBDynAbsoluteForce::parseMBDyn(std::string line)
{
    forceString = line;
    arguments = collectArgumentsFor("force", line);
    readLabel(arguments);
    type = readStringNoSpacesOffTop(arguments);
    nodeName = readStringNoSpacesOffTop(arguments);
    rnmn = readPosition(arguments);
    assert(readStringNoSpacesOffTop(arguments) == "single");
    fn = readVector3(arguments);
    assert(readStringNoSpacesOffTop(arguments) == "string");
    formula = popOffTop(arguments);
    formula = std::regex_replace(formula, std::regex("\""), "");
}

void MBDynAbsoluteForce::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}
