#include "MBDynData.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynData> MBDynData::With()
{
    auto inst = std::make_shared<MBDynData>();
    inst->initialize();
    return inst;
}

void MBDynData::initialize()
{
    throw SimulationStoppingError("To be implemented.");
}

void MBDynData::parseMBDyn(std::vector<std::string>& lines)
{
    assert(lines.size() == 3);
    std::vector<std::string> tokens{ "problem:", "initial", "value" };
    auto problemit = findLineWith(lines, tokens);
    assert(problemit != lines.end());
}
