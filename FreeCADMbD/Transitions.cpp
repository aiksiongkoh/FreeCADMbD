#include "Transitions.h"

using namespace MbD;

std::shared_ptr<Transitions> Transitions::With()
{
    auto inst = std::make_shared<Transitions>();
    inst->initialize();
    return inst;
}
