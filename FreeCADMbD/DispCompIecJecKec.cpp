/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIecJecKec.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<DispCompIecJecKec> DispCompIecJecKec::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    assert(!frmi->has_qX());
    assert(!frmj->has_qX());
    assert(!frmk->has_qX());
    auto inst = std::make_shared<DispCompIecJecKec>(frmi, frmj, frmk, axisk);
    inst->initialize();
    return inst;
}

void DispCompIecJecKec::withFrmIFrmJFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis)
{
    eFrmI = frmi;
    eFrmJ = frmj;
    efrmK = frmk;
    axisK = axis;
}

void DispCompIecJecKec::initializeLocally()
{
    KinematicIJ::initializeLocally();
    prtFrmK = efrmK->getPartFrame();
}

void DispCompIecJecKec::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    //rIeJeKe = aAKeO * rIeJeO
    //riIeJeKe = aArowiKeO dot rIeJeO = aAcoljOKe dot rIeJeO
    throw SimulationStoppingError("To be implemented.");
}

SpatialContainerFrame* DispCompIecJecKec::partFrameK()
{
    return prtFrmK;
}

double DispCompIecJecKec::value()
{
    return riIeJeKe;
}
