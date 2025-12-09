/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Function.h"
#include <cassert>
#include "SimulationStoppingError.h"

using namespace MbD;

void Function::arguments(Symsptr args)
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}
