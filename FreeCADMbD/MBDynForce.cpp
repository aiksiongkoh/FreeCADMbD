#include <regex>

#include "MBDynForce.h"
#include "MBDynAbsoluteForce.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynForce> MBDynForce::newForce(std::string statement)
{
    if (lineHasTokens(statement, "absolute")) {
        return MBDynAbsoluteForce::With();
    }
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<MBDynForce>();
}

void MBDynForce::parseMBDyn(std::string line)
{
    throw SimulationStoppingError("To be implemented.");
}

void MBDynForce::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}
