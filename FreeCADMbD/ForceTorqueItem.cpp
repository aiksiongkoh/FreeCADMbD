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
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueItem::fillStaticJacob(SpMatDsptr mat)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueItem::postAccICIteration()
{
    calcPostDynCorrectorIteration();
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
    return FColDsptr();
}

void ForceTorqueItem::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    throw SimulationStoppingError("To be implemented.");
}

void ForceTorqueItem::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    throw SimulationStoppingError("To be implemented.");
}
