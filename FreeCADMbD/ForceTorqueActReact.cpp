#include "ForceTorqueActReact.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActReact> ForceTorqueActReact::With()
{
    auto inst = std::make_shared<ForceTorqueActReact>();
    inst->initialize();
    return inst;
}

FColDsptr ForceTorqueActReact::getFTIeO() const
{
    return forTorAction->getFTIeO();
}

std::shared_ptr<ForceTorqueFunction> ForceTorqueActReact::getforTorFunction()
{
    return forTorAction->forTorFunction;
}

void ForceTorqueActReact::setforTorFunction(std::shared_ptr<ForceTorqueFunction> forTorFunction)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueActReact::initializeGlobally()
{
    forTorAction->initializeGlobally();
    forTorBasicJ->initializeGlobally();
}

void ForceTorqueActReact::initializeLocally()
{
    forTorAction->initializeLocally();
    forTorBasicJ->initializeLocally();
}

void ForceTorqueActReact::postAccICIteration()
{
    forTorAction->postAccICIteration();
    forTorBasicJ->postAccICIteration();
    ForceTorqueItem::postAccICIteration();
}

void ForceTorqueActReact::postCollisionCorrectorIteration()
{
    forTorAction->postCollisionCorrectorIteration();
    forTorBasicJ->postCollisionCorrectorIteration();
    ForceTorqueItem::postCollisionCorrectorIteration();
}

void ForceTorqueActReact::postCollisionPredictor()
{
    forTorAction->postCollisionPredictor();
    forTorBasicJ->postCollisionPredictor();
    ForceTorqueItem::postCollisionPredictor();
}

void ForceTorqueActReact::postDynCorrectorIteration()
{
    forTorAction->postDynCorrectorIteration();
    forTorBasicJ->postDynCorrectorIteration();
    ForceTorqueItem::postDynCorrectorIteration();
}

void ForceTorqueActReact::postDynOutput()
{
    forTorAction->postDynOutput();
    forTorBasicJ->postDynOutput();
    ForceTorqueItem::postDynOutput();
}

void ForceTorqueActReact::postDynPredictor()
{
    forTorAction->postDynPredictor();
    forTorBasicJ->postDynPredictor();
    ForceTorqueItem::postDynPredictor();
}

void ForceTorqueActReact::postInput()
{
    forTorAction->postInput();
    forTorBasicJ->postInput();
    ForceTorqueItem::postInput();
}

void ForceTorqueActReact::postStaticIteration()
{
    forTorAction->postStaticIteration();
    forTorBasicJ->postStaticIteration();
    ForceTorqueItem::postStaticIteration();
}

void ForceTorqueActReact::preAccIC()
{
    forTorAction->preAccIC();
    forTorBasicJ->preAccIC();
    ForceTorqueItem::preAccIC();
}

void ForceTorqueActReact::preDynOutput()
{
    forTorAction->preDynOutput();
    forTorBasicJ->preDynOutput();
    ForceTorqueItem::preDynOutput();
}

void ForceTorqueActReact::preStatic()
{
    forTorAction->preStatic();
    forTorBasicJ->preStatic();
    ForceTorqueItem::preStatic();
}

void ForceTorqueActReact::simUpdateAll()
{
    forTorAction->simUpdateAll();
    forTorBasicJ->simUpdateAll();
    ForceTorqueItem::simUpdateAll();
}

void ForceTorqueActReact::useEquationNumbers()
{
    forTorAction->useEquationNumbers();
    forTorBasicJ->useEquationNumbers();
}
