#include <regex>

#include "MBDynOutputMeter.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynOutputMeter> MBDynOutputMeter::With()
{
    auto inst = std::make_shared<MBDynOutputMeter>();
    inst->initialize();
    return inst;
}

void MBDynOutputMeter::parseMBDyn(std::string line)
{
    outputMeterString = line;
    arguments = collectArgumentsFor("output meter", line);
    assert(readStringNoSpacesOffTop(arguments) == "string");
    formula = popOffTop(arguments);
    formula = std::regex_replace(formula, std::regex("\""), "");
}

void MBDynOutputMeter::readFunction(std::vector<std::string>& args)
{
    throw SimulationStoppingError("To be implemented.");
}
