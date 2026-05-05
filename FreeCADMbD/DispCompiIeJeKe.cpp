/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompiIeJeKe.h"
#include "EndFramec.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<DispCompiIeJeKe> DispCompiIeJeKe::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis)
{
    auto inst = std::make_shared<DispCompiIeJeKe>(frmi, frmj, frmk, axis);
    inst->initialize();
    return inst;
}

void DispCompiIeJeKe::initialize()
{
    Kinematic::initialize();
    dispIeJeKe = DispIeJeKe::With(eFrmI, eFrmJ, eFrmK);
    dispIeJeKe->owner = this;
}

void MbD::DispCompiIeJeKe::useUniqueDispIeJeO()
{
    dispIeJeKe->useUniqueDispIeJeO();
}

void MbD::DispCompiIeJeKe::useUniqueDispIeJeKe()
{
    if (!dispIeJeKe) return;
    auto dispIeJeKes = root()->dispIeJeKes;
    auto it = std::find_if(dispIeJeKes->begin(), dispIeJeKes->end(), [&](auto disp) { return disp->hasSameEndFrms(dispIeJeKe); });
    if (it == dispIeJeKes->end()) {
        dispIeJeKes->push_back(dispIeJeKe);
    }
    else {
        dispIeJeKe = *it;
    }
}

FRowDsptr DispCompiIeJeKe::pvaluepXI()
{
    return componentRowFrom(dispIeJeKe->getpVectorpXI());
}

FRowDsptr DispCompiIeJeKe::pvaluepEI()
{
    return componentRowFrom(dispIeJeKe->getpVectorpEI());
}

FRowDsptr DispCompiIeJeKe::pvaluepXJ()
{
    return componentRowFrom(dispIeJeKe->getpVectorpXJ());
}

FRowDsptr DispCompiIeJeKe::pvaluepEJ()
{
    return componentRowFrom(dispIeJeKe->getpVectorpEJ());
}

FMatDsptr DispCompiIeJeKe::ppvaluepEIpEI()
{
    return dispIeJeKe->getppCompipEIpEI(axis);
}

FMatDsptr DispCompiIeJeKe::ppvaluepEJpEJ()
{
    return dispIeJeKe->getppCompipEJpEJ(axis);
}

double DispCompiIeJeKe::pvaluept()
{
    return componentFrom(dispIeJeKe->getpVectorpt());
}

double DispCompiIeJeKe::ppvalueptpt()
{
    return componentFrom(dispIeJeKe->getppVectorptpt());
}

std::shared_ptr<KinematicVectorIeJe> DispCompiIeJeKe::kineVector() const
{
    return dispIeJeKe;
}

FColDsptr DispCompiIeJeKe::currentVector() const
{
    return dispIeJeKe->rIeJeKe;
}
