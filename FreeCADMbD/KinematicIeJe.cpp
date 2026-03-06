/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "KinematicIeJe.h"
#include "EndFramec.h"
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

void KinematicIeJe::calcpvaluepXK()
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

void KinematicIeJe::calcppvaluepXKpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::calcppvaluepEKpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FRowDsptr KinematicIeJe::pvaluepX(SpatialContainerFrame* partFrame)
{
    if (partFrame == frmIp)
    {
        return pvaluepXI();
    }
    else if (partFrame == frmJp)
    {
        return pvaluepXJ();
    }
    return FRowDsptr();
}

FRowDsptr KinematicIeJe::pvaluepE(SpatialContainerFrame* partFrame)
{
    if (partFrame == frmIp)
    {
        return pvaluepEI();
    }
    else if (partFrame == frmJp)
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
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepXIpEI()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepEIpEI()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
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
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepXIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepEIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepEIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepXJpXJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepXJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepEJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FRowDsptr KinematicIeJe::pvaluepXK()
{
    return FRowDsptr();
}

FRowDsptr KinematicIeJe::pvaluepEK()
{
    return FRowDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepXIpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepEIpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepXJpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepEJpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::ppvaluepEKpEK()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::puIeJeOpEI()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::puIeJeOpXI()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::puIeJeOpEJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr KinematicIeJe::puIeJeOpXJ()
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

double KinematicIeJe::pvaluept()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

double KinematicIeJe::ppvalueptpt()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

FRowDsptr KinematicIeJe::ppvaluepXIpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIeJe::ppvaluepEIpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIeJe::ppvaluepXJpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIeJe::ppvaluepEJpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIeJe::ppvaluepXKpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

FRowDsptr KinematicIeJe::ppvaluepEKpt()
{
    throw SimulationStoppingError("To be implemented.");
    return FRowDsptr();
}

double KinematicIeJe::value()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}

void KinematicIeJe::withFrmIFrmJ(EndFrmsptr eFrmi, EndFrmsptr eFrmj)
{
    frmIe = eFrmi;
    frmJe = eFrmj;
}

void KinematicIeJe::withFrmIFrmJaxis(EndFrmsptr eFrmI, EndFrmsptr eFrmJ, size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::withFrmIFrmJfrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIeJe::withFrmIFrmJFrmKaxis(EndFrmsptr eFrmi, EndFrmsptr eFrmj, EndFrmsptr eFrmk, size_t axis)
{
}

void KinematicIeJe::initializeLocally()
{
    frmIp = frmIe->getPartFrame();
    frmJp = frmJe->getPartFrame();
    has_qI = frmIe->has_qX();
    has_qJ = frmJe->has_qX();
}

void KinematicIeJe::initializeGlobally()
{
}

SpatialContainerFrame* KinematicIeJe::partFrameI()
{
    return frmIp;
}

SpatialContainerFrame* KinematicIeJe::partFrameJ()
{
    return frmJp;
}

FColDsptr MbD::KinematicIeJe::getrIeJeO()
{
    return frmJe->rOeO->minusFullColumn(frmIe->rOeO);
}
