/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstraintIJ.h"
#include "EndFrameqc.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ConstraintIJ> ConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<ConstraintIJ>();
}

void ConstraintIJ::initialize()
{
    Constraint::initialize();
    aConstant = 0.0;
}

std::string ConstraintIJ::constraintSpec()
{
    return "ConstraintIJ";
}
