/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "SimulationStoppingError.h"

using namespace MbD;

void MbD::throwUnsupportedFrameCombination(const std::string& factoryName)
{
    throw SimulationStoppingError("Unsupported frame combination in " + factoryName + ".");
}
