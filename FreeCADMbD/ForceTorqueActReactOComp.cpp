#include "ForceTorqueActReactOComp.h"
#include "ForceBasicqccqComp.h"
#include "ForceTorqueActionOComp.h"
#include "TorqueBasicComp.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActReactOComp> ForceTorqueActReactOComp::With()
{
    auto inst = std::make_shared<ForceTorqueActReactOComp>();
    inst->initialize();
    return inst;
}

void ForceTorqueActReactOComp::initialize()
{
    forTorAction = ForceTorqueActionOComp::With();
}

std::shared_ptr<ForceTorqueActReactOComp> ForceTorqueActReactOComp::ForceOnFrmIandFrmJaxis(EndFrmsptr eFrmI, EndFrmsptr eFrmJ, size_t axis)
{
    auto forTor = ForceTorqueActReactOComp::With();
    forTor->forceOnFrmIandFrmJaxis(eFrmI, eFrmJ, axis);
    return forTor;
}

std::shared_ptr<ForceTorqueActReactOComp> ForceTorqueActReactOComp::TorqueOnFrmIandFrmJaxis(EndFrmsptr eFrmI, EndFrmsptr eFrmJ, size_t axis)
{
    auto forTor = ForceTorqueActReactOComp::With();
    forTor->torqueOnFrmIandFrmJaxis(eFrmI, eFrmJ, axis);
    return forTor;
}

void ForceTorqueActReactOComp::forceOnFrmIandFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    forTorAction->forceOnFrmIaxis(frmi, axis);
    forTorBasicJ = ForceBasicqccqComp::With();
    forTorBasicJ->parent = this;
    forTorBasicJ->endFramefollowEndFrame(frmj, frmi);
}

void ForceTorqueActReactOComp::torqueOnFrmIandFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    forTorAction->torqueOnFrmIaxis(frmi, axis);
    forTorBasicJ = TorqueBasicComp::With();
    forTorBasicJ->parent = this;
    forTorBasicJ->endFrame = frmj;
}

void ForceTorqueActReactOComp::postDynPredictor()
{
    throw SimulationStoppingError("To be implemented.");
}
