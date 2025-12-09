#include "ForceBasicqcVector.h"
#include "PartFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceBasicqcVector> ForceBasicqcVector::With()
{
    auto inst = std::make_shared<ForceBasicqcVector>();
    inst->initialize();
    return inst;
}

void ForceBasicqcVector::calcPostDynCorrectorIteration()
{
    //"rpep is not a constant for aMbDEndFrameqccq, qcs or qct."

    prOeOpET = std::static_pointer_cast<EndFrameqc>(endFrame)->prOeOpE->transpose();
}

void ForceBasicqcVector::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    col->atiplusFullColumn(iqX, aFTO);
    col->atiplusFullColumn(iqE, (prOeOpET->timesFullColumn(aFTO)));
}

void ForceBasicqcVector::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcVector::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    col->atiplusFullColumn(iqX, aFTO);
    col->atiplusFullColumn(iqE, prOeOpET->timesFullColumn(aFTO));
}

void ForceBasicqcVector::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
    auto endFrmqc = std::static_pointer_cast<EndFrameqc>(endFrame);
    auto pprOeOpEpE = endFrmqc->pprOeOpEpE;
    for (size_t i = 0; i < 4; i++) {
        auto pprOeOpEpEi = pprOeOpEpE->at(i);
        auto mati = mat->at(iqE + i);
        for (size_t j = 0; j < 4; j++) {
            auto pprOeOpEpEij = pprOeOpEpEi->at(j);
            mati->atiplusNumber(iqE + j, pprOeOpEpEij->dot(aFTO));
        }
    }
}

void ForceBasicqcVector::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, PartFrame* partj)
{
    auto iqEj = partj->iqE;
    mat->atijplusFullMatrix(iqX, iqEj, pFTOpEj);
    mat->atijplusFullMatrix(iqE, iqEj, prOeOpET->timesFullMatrix(pFTOpEj));
}

void ForceBasicqcVector::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, PartFrame* partj)
{
    auto iqXj = partj->iqX;
    mat->atijplusFullMatrix(iqX, iqXj, pFTOpXj);
    mat->atijplusFullMatrix(iqE, iqXj, prOeOpET->timesFullMatrix(pFTOpXj));
}

void ForceBasicqcVector::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, PartFrame* partj)
{
    fillpFpypFTOpXjpartj(mat, pFTOpXj, partj);
    fillpFpypFTOpEjpartj(mat, pFTOpEj, partj);
}

void ForceBasicqcVector::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
    auto iqEj = partj->iqE;
    mat->atijplusFullMatrix(iqX, iqEj, pFTOpEdotj);
    mat->atijplusFullMatrix(iqE, iqEj, prOeOpET->timesFullMatrix(pFTOpEdotj));
}

void ForceBasicqcVector::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceBasicqcVector::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, PartFrame* partj)
{
    auto iqXj = partj->iqX;
    mat->atijplusFullMatrix(iqX, iqXj, pFTOpXdotj);
    mat->atijplusFullMatrix(iqE, iqXj, prOeOpET->timesFullMatrix(pFTOpXdotj));
}

void ForceBasicqcVector::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
    fillpFpydotpFTOpXdotjpartj(mat, pFTOpXdotj, partj);
    fillpFpydotpFTOpEdotjpartj(mat, pFTOpEdotj, partj);
}

void ForceBasicqcVector::useEquationNumbers()
{
    ForceTorqueBasic::useEquationNumbers();
    iqX = std::static_pointer_cast<EndFrameqc>(endFrame)->iqX();
}
