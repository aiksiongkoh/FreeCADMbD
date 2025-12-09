/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "KinematicDotIJ.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<KinematicDotIJ> KinematicDotIJ::With()
{
    auto inst = std::make_shared<KinematicDotIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicDotIJ> KinematicDotIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<KinematicDotIJ>(frmi, frmj);
    inst->initialize();
    return inst;
}

bool KinematicDotIJ::isKineIJ()
{
    return false;
}

bool KinematicDotIJ::isKinedotIJ()
{
    return true;
}

FRowDsptr KinematicDotIJ::pvaluepEdotI()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicDotIJ::pvaluepEdotJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicDotIJ::pvaluepEdotK()
{
    return FullRow<double>::With(0);
}

FRowDsptr KinematicDotIJ::pvaluepXdotI()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicDotIJ::pvaluepXdotJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicDotIJ::pvaluepXdotK()
{
    return FullRow<double>::With(0);
}
