#include <cassert>

#include "SolverStatistics.h"

using namespace MbD;

std::shared_ptr<SolverStatistics> SolverStatistics::With()
{
    auto inst = std::make_shared<SolverStatistics>();
    //inst->initialize();
    return inst;
}
