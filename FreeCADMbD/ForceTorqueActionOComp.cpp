#include "ForceTorqueActionOComp.h"
#include "ForceTorqueBasic.h"
#include "ForceBasicqcComp.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActionOComp> ForceTorqueActionOComp::With()
{
    auto inst = std::make_shared<ForceTorqueActionOComp>();
    inst->initialize();
    return inst;
}

void ForceTorqueActionOComp::calcPostDynCorrectorIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionOComp::fillAccICIterError(FColDsptr col)
{
    forTorBasicI->fillAccICIterErroraFTOi(col, aFTIeOi);
}

void ForceTorqueActionOComp::fillAccICIterJacob(SpMatDsptr mat)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionOComp::fillDynError(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionOComp::fillpFpy(SpMatDsptr mat)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionOComp::fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionOComp::fillpFpydot(SpMatDsptr mat)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionOComp::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionOComp::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionOComp::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr ForceTorqueActionOComp::getFTIeO() const
{
    return FColDsptr();
}

void ForceTorqueActionOComp::forceOnFrmIaxis(EndFrmsptr frmi, size_t axis)
{
    forTorBasicI = ForceBasicqcComp::With();
    forTorBasicI->parent = this;
    forTorBasicI->endFrame = frmi;
}

void ForceTorqueActionOComp::torqueOnFrmIaxis(EndFrmsptr frmi, size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActionOComp::postDynPredictor()
{
    throw SimulationStoppingError("To be implemented.");
}
