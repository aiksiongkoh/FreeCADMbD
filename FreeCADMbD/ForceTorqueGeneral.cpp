#include "ForceTorqueGeneral.h"

using namespace MbD;

std::shared_ptr<ForceTorqueGeneral> ForceTorqueGeneral::OnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ForceTorqueGeneral>();
    inst->initialize();
    inst->onFrmIandFrmJ(frmi, frmj);
    return inst;
}

std::shared_ptr<ForceTorqueGeneral> ForceTorqueGeneral::OnFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    auto inst = std::make_shared<ForceTorqueGeneral>();
    inst->initialize();
    inst->onFrmIandFrmJwrtFrmK(frmi, frmj, frmk);
    return inst;
}

void ForceTorqueGeneral::onFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    forceVector = ForceVector::OnFrmIandFrmJ(frmi, frmj);
    torqueVector = TorqueVector::OnFrmIandFrmJ(frmi, frmj);
}

void ForceTorqueGeneral::onFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    eFrmI = frmi;
    eFrmJ = frmj;
    forceVector = ForceVector::OnFrmIandFrmJwrtFrmK(frmi, frmj, frmk);
    torqueVector = TorqueVector::OnFrmIandFrmJwrtFrmK(frmi, frmj, frmk);
}

void ForceTorqueGeneral::initializeGlobally()
{
    forceVector->initializeGlobally();
    torqueVector->initializeGlobally();
}

void ForceTorqueGeneral::initializeLocally()
{
    forceVector->initializeLocally();
    torqueVector->initializeLocally();
}

FColDsptr ForceTorqueGeneral::aFX() const
{
    return forceVector->getFTIeO();
}

FColDsptr ForceTorqueGeneral::aTX() const
{
    return torqueVector->getFTIeO();
}

void ForceTorqueGeneral::postAccICIteration()
{
    forceVector->postAccICIteration();
    torqueVector->postAccICIteration();
}

void ForceTorqueGeneral::postCollisionCorrectorIteration()
{
    forceVector->postCollisionCorrectorIteration();
    torqueVector->postCollisionCorrectorIteration();
}

void ForceTorqueGeneral::postCollisionPredictor()
{
    forceVector->postCollisionPredictor();
    torqueVector->postCollisionPredictor();
}

void ForceTorqueGeneral::postDynCorrectorIteration()
{
    forceVector->postDynCorrectorIteration();
    torqueVector->postDynCorrectorIteration();
}

void ForceTorqueGeneral::postDynOutput()
{
    forceVector->postDynOutput();
    torqueVector->postDynOutput();
}

void ForceTorqueGeneral::postDynPredictor()
{
    forceVector->postDynPredictor();
    torqueVector->postDynPredictor();
}

void ForceTorqueGeneral::postInput()
{
    forceVector->postInput();
    torqueVector->postInput();
}

void ForceTorqueGeneral::postStaticIteration()
{
    forceVector->postStaticIteration();
    torqueVector->postStaticIteration();
}

void ForceTorqueGeneral::preAccIC()
{
    forceVector->preAccIC();
    torqueVector->preAccIC();
}

void ForceTorqueGeneral::preDynOutput()
{
    forceVector->preDynOutput();
    torqueVector->preDynOutput();
}

void ForceTorqueGeneral::preStatic()
{
    forceVector->preStatic();
    torqueVector->preStatic();
}

void ForceTorqueGeneral::simUpdateAll()
{
    forceVector->simUpdateAll();
    torqueVector->simUpdateAll();
}

void ForceTorqueGeneral::torqueFunctions(FColsptr<Symsptr> col)
{
    torqueVector->functions(col);
}

void ForceTorqueGeneral::fillAccICIterError(FColDsptr col)
{
    forceVector->fillAccICIterError(col);
    torqueVector->fillAccICIterError(col);
}

void ForceTorqueGeneral::fillAccICIterJacob(SpMatDsptr mat)
{
    forceVector->fillAccICIterJacob(mat);
    torqueVector->fillAccICIterJacob(mat);
}

void ForceTorqueGeneral::fillDynError(FColDsptr col)
{
    forceVector->fillDynError(col);
    torqueVector->fillDynError(col);
}

void ForceTorqueGeneral::fillpFpy(SpMatDsptr mat)
{
    forceVector->fillpFpy(mat);
    torqueVector->fillpFpy(mat);
}

void ForceTorqueGeneral::fillpFpydot(SpMatDsptr mat)
{
    forceVector->fillpFpydot(mat);
    torqueVector->fillpFpydot(mat);
}

void ForceTorqueGeneral::fillStaticError(FColDsptr col)
{
    forceVector->fillStaticError(col);
    torqueVector->fillStaticError(col);
}

void ForceTorqueGeneral::fillStaticJacob(SpMatDsptr mat)
{
    forceVector->fillStaticJacob(mat);
    torqueVector->fillStaticJacob(mat);
}

void ForceTorqueGeneral::forceFunctions(FColsptr<Symsptr> col)
{
    forceVector->functions(col);
}

void ForceTorqueGeneral::useEquationNumbers()
{
    forceVector->useEquationNumbers();
    torqueVector->useEquationNumbers();
}
