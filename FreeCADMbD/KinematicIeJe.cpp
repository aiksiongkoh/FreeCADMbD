/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "KinematicIeJe.h"
#include "EndFrame.h"
#include "SpatialContainerFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<KinematicIeJe> KinematicIeJe::With()
{
    auto inst = std::make_shared<KinematicIeJe>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIeJe> KinematicIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<KinematicIeJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

bool KinematicIeJe::isKineIJ()
{
    return true;
}

void KinematicIeJe::calcpvaluepXI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcpvaluepEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXIpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcpvaluepXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcpvaluepEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXJpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcpvaluepEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEKpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcpvaluept()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvalueptpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcvalue()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepXJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEKpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIeJe::pvaluepX(SpatialContainerFrame* partFrame)
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

FRowDsptr KinematicIeJe::pvaluepE(SpatialContainerFrame* partFrame)
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

FRowDsptr KinematicIeJe::pvaluepXI()
{
    return FRowDsptr();
}

FRowDsptr KinematicIeJe::pvaluepEI()
{
    return FRowDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepXIpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepXIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepEIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIeJe::pvaluepXJ()
{
    return FRowDsptr();
}

FRowDsptr KinematicIeJe::pvaluepEJ()
{
    return FRowDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepXIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepXIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepEIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepEIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepXJpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepXJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepEJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIeJe::pvaluepEK()
{
    return FRowDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepXIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepEIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepXJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepEJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::ppvaluepEKpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::puIeJeOpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::puIeJeOpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::puIeJeOpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicIeJe::puIeJeOpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

double KinematicIeJe::pvaluept()
{
    throw SimulationStoppingError("To be implemented.");
}

double KinematicIeJe::ppvalueptpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIeJe::ppvaluepXIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIeJe::ppvaluepEIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIeJe::ppvaluepXJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIeJe::ppvaluepEJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIeJe::ppvaluepEKpt()
{
    throw SimulationStoppingError("To be implemented.");
}

double KinematicIeJe::value()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::initializeLocally()
{
    prtFrmI = eFrmI->getPartFrame();
    prtFrmJ = eFrmJ->getPartFrame();
    has_qI = eFrmI->has_qX();
    has_qJ = eFrmJ->has_qX();
}

void KinematicIeJe::initializeGlobally()
{
}

SpatialContainerFrame* KinematicIeJe::partFrameI()
{
    return prtFrmI;
}

SpatialContainerFrame* KinematicIeJe::partFrameJ()
{
    return prtFrmJ;
}
