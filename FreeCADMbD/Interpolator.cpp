#include "Interpolator.h"

using namespace MbD;

std::shared_ptr<Interpolator> Interpolator::With()
{
    auto inst = std::make_shared<Interpolator>();
    inst->initialize();
    return inst;
}
