/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ForceTorqueItem.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void ForceTorqueItem::fillStaticError(FColDsptr col)
{
    fillDynError(col);
}

void ForceTorqueItem::fillStaticJacob(SpMatDsptr mat)
{
    fillpFpy(mat);
}

void ForceTorqueItem::postAccICIteration()
{
    simUpdateAll();
}

void ForceTorqueItem::postCollisionCorrectorIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueItem::postCollisionPredictor()
{
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr ForceTorqueItem::getFTIeO() const
{
    throw SimulationStoppingError("To be implemented.");
}
