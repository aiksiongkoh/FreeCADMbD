/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompiIeJeO.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<DispCompiIeJeO> DispCompiIeJeO::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompiIeJeO>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompiIeJeO::initialize()
{
    Kinematic::initialize();
    dispIeJeO = DispIeJeO::With(eFrmI, eFrmJ);
    dispIeJeO->owner = this;
}

void DispCompiIeJeO::initializeLocally()
{
    KinematicCompiIeJe::initializeLocally();
    syncDispIeJeO();
    dispIeJeO->initializeLocally();
}

void DispCompiIeJeO::initializeGlobally()
{
    syncDispIeJeO();
    dispIeJeO->initializeGlobally();
}

void MbD::DispCompiIeJeO::useUniqueDispIeJeO()
{
    auto dispIeJeOs = root()->dispIeJeOs;
    auto it = std::find_if(dispIeJeOs->begin(), dispIeJeOs->end(), [&](auto disp) {return disp->hasSameEndFrms(dispIeJeO); });
    if (it == dispIeJeOs->end()) {
        dispIeJeOs->push_back(dispIeJeO);
    }
    else {
        dispIeJeO = *it;
    }
}

std::shared_ptr<KinematicVectorIeJe> DispCompiIeJeO::kineVector() const
{
    return dispIeJeO;
}

FColDsptr DispCompiIeJeO::currentVector() const
{
    return dispIeJeO->rIeJeO;
}

void DispCompiIeJeO::syncDispIeJeO() const
{
    dispIeJeO->withFrmIFrmJ(eFrmI, eFrmJ);
}
