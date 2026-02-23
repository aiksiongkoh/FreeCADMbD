/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeJeO.h"
#include "EndFramec.h"
#include "EndFramect.h"
#include "EndFrameqct.h"
#include "DispIeqJeqO.h"
#include "DispIeJeqO.h"
#include "DispIetJeqO.h"

using namespace MbD;

std::shared_ptr<DispIeJeO> DispIeJeO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    std::shared_ptr<DispIeJeO> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
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
    else if (std::dynamic_pointer_cast<EndFrameqc>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DispIeqJeqO>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<DispIeqJeO>(frmi, frmj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DispIetJeqO>(frmi, frmj);
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
            inst = std::make_shared<DispIeJeqO>(frmi, frmj);
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

void DispIeJeO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    rIeJeO = getrIeJeO();
}

FMatDsptr MbD::DispIeJeO::getprIeJeOpXI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getprIeJeOpEI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getprIeJeOpXJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getprIeJeOpEJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getppriIeJeOpEIpEI(size_t axis)
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getppriIeJeOpEJpEJ(size_t axis)
{
    return FMatDsptr();
}

FColDsptr MbD::DispIeJeO::getprIeJeOpt()
{
    return FColDsptr();
}

FMatDsptr MbD::DispIeJeO::getpprIeJeOpEIpt()
{
    return FMatDsptr();
}

FColDsptr MbD::DispIeJeO::getpprIeJeOptpt()
{
    return FColDsptr();
}

bool MbD::DispIeJeO::hasSameEndFrms(const std::shared_ptr<DispIeJeO> other) const
{
    return frmIe == other->frmIe && frmJe == other->frmJe;
}
