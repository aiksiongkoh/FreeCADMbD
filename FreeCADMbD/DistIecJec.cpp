/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistIecJec.h"
#include "EndFramec.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<DistIecJec> DistIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistIecJec>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistIecJec::calcPostDynCorrectorIteration()
{
    rIeJeO = eFrmJ->rOeO->minusFullColumn(eFrmI->rOeO);
    rIeJe = rIeJeO->length();
    calcPrivate();
}

void DistIecJec::calcPrivate()
{
    if (rIeJe == 0.0) return;
    uIeJeO = rIeJeO->times(1.0 / rIeJe);
    muIeJeO = uIeJeO->negated();
}

double DistIecJec::value()
{
    return rIeJe;
}

FColDsptr DistIecJec::rIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}
