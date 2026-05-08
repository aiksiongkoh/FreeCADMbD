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

