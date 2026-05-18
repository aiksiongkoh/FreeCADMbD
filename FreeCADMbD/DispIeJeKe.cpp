/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispIeJeKe.h"
#include "EndFrame.h"
#include "EndFramet.h"
#include "EndFrameqt.h"
#include "DispIeqJeKeq.h"
#include "DispIeqJeqKeq.h"
#include "DispIeJeqKe.h"
#include "DispIetJeqKet.h"
#include "SimulationStoppingError.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<DispIeJeKe> DispIeJeKe::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
    const auto factoryName = "DispIeJeKe::With";
    std::shared_ptr<DispIeJeKe> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameq>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            assert(frmk->has_qX());
            inst = std::make_shared<DispIeqJeqKeq>(frmi, frmj, frmk);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            assert(frmk->has_qX());
            inst = std::make_shared<DispIeqJeKeq>(frmi, frmj, frmk);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            assert(!frmk->has_qX());
            inst = std::make_shared<DispIetJeqKet>(frmi, frmj, frmk);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrame>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            assert(!frmk->has_qX());
            inst = std::make_shared<DispIeJeqKe>(frmi, frmj, frmk);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
    }
    assert(inst);
    inst->initialize();
    return inst;
}

void DispIeJeKe::initialize()
{
    dispIeJeO = DispIeJeO::With(geteFrmI(), geteFrmJ());
    dispIeJeO->owner = this;
}

void DispIeJeKe::initializeGlobally()
{
    //Do nothing.
}

void DispIeJeKe::simUpdateAll()
{
    calcVector();
}

void DispIeJeKe::calcVector()
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

FColDsptr DispIeJeKe::getVector()
{
    return rIeJeKe;
}

FMatDsptr DispIeJeKe::getpVectorpXI()
{
    return FMatDsptr();
}

FMatDsptr DispIeJeKe::getpVectorpEI()
{
    return FMatDsptr();
}

FMatDsptr DispIeJeKe::getpVectorpXJ()
{
    return FMatDsptr();
}

FMatDsptr DispIeJeKe::getpVectorpEJ()
{
    return FMatDsptr();
}

FMatDsptr DispIeJeKe::getppCompipEIpEI(size_t axis)
{
    return FMatDsptr();
}

FMatDsptr DispIeJeKe::getppCompipEJpEJ(size_t axis)
{
    return FMatDsptr();
}

FColDsptr DispIeJeKe::getpVectorpt()
{
    return FColDsptr();
}

FColDsptr DispIeJeKe::getppVectorptpt()
{
    return FColDsptr();
}

bool DispIeJeKe::hasSameEndFrms(const std::shared_ptr<KinematicVectorIeJe> other) const
{
    auto disp = std::dynamic_pointer_cast<DispIeJeKe>(other);
    if (disp) {
        return eFrmI == disp->eFrmI && eFrmJ == disp->eFrmJ && eFrmK == disp->eFrmK;
    }
    return false;
}

void DispIeJeKe::useUniqueDispIeJeO()
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
