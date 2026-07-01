/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "KinematicDotIeJe.h"
#include "EndFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<KinematicDotIeJe> KinematicDotIeJe::With()
{
    auto inst = std::make_shared<KinematicDotIeJe>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicDotIeJe> KinematicDotIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    auto inst = std::make_shared<KinematicDotIeJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

void KinematicDotIeJe::simUpdateAll()
{
    //Do nothing.
}

void MbD::KinematicDotIeJe::postStaticIteration()
{
    //Do nothing.
}

bool KinematicDotIeJe::isKineIJ()
{
    return false;
}

bool KinematicDotIeJe::isKinedotIJ()
{
    return true;
}

FRowDsptr KinematicDotIeJe::pvaluepXdot(SpatialContainerFrame* partFrame)
{
    if (partFrame == prtFrmI)
    {
        return pvaluepXdotI();
    }
    else if (partFrame == prtFrmJ)
    {
        return pvaluepXdotJ();
    }
    return FRowDsptr();
}

FRowDsptr KinematicDotIeJe::pvaluepEdot(SpatialContainerFrame* partFrame)
{
    if (partFrame == prtFrmI)
    {
        return pvaluepEdotI();
    }
    else if (partFrame == prtFrmJ)
    {
        return pvaluepEdotJ();
    }
    return FRowDsptr();
}

FRowDsptr KinematicDotIeJe::pvaluepEdotI()
{
    return FRowDsptr();
}

FRowDsptr KinematicDotIeJe::pvaluepEdotJ()
{
    return FRowDsptr();
}

FRowDsptr KinematicDotIeJe::pvaluepEdotK()
{
    return FullRow<double>::With(0);
}

FRowDsptr KinematicDotIeJe::pvaluepXdotI()
{
    return FRowDsptr();
}

FRowDsptr KinematicDotIeJe::pvaluepXdotJ()
{
    return FRowDsptr();
}
