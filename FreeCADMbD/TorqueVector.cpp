#include "TorqueVector.h"
#include "ForceTorqueActReactOComp.h"
#include "ForceTorqueActReactKComp.h"

using namespace MbD;

std::shared_ptr<TorqueVector> TorqueVector::OnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<TorqueVector>();
    inst->initialize();
    inst->onFrmIandFrmJ(frmi, frmj);
    return inst;
}

std::shared_ptr<TorqueVector> TorqueVector::OnFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    auto inst = std::make_shared<TorqueVector>();
    inst->initialize();
    inst->onFrmIandFrmJwrtFrmK(frmi, frmj, frmk);
    return inst;
}

void TorqueVector::onFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto comps = FullColumn<std::shared_ptr<ForceTorqueActReactComp>>::With();
    comps->push_back(ForceTorqueActReactOComp::TorqueOnFrmIandFrmJaxis(frmi, frmj, 0));
    comps->push_back(ForceTorqueActReactOComp::TorqueOnFrmIandFrmJaxis(frmi, frmj, 1));
    comps->push_back(ForceTorqueActReactOComp::TorqueOnFrmIandFrmJaxis(frmi, frmj, 2));
    components = comps;
}

void TorqueVector::onFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    auto comps = FullColumn<std::shared_ptr<ForceTorqueActReactComp>>::With();
    comps->push_back(ForceTorqueActReactKComp::TorqueOnFrmIandFrmJwrtFrmKaxis(frmi, frmj, frmk, 0));
    comps->push_back(ForceTorqueActReactKComp::TorqueOnFrmIandFrmJwrtFrmKaxis(frmi, frmj, frmk, 1));
    comps->push_back(ForceTorqueActReactKComp::TorqueOnFrmIandFrmJwrtFrmKaxis(frmi, frmj, frmk, 2));
    components = comps;
}
