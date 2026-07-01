/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "KinematicVectorIeJe.h"
#include "EndFrame.h"
#include "SpatialContainerFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<KinematicVectorIeJe> KinematicVectorIeJe::With()
{
    auto inst = std::make_shared<KinematicVectorIeJe>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicVectorIeJe> KinematicVectorIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<KinematicVectorIeJe>(frmi, frmj);
    inst->initialize();
    return inst;
}

bool KinematicVectorIeJe::isKineIJ()
{
    return true;
}

void KinematicVectorIeJe::calcpVectorpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcpVectorpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXIpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcpVectorpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcpVectorpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXJpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcpVectorpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEKpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcpVectorpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorptpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcVector()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpXJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicVectorIeJe::calcppVectorpEKpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr KinematicVectorIeJe::getVector()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getpVectorpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getpVectorpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpXIpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpXIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpEIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getpVectorpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getpVectorpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpXIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpXIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpEIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpEIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpXJpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpXJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpEJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getpVectorpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpXIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpEIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpXJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpEJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatFColDsptr KinematicVectorIeJe::getppVectorpEKpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::puIeJeOpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::puIeJeOpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::puIeJeOpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::puIeJeOpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr KinematicVectorIeJe::getpVectorpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr KinematicVectorIeJe::getppVectorptpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getppVectorpXIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getppVectorpEIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getppVectorpXJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getppVectorpEJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getppVectorpEKpt()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getppCompipEIpEI(size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr KinematicVectorIeJe::getppCompipEJpEJ(size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}

double KinematicVectorIeJe::value()
{
    throw SimulationStoppingError("To be implemented.");
}

bool KinematicVectorIeJe::hasSameEndFrms(const std::shared_ptr<KinematicVectorIeJe> other) const
{
    return false;
}

void KinematicVectorIeJe::initializeLocally()
{
}

void KinematicVectorIeJe::initializeGlobally()
{
}
