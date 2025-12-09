#include "MBDynNodePlugin.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynNodePlugin> MBDynNodePlugin::With()
{
    auto inst = std::make_shared<MBDynNodePlugin>();
    inst->initialize();
    return inst;
}

void MBDynNodePlugin::parseMBDyn(std::string line)
{
    pluginString = line;
    arguments = collectArgumentsFor("set", line);
    assert(lineHasToken(readStringNoSpacesOffTop(arguments), "node"));
    varName = readStringNoSpacesOffTop(arguments);
    nodeName = readStringNoSpacesOffTop(arguments);
    readStringNoSpacesOffTop(arguments);
    auto str = readStringNoSpacesOffTop(arguments);
    auto firstPos = str.find("\"", 0);
    auto secondPos = str.find("\"", firstPos + 1);
    _string = str.substr(firstPos + 1, secondPos - firstPos - 1);
}

void MBDynNodePlugin::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}
