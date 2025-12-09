/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIecJecIe.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<DispCompIecJecIe> DispCompIecJecIe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompIecJecIe>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompIecJecIe::withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axs)
{
    eFrmI = frmi;
    eFrmJ = frmj;
    axis = axs;
}

void DispCompIecJecIe::calc_value()
{
    aAjOIe = eFrmI->aAjOe(axis);
    rIeJeO = eFrmJ->rOeO->minusFullColumn(eFrmI->rOeO);
    riIeJeIe = aAjOIe->dot(rIeJeO);
}

void DispCompIecJecIe::calcPostDynCorrectorIteration()
{
    calc_value();
}

double DispCompIecJecIe::value()
{
    return riIeJeIe;
}
