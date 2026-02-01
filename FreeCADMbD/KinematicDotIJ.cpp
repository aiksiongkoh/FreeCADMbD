/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "KinematicDotIJ.h"
#include "EndFramec.h"
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

void KinematicDotIJ::calcPostDynCorrectorIteration()
{
    //Do nothing.
}

bool KinematicDotIJ::isKineIJ()
{
    return false;
}

bool KinematicDotIJ::isKinedotIJ()
{
    return true;
}

FRowDsptr KinematicDotIJ::pvaluepXdot(SpatialContainerFrame* partFrame)
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

FRowDsptr KinematicDotIJ::pvaluepEdot(SpatialContainerFrame* partFrame)
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

FRowDsptr KinematicDotIJ::pvaluepEdotI()
{
    return FRowDsptr();
}

FRowDsptr KinematicDotIJ::pvaluepEdotJ()
{
    return FRowDsptr();
}

FRowDsptr KinematicDotIJ::pvaluepEdotK()
{
    return FullRow<double>::With(0);
}

FRowDsptr KinematicDotIJ::pvaluepXdotI()
{
    return FRowDsptr();
}

FRowDsptr KinematicDotIJ::pvaluepXdotJ()
{
    return FRowDsptr();
}

FRowDsptr KinematicDotIJ::pvaluepXdotK()
{
    return FullRow<double>::With(0);
}
