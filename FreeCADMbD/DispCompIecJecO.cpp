/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIecJecO.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<DispCompIecJecO> DispCompIecJecO::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompIecJecO>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompIecJecO::withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axs)
{
    eFrmI = frmi;
    eFrmJ = frmj;
    axis = axs;
}

void DispCompIecJecO::calcPostDynCorrectorIteration()
{
    riIeJeO = eFrmJ->riOeO(axis) - eFrmI->riOeO(axis);
}

double DispCompIecJecO::value()
{
    return riIeJeO;
}
