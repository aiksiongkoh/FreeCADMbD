#include "ForceBasicqcComp.h"
#include "ForceTorqueActionComp.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceBasicqcComp> ForceBasicqcComp::With()
{
    auto inst = std::make_shared<ForceBasicqcComp>();
    inst->initialize();
    return inst;
}

void ForceBasicqcComp::calcPostDynCorrectorIteration()
{
    //"rpep is not a constant for aMbDEndFrameqccq, qcs or qct."

    auto efrmqc = std::static_pointer_cast<EndFrameqc>(endFrame);
    auto axis = static_cast<ForceTorqueActionComp*>(parent)->axis;
    prOeOaxispET = efrmqc->prOeOpE->at(axis)->transpose();
}

void ForceBasicqcComp::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::useEquationNumbers()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcComp::fillAccICIterErroraFTOi(FColDsptr col, double aFTOi)
{
    col->atiplusNumber(iqXaxis, aFTOi);
    col->atiplusFullColumn(iqE, (prOeOaxispET->times(aFTOi)));
}
