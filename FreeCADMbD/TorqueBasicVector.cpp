#include "TorqueBasicVector.h"
#include "PartFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<TorqueBasicVector> TorqueBasicVector::With()
{
    auto inst = std::make_shared<TorqueBasicVector>();
    inst->initialize();
    return inst;
}

void TorqueBasicVector::calcPostDynCorrectorIteration()
{
    twoBT = endFrame->markerFrame->partFrame->qE->aB->transpose()->times(2.0);
}

void TorqueBasicVector::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    col->atiplusFullColumn(iqE, (twoBT->timesFullColumn(aFTO)));
}

void TorqueBasicVector::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
    throw SimulationStoppingError("To be implemented.");
}

void TorqueBasicVector::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    col->atiplusFullColumn(iqE, twoBT->timesFullColumn(aFTO));
}

void TorqueBasicVector::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
    mat->atijplusFullMatrix(iqE, iqE, (EulerParameters<double>::pBTpEtimesColumn(aFTO->times(2.0))));
}

void TorqueBasicVector::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, PartFrame* partj)
{
    mat->atijplusFullMatrix(iqE, partj->iqE, (twoBT->timesFullMatrix(pFTOpEj)));
}

void TorqueBasicVector::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void TorqueBasicVector::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, PartFrame* partj)
{
    mat->atijplusFullMatrix(iqE, partj->iqX, twoBT->timesFullMatrix(pFTOpXj));
    mat->atijplusFullMatrix(iqE, partj->iqE, twoBT->timesFullMatrix(pFTOpEj));
}

void TorqueBasicVector::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void TorqueBasicVector::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
    throw SimulationStoppingError("To be implemented.");
}

void TorqueBasicVector::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void TorqueBasicVector::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}
