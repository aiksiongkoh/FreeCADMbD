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

void DispIeJeKe::simUpdateAll()
{
    //rIeJeO = rOJeO - rOIeO
    rIeJeO = getrIeJeO();
}

void MbD::DispIeJeKe::calcvalue()
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

void MbD::DispIeJeKe::calcpvaluepXI()
{
    assert(!prIeJeKepXI);
}

void MbD::DispIeJeKe::calcpvaluepEI()
{
    assert(!prIeJeKepEI);
}

void MbD::DispIeJeKe::calcpvaluepXJ()
{
    assert(!prIeJeKepXJ);
}

void MbD::DispIeJeKe::calcpvaluepEJ()
{
    assert(!prIeJeKepEJ);
}

void MbD::DispIeJeKe::calcpvaluepXK()
{
    assert(!prIeJeKepXK);
}

void MbD::DispIeJeKe::calcpvaluepEK()
{
    assert(!prIeJeKepEK);
}

void MbD::DispIeJeKe::calcppvaluepXIpXI()
{
    assert(!pprIeJeKepXIpXI);
}

void MbD::DispIeJeKe::calcppvaluepXIpEI()
{
    assert(!pprIeJeKepXIpEI);
}

void MbD::DispIeJeKe::calcppvaluepXIpXJ()
{
    assert(!pprIeJeKepXIpXJ);
}

void MbD::DispIeJeKe::calcppvaluepXIpEJ()
{
    assert(!pprIeJeKepXIpEJ);
}

void MbD::DispIeJeKe::calcppvaluepXIpEK()
{
    assert(!pprIeJeKepXIpEK);
}

void MbD::DispIeJeKe::calcppvaluepEIpEI()
{
    assert(!pprIeJeKepEIpEI);
}

void MbD::DispIeJeKe::calcppvaluepEIpXJ()
{
    assert(!pprIeJeKepEIpXJ);
}

void MbD::DispIeJeKe::calcppvaluepEIpEJ()
{
    assert(!pprIeJeKepEIpEJ);
}

void MbD::DispIeJeKe::calcppvaluepEIpEK()
{
    assert(!pprIeJeKepEIpEK);
}

void MbD::DispIeJeKe::calcppvaluepXJpXJ()
{
    assert(!pprIeJeKepXJpXJ);
}

void MbD::DispIeJeKe::calcppvaluepXJpEJ()
{
    assert(!pprIeJeKepXJpEJ);
}

void MbD::DispIeJeKe::calcppvaluepXJpEK()
{
    assert(!pprIeJeKepXJpEK);
}

void MbD::DispIeJeKe::calcppvaluepEJpEJ()
{
    assert(!pprIeJeKepEJpEJ);
}

void MbD::DispIeJeKe::calcppvaluepEJpEK()
{
    assert(!pprIeJeKepEJpEK);
}

void MbD::DispIeJeKe::calcppvaluepEKpEK()
{
    assert(!pprIeJeKepEKpEK);
}

FMatDsptr MbD::DispIeJeKe::getprIeJeOpXI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getprIeJeOpEI()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getprIeJeOpXJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getprIeJeOpEJ()
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getppriIeJeOpEIpEI(size_t axis)
{
    return FMatDsptr();
}

FMatDsptr MbD::DispIeJeKe::getppriIeJeOpEJpEJ(size_t axis)
{
    return FMatDsptr();
}

FColDsptr MbD::DispIeJeKe::getprIeJeOpt()
{
    return FColDsptr();
}

FColDsptr MbD::DispIeJeKe::getpprIeJeOptpt()
{
    return FColDsptr();
}

bool MbD::DispIeJeKe::hasSameEndFrms(const std::shared_ptr<DispIeJeKe> other) const
{
    return frmIe == other->frmIe && frmJe == other->frmJe && frmKe == other->frmKe;
}
