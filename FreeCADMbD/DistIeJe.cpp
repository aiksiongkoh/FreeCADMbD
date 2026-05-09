/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistIeJe.h"
#include "EndFrameqt.h"
#include "EndFrameq.h"
#include "EndFramet.h"
#include "EndFrame.h"
#include "SimulationStoppingError.h"
#include "DistIeqtJeq.h"
#include "DistIeqJeq.h"
#include "DistIeJeq.h"
#include "DistIetJeq.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<DistIeJe> DistIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    std::shared_ptr<DistIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DistIeqtJeq>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameq>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DistIeqJeq>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = std::make_shared<DistIeqJe>(frmi, frmj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DistIetJeq>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    else if (std::dynamic_pointer_cast<EndFrame>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DistIeJeq>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    assert(inst);
    inst->initialize();
    return inst;
}

void MbD::DistIeJe::initialize()
{
    dispIeJeO = DispIeJeO::With(eFrmI, eFrmJ);
    dispIeJeO->owner = this;
}

void MbD::DistIeJe::useUniqueDispIeJeO()
{
    auto dispIeJeOs = root()->dispIeJeOs;
    auto it = std::find_if(dispIeJeOs->begin(), dispIeJeOs->end(), [&](auto disp) {return disp->hasSameEndFrms(dispIeJeO); });
    if (it == dispIeJeOs->end()) {
        dispIeJeOs->push_back(dispIeJeO);
    }
    else {
        dispIeJeO = *it;
    }
}

void MbD::DistIeJe::useUniqueDispIeJeKe()
{
}

void DistIeJe::simUpdateAll()
{
    rIeJeO = dispIeJeO->rIeJeO;
    rIeJe = rIeJeO->length();
    calcPrivate();
}

void DistIeJe::calcPrivate()
{
    if (rIeJe == 0.0) return;
    uIeJeO = rIeJeO->times(1.0 / rIeJe);
    muIeJeO = uIeJeO->negated();
}

double DistIeJe::value()
{
    return rIeJe;
}

FMatDsptr MbD::DistIeJe::puIeJeOpX(SpatialContainerFrame *partFrame)
{
{
    if (prtFrmI == partFrame) {
        return puIeJeOpXI();
    }
    else if (prtFrmJ == partFrame) {
        return puIeJeOpXJ();
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}
}

FMatDsptr MbD::DistIeJe::puIeJeOpE(SpatialContainerFrame *partFrame)
{
    if (prtFrmI == partFrame) {
        return puIeJeOpEI();
    }
    else if (prtFrmJ == partFrame) {
        return puIeJeOpEJ();
    }
    else {
        throw SimulationStoppingError("To be implemented.");
    }
}

FMatDsptr DistIeJe::puIeJeOpEI()
{
    return FMatDsptr();
}

FMatDsptr DistIeJe::puIeJeOpXI()
{
    return FMatDsptr();
}

FRowDsptr DistIeJe::pvaluepEI()
{
    return FRowDsptr();
}

FRowDsptr DistIeJe::pvaluepXI()
{
    return FRowDsptr();
}

