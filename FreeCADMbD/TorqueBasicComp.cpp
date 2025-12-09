#include "TorqueBasicComp.h"

using namespace MbD;

std::shared_ptr<TorqueBasicComp> TorqueBasicComp::With()
{
    auto torqueBasicComp = std::make_shared<TorqueBasicComp>();
    torqueBasicComp->initialize();
    return torqueBasicComp;
}
