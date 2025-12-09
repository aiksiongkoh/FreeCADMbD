#include "EigenDecomposition.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<EigenDecomposition> EigenDecomposition::With()
{
    auto inst = std::make_shared<EigenDecomposition>();
    inst->initialize();
    return inst;
}

FColDsptr EigenDecomposition::basicSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

FColDsptr EigenDecomposition::basicSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

void EigenDecomposition::preSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
    throw SimulationStoppingError("To be implemented.");
}

void EigenDecomposition::preSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
    throw SimulationStoppingError("To be implemented.");
}

void EigenDecomposition::doPivoting(size_t p)
{
    throw SimulationStoppingError("To be implemented.");
}

void EigenDecomposition::forwardEliminateWithPivot(size_t p)
{
    throw SimulationStoppingError("To be implemented.");
}

void EigenDecomposition::backSubstituteIntoDU()
{
    throw SimulationStoppingError("To be implemented.");
}

void EigenDecomposition::postSolve()
{
    throw SimulationStoppingError("To be implemented.");
}

double EigenDecomposition::getmatrixArowimaxMagnitude(size_t i)
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}
