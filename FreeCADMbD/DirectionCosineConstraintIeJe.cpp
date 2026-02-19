/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineConstraintIeqJeq.h"
#include "DirectionCosineIeqcJeqc.h"
#include "EndFramect.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "DirectionCosineConstraintIeqtJeq.h"
#include "DirectionCosineConstraintIetJeq.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeJe> DirectionCosineConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    std::shared_ptr<DirectionCosineConstraintIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeqtJeq>(frmi, frmj, axisi, axisj);
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
            inst = std::make_shared<DirectionCosineConstraintIeqJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIeqJe>(frmi, frmj, axisi, axisj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<DirectionCosineConstraintIetJeq>(frmi, frmj, axisi, axisj);
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
            inst = std::make_shared<DirectionCosineConstraintIeJeq>(frmi, frmj, axisi, axisj);
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

void MbD::DirectionCosineConstraintIeJe::calcG()
{
    //aG = aAijIeJe - aConstant;
    aG = aAijIeJe->value() - aConstant;
}

void MbD::DirectionCosineConstraintIeJe::calcpGpXI()
{
    //pGpXI = [0];
    assert(!pGpXI);
}

void MbD::DirectionCosineConstraintIeJe::calcpGpEI()
{
    //pGpEI = [0];
    assert(!pGpEI);
}

void MbD::DirectionCosineConstraintIeJe::calcpGpXJ()
{
    //pGpXJ = [0];
    assert(!pGpXJ);
}

void MbD::DirectionCosineConstraintIeJe::calcpGpEJ()
{
    //pGpEJ = [0];
    assert(!pGpEJ);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpXIpXI()
{
    //ppGpXIpXI = [0];
    assert(!ppGpXIpXI);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpXIpEI()
{
    //ppGpXIpEI = [0];
    assert(!ppGpXIpEI);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpXIpXJ()
{
    //ppGpXIpXJ = [0];
    assert(!ppGpXIpXJ);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpXIpEJ()
{
    //ppGpXIpEJ = [0];
    assert(!ppGpXIpEJ);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpEIpEI()
{
    //ppGpEIpEI = [0];
    assert(!ppGpEIpEI);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpEIpXJ()
{
    //ppGpEIpXJ = [0];
    assert(!ppGpEIpXJ);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpEIpEJ()
{
    //ppGpEIpEJ = [0];
    assert(!ppGpEIpEJ);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpXJpXJ()
{
    //ppGpXJpXJ = [0];
    assert(!ppGpXJpXJ);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpXJpEJ()
{
    //ppGpXJpEJ = [0];
    assert(!ppGpXJpEJ);
}

void MbD::DirectionCosineConstraintIeJe::calcppGpEJpEJ()
{
    //ppGpEJpEJ = [0];
    assert(!ppGpEJpEJ);
}

void MbD::DirectionCosineConstraintIeJe::addToJointForceI(FColDsptr col)
{
    //aFIeO = lam * pGpXI
    //aFIeO = lam * zero
    //Do nothing.
    assert(!pGpXI);
}

void MbD::DirectionCosineConstraintIeJe::addToJointTorqueI(FColDsptr col)
{
    //aTIeO = 0.5 * aBOIp * (lam * pGpEI - prOIeOpEIT * aFIeO)
    //aFIeO = zero
    //aTIeO = 0.5 * aBOIp * lam * pGpEI
    auto aBOIp = frmIe->aBOp();
    auto lampGpEI = pGpEI->transpose()->times(lam);  //lam * pGpEI
    auto aTIeO = aBOIp->timesFullColumn(lampGpEI)->times(0.5);
    col->equalSelfPlus(aTIeO);
}

ConstraintType MbD::DirectionCosineConstraintIeJe::type()
{
    return perpendicular;
}

std::string MbD::DirectionCosineConstraintIeJe::constraintSpec()
{
    return "DirectionCosineConstraintIeJe";
}

void MbD::DirectionCosineConstraintIeJe::initialize()
{
    ConstraintIeJe::initialize();
    aAijIeJe = DirectionCosineIecJec::With(frmIe, frmJe, axisI, axisJ);
}
