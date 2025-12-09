#include "MBDynDriveMeter.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynDriveMeter> MBDynDriveMeter::With()
{
    auto inst = std::make_shared<MBDynDriveMeter>();
    inst->initialize();
    return inst;
}

void MBDynDriveMeter::readFunction(std::vector<std::string>& args)
{
    assert(readStringNoSpacesOffTop(args) == "meter");
    assert(readDoubleOffTop(args) == 0.0);
    assert(readStringNoSpacesOffTop(args) == "forever");
    assert(readStringNoSpacesOffTop(args) == "steps");
    auto steps = readIntOffTop(args);
    auto ss = std::stringstream();
    ss << steps;
    formula = ss.str();

}

void MBDynDriveMeter::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}

