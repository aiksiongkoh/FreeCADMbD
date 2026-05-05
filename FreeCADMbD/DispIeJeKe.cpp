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
#include "DispIeqJeKeq.h"
#include "DispIeqJeqKeq.h"
#include "DispIeJeqKe.h"
#include "DispIetJeqKet.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<DispIeJeKe> DispIeJeKe::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
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
            assert(frmk->has_qX());
            inst = std::make_shared<DispIeqJeqKeq>(frmi, frmj, frmk);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            assert(frmk->has_qX());
            inst = std::make_shared<DispIeqJeKeq>(frmi, frmj, frmk);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            assert(!frmk->has_qX());
            inst = std::make_shared<DispIetJeqKet>(frmi, frmj, frmk);
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
            assert(!frmk->has_qX());
            inst = std::make_shared<DispIeJeqKe>(frmi, frmj, frmk);
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

    aAOKe = eFrmK->aAOe;
    rIeJeO = dispIeJeO->rIeJeO;
    rIeJeKe = aAOKe->transposeTimesFullColumn(rIeJeO);
}

FColDsptr MbD::DispIeJeKe::getVector()
{
    return rIeJeKe;
}

FMatDsptr MbD::DispIeJeKe::getpVectorpXI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getpVectorpEI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getpVectorpXJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getpVectorpEJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getppCompipEIpEI(size_t axis)
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getppCompipEJpEJ(size_t axis)
{
    return FMatDsptr();
}

FColDsptr MbD::DispIeJeKe::getpVectorpt()
{
    return FColDsptr();
}

FColDsptr MbD::DispIeJeKe::getppVectorptpt()
{
    return FColDsptr();
}

bool MbD::DispIeJeKe::hasSameEndFrms(const std::shared_ptr<KinematicVectorIeJe> other) const
{
    auto disp = std::dynamic_pointer_cast<DispIeJeKe>(other);
    if (disp) {
        return eFrmI == disp->eFrmI && eFrmJ == disp->eFrmJ && eFrmK == disp->eFrmK;
    }
    return false;
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
