#include "MBDynGenel.h"
#include "MBDynClampGenel.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynGenel> MBDynGenel::newGenel(std::string statement)
{
    if (lineHasTokens(statement, "clamp")) {
        return MBDynClampGenel::With();
    }
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<MBDynGenel>();
}

void MBDynGenel::parseMBDyn(std::string line)
{
    throw SimulationStoppingError("To be implemented.");
}

void MBDynGenel::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}
