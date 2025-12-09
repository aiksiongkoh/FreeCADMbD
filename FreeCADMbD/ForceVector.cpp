#include "ForceVector.h"
#include "ForceTorqueActReactOComp.h"
#include "ForceTorqueActReactKComp.h"

using namespace MbD;

std::shared_ptr<ForceVector> ForceVector::OnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<ForceVector>();
    inst->initialize();
    inst->onFrmIandFrmJ(frmi, frmj);
    return inst;
}

std::shared_ptr<ForceVector> ForceVector::OnFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    auto inst = std::make_shared<ForceVector>();
    inst->initialize();
    inst->onFrmIandFrmJwrtFrmK(frmi, frmj, frmk);
    return inst;
}

void ForceVector::onFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto comps = FullColumn<std::shared_ptr<ForceTorqueActReactComp>>::With();
    comps->push_back(ForceTorqueActReactOComp::ForceOnFrmIandFrmJaxis(frmi, frmj, 0));
    comps->push_back(ForceTorqueActReactOComp::ForceOnFrmIandFrmJaxis(frmi, frmj, 1));
    comps->push_back(ForceTorqueActReactOComp::ForceOnFrmIandFrmJaxis(frmi, frmj, 2));
    components = comps;
}

void ForceVector::onFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    auto comps = FullColumn<std::shared_ptr<ForceTorqueActReactComp>>::With();
    comps->push_back(ForceTorqueActReactKComp::ForceOnFrmIandFrmJwrtFrmKaxis(frmi, frmj, frmk, 0));
    comps->push_back(ForceTorqueActReactKComp::ForceOnFrmIandFrmJwrtFrmKaxis(frmi, frmj, frmk, 1));
    comps->push_back(ForceTorqueActReactKComp::ForceOnFrmIandFrmJwrtFrmKaxis(frmi, frmj, frmk, 2));
    components = comps;
}
