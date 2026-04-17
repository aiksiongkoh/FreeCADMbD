/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeJeKe.h"
#include "EndFramec.h"
#include "EndFramect.h"
#include "EndFrameqct.h"
#include "DispIeqJeqKe.h"
#include "DispIeJeqKe.h"
#include "DispIetJeqKet.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<DispIeJeKe> DispIeJeKe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    std::shared_ptr<DispIeJeKe> inst;
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
            inst = std::make_shared<DispIeqJeqKe>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<DispIeqJeKe>(frmi, frmj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DispIetJeqKet>(frmi, frmj);
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
            inst = std::make_shared<DispIeJeqKe>(frmi, frmj);
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

void MbD::DispIeJeKe::initialize()
{
    dispIeJeO = DispIeJeO::With(geteFrmI(), geteFrmJ());
}

void MbD::DispIeJeKe::initializeGlobally()
{
    //Do nothing.
}

void DispIeJeKe::simUpdateAll()
{
    calcVector();
}

void MbD::DispIeJeKe::calcVector()
{
    //rIeJeO = rOJeO - rOIeO
    //rIeJeKe = aAKeO * rIeJeO
    //prIeJeKepXI = aAOKeT * prIeJeOpXI
    //prIeJeKepEI = aAOKeT * prIeJeOpEI
    //prIeJeKepXJ = aAOKeT * prIeJeOpXJ
    //prIeJeKepEJ = aAOKeT * prIeJeOpEJ
    //prIeJeKepEK = pAOKeTpEK * rIeJeO
    //pprIeJeKepXIpEK = pAOKeTpEK * prIeJeOpXI
    //pprIeJeKepEIpEI = aAOKeT * pprIeJeOpEIpEI
    //pprIeJeKepEIpEK = pAOKeTpEK * prIeJeOpEI
    //pprIeJeKepXJpEK = pAOKeTpEK * prIeJeOpXJ
    //pprIeJeKepEJpEK = pAOKeTpEK * prIeJeOpEJ
    //pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO

    aAOKe = frmKe->aAOe;
    rIeJeO = dispIeJeO->rIeJeO;
    rIeJeKe = aAOKe->transposeTimesFullColumn(rIeJeO);
}

FMatDsptr MbD::DispIeJeKe::getprIeJeKepXI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getprIeJeKepEI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getprIeJeKepXJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getprIeJeKepEJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getppriIeJeKepEIpEI(size_t axis)
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getppriIeJeKepEJpEJ(size_t axis)
{
    return FMatDsptr();
}

FColDsptr MbD::DispIeJeKe::getprIeJeKept()
{
    return FColDsptr();
}

FColDsptr MbD::DispIeJeKe::getpprIeJeKeptpt()
{
    return FColDsptr();
}

bool MbD::DispIeJeKe::hasSameEndFrms(const std::shared_ptr<DispIeJeKe> other) const
{
    auto sameClass = typeid(*this).name() == typeid(*other).name();
    return sameClass && frmIe == other->frmIe && frmJe == other->frmJe && frmKe == other->frmKe;
}

void MbD::DispIeJeKe::useUniqueDispIeJeO()
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
