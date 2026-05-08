/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "KinematicIJ.h"
#include "EndFrame.h"
#include "SpatialContainerFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<KinematicIJ> KinematicIJ::With()
{
    auto inst = std::make_shared<KinematicIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> KinematicIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<KinematicIJ>(frmi, frmj);
    inst->initialize();
    return inst;
}

bool KinematicIJ::isKineIJ()
{
    return true;
}

void KinematicIJ::calcpvaluepXI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcpvaluepEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXIpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcpvaluepXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcpvaluepEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXJpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcpvaluepXK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcpvaluepEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEKpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcpvaluept()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvalueptpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcvalue()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepXKpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calcppvaluepEKpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIJ::pvaluepX(SpatialContainerFrame* partFrame)
{
    if (partFrame == prtFrmI)
    {
        return pvaluepXI();
    }
    else if (partFrame == prtFrmJ)
    {
        return pvaluepXJ();
    }
    return FRowDsptr();
}

FRowDsptr KinematicIJ::pvaluepE(SpatialContainerFrame* partFrame)
{
    if (partFrame == prtFrmI)
    {
        return pvaluepEI();
    }
    else if (partFrame == prtFrmJ)
    {
        return pvaluepEJ();
    }
    return FRowDsptr();
}

FRowDsptr KinematicIJ::pvaluepXI()
{
    return FRowDsptr();
}

FRowDsptr KinematicIJ::pvaluepEI()
{
    return FRowDsptr();
}

FMatDsptr KinematicIJ::ppvaluepXIpXI()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepXIpEI()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepEIpEI()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FRowDsptr KinematicIJ::pvaluepXJ()
{
    return FRowDsptr();
}

FRowDsptr KinematicIJ::pvaluepEJ()
{
    return FRowDsptr();
}

FMatDsptr KinematicIJ::ppvaluepXIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepXIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepEIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepEIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepXJpXJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepXJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepEJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FRowDsptr KinematicIJ::pvaluepXK()
{
    return FRowDsptr();
}

FRowDsptr KinematicIJ::pvaluepEK()
{
    return FRowDsptr();
}

FMatDsptr KinematicIJ::ppvaluepXIpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepEIpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepXJpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepEJpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::ppvaluepEKpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::puIeJeOpEI()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::puIeJeOpXI()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::puIeJeOpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIJ::puIeJeOpXJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

double KinematicIJ::pvaluept()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

double KinematicIJ::ppvalueptpt()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

FRowDsptr KinematicIJ::ppvaluepXIpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIJ::ppvaluepEIpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIJ::ppvaluepXJpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIJ::ppvaluepEJpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIJ::ppvaluepXKpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIJ::ppvaluepEKpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

double KinematicIJ::value()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

void KinematicIJ::withFrmIFrmJ(EndFrmsptr eFrmi, EndFrmsptr eFrmj)
{
    eFrmI = eFrmi;
    eFrmJ = eFrmj;
}

void KinematicIJ::withFrmIFrmJaxis(EndFrmsptr eFrmI, EndFrmsptr eFrmJ, size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::withFrmIFrmJfrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::withFrmIFrmJFrmKaxis(EndFrmsptr eFrmi, EndFrmsptr eFrmj, EndFrmsptr eFrmk, size_t axis)
{
}

void KinematicIJ::initializeLocally()
{
    prtFrmI = eFrmI->getPartFrame();
    prtFrmJ = eFrmJ->getPartFrame();
    has_qI = eFrmI->has_qX();
    has_qJ = eFrmJ->has_qX();
}

void KinematicIJ::initializeGlobally()
{
}

SpatialContainerFrame* KinematicIJ::partFrameI()
{
    return prtFrmI;
}

SpatialContainerFrame* KinematicIJ::partFrameJ()
{
    return prtFrmJ;
}
