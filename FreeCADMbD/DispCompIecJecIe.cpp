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
    throw SimulationStoppingError("To be implemented.");
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

void DispCompIecJecIe::calcvalue()
{
    aAjOIe = eFrmI->aAjOe(axis);
    rIeJeO = getrIeJeO();
    riIeJeIe = aAjOIe->dot(rIeJeO);
}

void DispCompIecJecIe::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    //rIeJeIe = aAIeO * rIeJeO
    //riIeJeIe = aArowiIeO dot rIeJeO = aAcoljOIe dot rIeJeO
    calcvalue();
}

double DispCompIecJecIe::value()
{
    return riIeJeIe;
}
