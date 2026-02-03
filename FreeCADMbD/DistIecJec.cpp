/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistIecJec.h"
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"
#include "SimulationStoppingError.h"
#include "DistIeqctJeqc.h"
#include "DistIeqcJeqc.h"
#include "DistIecJeqc.h"

using namespace MbD;

std::shared_ptr<DistIecJec> DistIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    std::shared_ptr<DistIecJec> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DistIeqctJeqc>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameqc>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DistIeqcJeqc>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<DistIeqcJec>(frmi, frmj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
    }
    else if (std::dynamic_pointer_cast<EndFramec>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DistIecJeqc>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
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
    rIeJeO = getrIeJeO();
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

FMatDsptr MbD::DistIecJec::puIeJeOpX(SpatialContainerFrame* partFrame)
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

FMatDsptr MbD::DistIecJec::puIeJeOpE(SpatialContainerFrame* partFrame)
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

FMatDsptr MbD::DistIecJec::puIeJeOpEI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DistIecJec::puIeJeOpXI()
{
    return FMatDsptr();
}

FRowDsptr MbD::DistIecJec::pvaluepEI()
{
    return FRowDsptr();
}

FRowDsptr MbD::DistIecJec::pvaluepXI()
{
    return FRowDsptr();
}
