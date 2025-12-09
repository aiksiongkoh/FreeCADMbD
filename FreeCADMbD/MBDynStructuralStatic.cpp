#include "MBDynStructuralStatic.h"

using namespace MbD;

std::shared_ptr<MBDynStructuralStatic> MBDynStructuralStatic::With()
{
    auto inst = std::make_shared<MBDynStructuralStatic>();
    inst->initialize();
    return inst;
}

void MBDynStructuralStatic::parseMBDyn(std::string line)
{
    strucString = line;
    arguments = collectArgumentsFor("structural", line);
    readLabel(arguments);
    auto nodeType = readStringNoSpacesOffTop(arguments);
    assert(nodeType == "static");
    readPosition(arguments);
    readOrientation(arguments);
    readVelocity(arguments);
    readOmega(arguments);
}
