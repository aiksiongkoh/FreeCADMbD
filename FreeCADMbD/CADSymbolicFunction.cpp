#include "CADSymbolicFunction.h"

using namespace MbD;

std::shared_ptr<CADSymbolicFunction> CADSymbolicFunction::With()
{
    auto inst = std::make_shared<CADSymbolicFunction>();
    inst->initialize();
    return inst;
}

Symsptr CADSymbolicFunction::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    return sptr;
}

Symsptr CADSymbolicFunction::simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    return sptr;
}

bool CADSymbolicFunction::isConstant()
{
    return false;
}

void CADSymbolicFunction::fillKineIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs)
{
    xx->fillKineIJs(kineIJs);
}

void CADSymbolicFunction::fillKinedotIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kinedotIJs)
{
    xx->fillKinedotIJs(kinedotIJs);
}

void CADSymbolicFunction::fillJointForces(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointForces)
{
    xx->fillJointForces(jointForces);
}

void CADSymbolicFunction::fillJointTorques(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointTorques)
{
    xx->fillJointTorques(jointTorques);
}
