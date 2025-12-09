/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "KinematicIJ.h"
#include "EndFramec.h"
#include "PartFrame.h"
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

void KinematicIJ::calc_pvaluepXI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_pvaluepEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXIpXI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEIpEI()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_pvaluepXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_pvaluepEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEIpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEIpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXJpXJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEJpEJ()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_pvaluepXK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_pvaluepEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEIpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEJpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEKpEK()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_pvaluept()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvalueptpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_value()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEIpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEJpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepXKpt()
{
    throw SimulationStoppingError("To be implemented.");
}

void KinematicIJ::calc_ppvaluepEKpt()
{
    throw SimulationStoppingError("To be implemented.");
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

PartFrame* KinematicIJ::partFrameI()
{
    return eFrmI->getPartFrame();
}

PartFrame* KinematicIJ::partFrameJ()
{
    return eFrmJ->getPartFrame();
}
