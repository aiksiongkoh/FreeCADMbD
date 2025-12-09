#include "MBDynDriveString.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynDriveString> MBDynDriveString::With()
{
    auto inst = std::make_shared<MBDynDriveString>();
    inst->initialize();
    return inst;
}

void MBDynDriveString::readFunction(std::vector<std::string>& args)
{
    assert(readStringNoSpacesOffTop(args) == "string");
    expression = popOffTop(args);
    output = readStringNoSpacesOffTop(args);
    yesno = readStringNoSpacesOffTop(args);
}

void MBDynDriveString::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}

