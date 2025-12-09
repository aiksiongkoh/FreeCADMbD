#include "ForceTorqueBasic.h"
#include "EndFramec.h"
#include "PartFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceTorqueBasic> ForceTorqueBasic::With()
{
    auto inst = std::make_shared<ForceTorqueBasic>();
    inst->initialize();
    return inst;
}

void ForceTorqueBasic::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::useEquationNumbers()
{
    iqE = endFrame->getPartFrame()->iqE;
}

void ForceTorqueBasic::fillAccICIterErroraFTOi(FColDsptr col, double aFTOi)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::fillpFpydotpFOpmudot(SpMatDsptr mat, SpMatDsptr pFOpmudot)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueBasic::endFramefollowEndFrame(EndFrmsptr frmj, EndFrmsptr frmi)
{
    endFrame = frmj->followEndFrame(frmi);
}
