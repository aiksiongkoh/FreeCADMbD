#include "MBDynPlugin.h"
#include "MBDynNodePlugin.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynPlugin> MBDynPlugin::newPlugin(std::string statement)
{
    if (lineHasTokens(statement, "set:", "[", "node")) {
        return MBDynNodePlugin::With();
    }
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<MBDynPlugin>();
}

void MBDynPlugin::parseMBDyn(std::string line)
{
    throw SimulationStoppingError("To be implemented.");
}

void MBDynPlugin::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}
