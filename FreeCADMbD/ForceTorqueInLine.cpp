#include "ForceTorqueInLine.h"
#include "ForceTorqueFunction.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ForceTorqueInLine> ForceTorqueInLine::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ForceTorqueInLine>(frmi, frmj);
    //inst->initialize();    //Need to pass arguments.
    inst->forceInLine = ForceTorqueActReactInLine::ForceOnFrmIandFrmJ(frmi, frmj);
    inst->torqueInLine = ForceTorqueActReactInLine::TorqueOnFrmIandFrmJ(frmi, frmj);
    return inst;
}

void ForceTorqueInLine::initializeGlobally()
{
    forceInLine->initializeGlobally();
    torqueInLine->initializeGlobally();
}

void ForceTorqueInLine::initializeLocally()
{
    forceInLine->initializeLocally();
    torqueInLine->initializeLocally();
}

void ForceTorqueInLine::postDynPredictor()
{
    forceInLine->postDynPredictor();
    torqueInLine->postDynPredictor();
}

void ForceTorqueInLine::postInput()
{
    forceInLine->postInput();
    torqueInLine->postInput();
}

void ForceTorqueInLine::postStaticIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueInLine::preAccIC()
{
    forceInLine->preAccIC();
    torqueInLine->preAccIC();
}

void ForceTorqueInLine::preDynOutput()
{
    forceInLine->preDynOutput();
    torqueInLine->preDynOutput();
}

void ForceTorqueInLine::preStatic()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueInLine::simUpdateAll()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueInLine::fillAccICIterError(FColDsptr col)
{
    forceInLine->fillAccICIterError(col);
    torqueInLine->fillAccICIterError(col);
}

void ForceTorqueInLine::fillAccICIterJacob(SpMatDsptr mat)
{
    forceInLine->fillAccICIterJacob(mat);
    torqueInLine->fillAccICIterJacob(mat);
}

void ForceTorqueInLine::fillDynError(FColDsptr col)
{
    forceInLine->fillDynError(col);
    torqueInLine->fillDynError(col);
}

void ForceTorqueInLine::fillpFpy(SpMatDsptr mat)
{
    forceInLine->fillpFpy(mat);
    torqueInLine->fillpFpy(mat);
}

void ForceTorqueInLine::fillpFpydot(SpMatDsptr mat)
{
    forceInLine->fillpFpydot(mat);
    torqueInLine->fillpFpydot(mat);
}

void ForceTorqueInLine::fillStaticError(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueInLine::fillStaticJacob(SpMatDsptr mat)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueInLine::useEquationNumbers()
{
    forceInLine->useEquationNumbers();
    torqueInLine->useEquationNumbers();
}

void ForceTorqueInLine::tension(Symsptr tensionFunc)
{
    forceInLine->getforTorFunction()->setformula(tensionFunc);
}

void ForceTorqueInLine::twist(Symsptr twistFunc)
{
    torqueInLine->getforTorFunction()->setformula(twistFunc);
}

FColDsptr ForceTorqueInLine::aFX() const
{
    return forceInLine->getFTIeO();
}

FColDsptr ForceTorqueInLine::aTX() const
{
    return torqueInLine->getFTIeO();
}

void ForceTorqueInLine::postAccICIteration()
{
    forceInLine->postAccICIteration();
    torqueInLine->postAccICIteration();
}

void ForceTorqueInLine::postCollisionCorrectorIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueInLine::postCollisionPredictor()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueInLine::postDynCorrectorIteration()
{
    forceInLine->postDynCorrectorIteration();
    torqueInLine->postDynCorrectorIteration();
}

void ForceTorqueInLine::postDynOutput()
{
    forceInLine->postDynOutput();
    torqueInLine->postDynOutput();
}
