#include <regex>

#include "MBDynClampGenel.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynClampGenel> MBDynClampGenel::With()
{
    auto inst = std::make_shared<MBDynClampGenel>();
    inst->initialize();
    return inst;
}

void MBDynClampGenel::parseMBDyn(std::string line)
{
    genelString = line;
    arguments = collectArgumentsFor("genel", line);
    readLabel(arguments);
    type = readStringNoSpacesOffTop(arguments);
    nodeName = readStringNoSpacesOffTop(arguments);
    assert(readStringNoSpacesOffTop(arguments) == "abstract");
    valueType = readStringNoSpacesOffTop(arguments);
    assert(readStringNoSpacesOffTop(arguments) == "string");
    formula = popOffTop(arguments);
    formula = std::regex_replace(formula, std::regex("\""), "");
}

void MBDynClampGenel::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}
