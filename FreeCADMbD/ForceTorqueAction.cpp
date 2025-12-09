#include "ForceTorqueAction.h"
#include "MarkerFrame.h"
#include "ForceTorqueFunction.h"
#include "ForceBasicqcVector.h"
#include "TorqueBasicVector.h"
#include "SimulationStoppingError.h"

using namespace MbD;

ForceTorqueAction::ForceTorqueAction(size_t count)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<ForceTorqueAction> ForceTorqueAction::With(size_t count)
{
    auto inst = std::make_shared<ForceTorqueAction>(count);
    inst->initialize();
    return inst;
}

void ForceTorqueAction::initialize()
{
    forTorFunction = ForceTorqueFunction::With();
}

std::shared_ptr<ForceTorqueFunction> ForceTorqueAction::getforTorFunction()
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<ForceTorqueFunction>();
}

void ForceTorqueAction::setforTorFunction(std::shared_ptr<ForceTorqueFunction> forTorFunction)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueAction::initializeGlobally()
{
    forTorFunction->initializeGlobally();
    forTorBasicI->initializeGlobally();
}

void ForceTorqueAction::initializeLocally()
{
    forTorFunction->initializeLocally();
    forTorBasicI->initializeLocally();
}

void ForceTorqueAction::postAccICIteration()
{
    forTorFunction->postAccICIteration();
    forTorBasicI->postAccICIteration();
    ForceTorqueItem::postAccICIteration();
}

void ForceTorqueAction::postCollisionCorrectorIteration()
{
    forTorFunction->postCollisionCorrectorIteration();
    forTorBasicI->postCollisionCorrectorIteration();
    ForceTorqueItem::postCollisionCorrectorIteration();
}

void ForceTorqueAction::postCollisionPredictor()
{
    forTorFunction->postCollisionPredictor();
    forTorBasicI->postCollisionPredictor();
    ForceTorqueItem::postCollisionPredictor();
}

void ForceTorqueAction::postDynCorrectorIteration()
{
    forTorFunction->postDynCorrectorIteration();
    forTorBasicI->postDynCorrectorIteration();
    ForceTorqueItem::postDynCorrectorIteration();
}

void ForceTorqueAction::postDynOutput()
{
    forTorFunction->postDynOutput();
    forTorBasicI->postDynOutput();
    ForceTorqueItem::postDynOutput();
}

void ForceTorqueAction::postDynPredictor()
{
    forTorFunction->postDynPredictor();
    forTorBasicI->postDynPredictor();
    ForceTorqueItem::postDynPredictor();
}

void ForceTorqueAction::postInput()
{
    forTorFunction->postInput();
    forTorBasicI->postInput();
    ForceTorqueItem::postInput();
}

void ForceTorqueAction::postStaticIteration()
{
    forTorFunction->postStaticIteration();
    forTorBasicI->postStaticIteration();
    ForceTorqueItem::postStaticIteration();
}

void ForceTorqueAction::preAccIC()
{
    forTorFunction->preAccIC();
    forTorBasicI->preAccIC();
    ForceTorqueItem::preAccIC();
}

void ForceTorqueAction::preDynOutput()
{
    forTorFunction->preDynOutput();
    forTorBasicI->preDynOutput();
    ForceTorqueItem::preDynOutput();
}

void ForceTorqueAction::preStatic()
{
    forTorFunction->preStatic();
    forTorBasicI->preStatic();
    ForceTorqueItem::preStatic();
}

void ForceTorqueAction::simUpdateAll()
{
    forTorFunction->simUpdateAll();
    forTorBasicI->simUpdateAll();
    ForceTorqueItem::simUpdateAll();
}

void ForceTorqueAction::useEquationNumbers()
{
    forTorFunction->useEquationNumbers();
    forTorBasicI->useEquationNumbers();
}

void ForceTorqueAction::forceOnFrmIaxis(EndFrmsptr frmi, size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueAction::torqueOnFrmIaxis(EndFrmsptr frmi, size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueAction::forceOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueAction::torqueOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}
