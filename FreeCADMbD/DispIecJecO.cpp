/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIecJecO.h"
#include "EndFramec.h"
#include "EndFramect.h"
#include "EndFrameqct.h"
#include "DispIeqcJeqcO.h"
#include "DispIecJeqcO.h"
#include "DispIectJeqcO.h"

using namespace MbD;

std::shared_ptr<DispIecJecO> DispIecJecO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    std::shared_ptr<DispIecJecO> inst;
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
            inst = std::make_shared<DispIeqcJeqcO>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<DispIeqcJecO>(frmi, frmj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DispIectJeqcO>(frmi, frmj);
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
            inst = std::make_shared<DispIecJeqcO>(frmi, frmj);
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

void DispIecJecO::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    rIeJeO = getrIeJeO();
}

FMatDsptr MbD::DispIecJecO::getprIeJeOpXI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIecJecO::getprIeJeOpEI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIecJecO::getprIeJeOpXJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIecJecO::getprIeJeOpEJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIecJecO::getppriIeJeOpEIpEI(size_t axis)
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIecJecO::getppriIeJeOpEJpEJ(size_t axis)
{
    return FMatDsptr();
}

FColDsptr MbD::DispIecJecO::getprIeJeOpt()
{
    return FColDsptr();
}

FColDsptr MbD::DispIecJecO::getpprIeJeOptpt()
{
    return FColDsptr();
}

bool MbD::DispIecJecO::hasSameEndFrms(const std::shared_ptr<DispIecJecO> other) const
{
    return eFrmI == other->eFrmI && eFrmJ == other->eFrmJ;
}
