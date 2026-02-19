/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIeJe.h"
#include "DispCompIeqcJeqcO.h"
#include "EndFramect.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "AtPointConstraintIeqJeq.h"
#include "AtPointConstraintIetJeq.h"
#include "AtPointConstraintIeqtJeq.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIeJe> AtPointConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    std::shared_ptr<AtPointConstraintIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<AtPointConstraintIeqtJeq>(frmi, frmj, axisO);
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
            inst = std::make_shared<AtPointConstraintIeqJeq>(frmi, frmj, axisO);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = std::make_shared<AtPointConstraintIeqJe>(frmi, frmj, axisO);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = std::make_shared<AtPointConstraintIetJeq>(frmi, frmj, axisO);
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
            inst = std::make_shared<AtPointConstraintIeJeq>(frmi, frmj, axisO);
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

void MbD::AtPointConstraintIeJe::calcG()
{
    auto rIeJeO = dispIeJeO->rIeJeO;
    aG = rIeJeO->at(axis) - aConstant;
}

void MbD::AtPointConstraintIeJe::calcpGpXI()
{
    //pGpXI = [0];
    assert(!pGpXI);
}

void MbD::AtPointConstraintIeJe::calcpGpEI()
{
    //pGpEI = [0];
    assert(!pGpEI);
}

void MbD::AtPointConstraintIeJe::calcpGpXJ()
{
    //pGpXJ = [0];
    assert(!pGpXJ);
}

void MbD::AtPointConstraintIeJe::calcpGpEJ()
{
    //pGpEJ = [0];
    assert(!pGpEJ);
}

void MbD::AtPointConstraintIeJe::calcppGpXIpXI()
{
    //ppGpXIpXI = [0];
    assert(!ppGpXIpXI);
}

void MbD::AtPointConstraintIeJe::calcppGpXIpEI()
{
    //ppGpXIpEI = [0];
    assert(!ppGpXIpEI);
}

void MbD::AtPointConstraintIeJe::calcppGpXIpXJ()
{
    //ppGpXIpXJ = [0];
    assert(!ppGpXIpXJ);
}

void MbD::AtPointConstraintIeJe::calcppGpXIpEJ()
{
    //ppGpXIpEJ = [0];
    assert(!ppGpXIpEJ);
}

void MbD::AtPointConstraintIeJe::calcppGpEIpEI()
{
    //ppGpEIpEI = [0];
    assert(!ppGpEIpEI);
}

void MbD::AtPointConstraintIeJe::calcppGpEIpXJ()
{
    //ppGpEIpXJ = [0];
    assert(!ppGpEIpXJ);
}

void MbD::AtPointConstraintIeJe::calcppGpEIpEJ()
{
    //ppGpEIpEJ = [0];
    assert(!ppGpEIpEJ);
}

void MbD::AtPointConstraintIeJe::calcppGpXJpXJ()
{
    //ppGpXJpXJ = [0];
    assert(!ppGpXJpXJ);
}

void MbD::AtPointConstraintIeJe::calcppGpXJpEJ()
{
    //ppGpXJpEJ = [0];
    assert(!ppGpXJpEJ);
}

void MbD::AtPointConstraintIeJe::calcppGpEJpEJ()
{
    //ppGpEJpEJ = [0];
    assert(!ppGpEJpEJ);
}

ConstraintType MbD::AtPointConstraintIeJe::type()
{
    return displacement;
}

std::string MbD::AtPointConstraintIeJe::constraintSpec()
{
    return "AtPointConstraintIeJe";
}
