/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistIecJec.h"
#include "EndFrameqt.h"
#include "EndFrameq.h"
#include "EndFramet.h"
#include "EndFrame.h"
#include "SimulationStoppingError.h"
#include "DistIeqctJeqc.h"
#include "DistIeqcJeqc.h"
#include "DistIecJeqc.h"

using namespace MbD;

std::shared_ptr<DistIecJec> DistIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    std::shared_ptr<DistIecJec> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DistIeqctJeqc>(frmi, frmj);
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
            inst = std::make_shared<DistIeqcJeqc>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = std::make_shared<DistIeqcJec>(frmi, frmj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
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
            inst = std::make_shared<DistIecJeqc>(frmi, frmj);
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

void DistIecJec::simUpdateAll()
{
    //rIeJe = rIeJeO->length();
    rIeJeO = eFrmJ->rOeO->minusFullColumn(eFrmI->rOeO);
    rIeJe = rIeJeO->length();
    calcPrivate();
}

void DistIecJec::calcPrivate()
{
    if (rIeJe == 0.0) return;
    uIeJeO = rIeJeO->times(1.0 / rIeJe);
    muIeJeO = uIeJeO->negated();
}

double DistIecJec::value()
{
    return rIeJe;
}

FColDsptr DistIecJec::rIeJeIe()
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr DistIecJec::puIeJeOpX(SpatialContainerFrame* partFrame)
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

FMatDsptr DistIecJec::puIeJeOpE(SpatialContainerFrame* partFrame)
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

FMatDsptr DistIecJec::puIeJeOpEI()
{
    return FMatDsptr();
}

FMatDsptr DistIecJec::puIeJeOpXI()
{
    return FMatDsptr();
}

FRowDsptr DistIecJec::pvaluepEI()
{
    return FRowDsptr();
}

FRowDsptr DistIecJec::pvaluepXI()
{
    return FRowDsptr();
}
