/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeJeO.h"
#include "EndFrame.h"
#include "EndFramet.h"
#include "EndFrameqt.h"
#include "DispIeqJeqO.h"
#include "DispIeJeqO.h"
#include "DispIetJeqO.h"
#include "DispIeqtJeqO.h"

using namespace MbD;

std::shared_ptr<DispIeJeO> DispIeJeO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    std::shared_ptr<DispIeJeO> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DispIeqtJeqO>(frmi, frmj);
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
            inst = std::make_shared<DispIeqJeqO>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = std::make_shared<DispIeqJeO>(frmi, frmj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DispIetJeqO>(frmi, frmj);
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
            inst = std::make_shared<DispIeJeqO>(frmi, frmj);
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

void DispIeJeO::simUpdateAll()
{
    calcVector();
}

void DispIeJeO::calcVector()
{
    //rIeJeO = rOJeO - rOIeO
    rIeJeO = eFrmJ->rOeO->minusFullColumn(eFrmI->rOeO);
}

FColDsptr DispIeJeO::getVector()
{
    return rIeJeO;
}

FMatDsptr DispIeJeO::getpVectorpXI()
{
    return FMatDsptr();
}

FMatDsptr DispIeJeO::getpVectorpEI()
{
    return FMatDsptr();
}

FMatDsptr DispIeJeO::getpVectorpXJ()
{
    return FMatDsptr();
}

FMatDsptr DispIeJeO::getpVectorpEJ()
{
    return FMatDsptr();
}

FMatDsptr DispIeJeO::getppCompipEIpEI(size_t axis)
{
    return FMatDsptr();
}

FMatDsptr DispIeJeO::getppCompipEJpEJ(size_t axis)
{
    return FMatDsptr();
}

FColDsptr DispIeJeO::getpVectorpt()
{
    return FColDsptr();
}

FMatDsptr DispIeJeO::getppVectorpEIpt()
{
    return FMatDsptr();
}

FColDsptr DispIeJeO::getppVectorptpt()
{
    return FColDsptr();
}

bool DispIeJeO::hasSameEndFrms(const std::shared_ptr<KinematicVectorIeJe> other) const
{
    auto disp = std::dynamic_pointer_cast<DispIeJeO>(other);
    if (disp) {
        return eFrmI == disp->eFrmI && eFrmJ == disp->eFrmJ;
    }
    return false;
}
