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
#include "DispIeqtJeqO.h"

using namespace MbD;

std::shared_ptr<DispIeJeO> DispIeJeO::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    std::shared_ptr<DispIeJeO> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DispIeqtJeqO>(frmi, frmj);
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
    calcVector();
}

void MbD::DispIeJeO::calcVector()
{
    //rIeJeO = rOJeO - rOIeO
    rIeJeO = eFrmJ->rOeO->minusFullColumn(eFrmI->rOeO);
}

FColDsptr MbD::DispIeJeO::getVector()
{
    return rIeJeO;
}

FMatDsptr MbD::DispIeJeO::getpVectorpXI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getpVectorpEI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getpVectorpXJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getpVectorpEJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getppCompipEIpEI(size_t axis)
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeO::getppCompipEJpEJ(size_t axis)
{
    return FMatDsptr();
}

FColDsptr MbD::DispIeJeO::getpVectorpt()
{
    return FColDsptr();
}

FMatDsptr MbD::DispIeJeO::getppVectorpEIpt()
{
    return FMatDsptr();
}

FColDsptr MbD::DispIeJeO::getppVectorptpt()
{
    return FColDsptr();
}

bool MbD::DispIeJeO::hasSameEndFrms(const std::shared_ptr<KinematicVectorIeJe> other) const
{
    auto disp = std::dynamic_pointer_cast<DispIeJeO>(other);
    if (disp) {
        return eFrmI == disp->eFrmI && eFrmJ == disp->eFrmJ;
    }
    return false;
}
