#include "MBDynDriveElement.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynDriveElement> MBDynDriveElement::With()
{
    auto inst = std::make_shared<MBDynDriveElement>();
    inst->initialize();
    return inst;
}

void MBDynDriveElement::readFunction(std::vector<std::string>& args)
{
    assert(readStringNoSpacesOffTop(args) == "element");
    elementLabel = readStringNoSpacesOffTop(args);
    elementType = readStringNoSpacesOffTop(args);
    str = readStringNoSpacesOffTop(args);
    component = readStringNoSpacesOffTop(args);
    direct = readStringNoSpacesOffTop(args);
    output = readStringNoSpacesOffTop(args);
    yesno = readStringNoSpacesOffTop(args);
}

void MBDynDriveElement::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}
