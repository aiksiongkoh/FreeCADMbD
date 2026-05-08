/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIeJe.h"
#include "EndFramet.h"
#include "EndFrameq.h"
#include "EndFrameqt.h"
#include "AtPointConstraintIeqJeq.h"
#include "AtPointConstraintIetJeq.h"
#include "AtPointConstraintIeqtJeq.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIeJe> AtPointConstraintIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    std::shared_ptr<AtPointConstraintIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<AtPointConstraintIeqtJeq>(frmi, frmj, axisO);
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
            inst = std::make_shared<AtPointConstraintIeqJeq>(frmi, frmj, axisO);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = std::make_shared<AtPointConstraintIeqJe>(frmi, frmj, axisO);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<AtPointConstraintIetJeq>(frmi, frmj, axisO);
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
            inst = std::make_shared<AtPointConstraintIeJeq>(frmi, frmj, axisO);
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

void AtPointConstraintIeJe::simUpdateAll()
{
    ConstraintIeJe::simUpdateAll();
}

void AtPointConstraintIeJe::calcG()
{
    aG = rIeJeO->at(axis) - aConstant;
}

ConstraintType AtPointConstraintIeJe::type()
{
    return displacement;
}

std::string AtPointConstraintIeJe::constraintSpec()
{
    return "AtPointConstraintIeJe";
}

void AtPointConstraintIeJe::fillPosICJacob(SpMatDsptr mat)
{
    //Do nothing.
}

void AtPointConstraintIeJe::fillVelICJacob(SpMatDsptr mat)
{
    //Do nothing.
}

void AtPointConstraintIeJe::fillAccICIterError(FColDsptr col)
{
    //Do nothing.
}

void AtPointConstraintIeJe::fillpFpy(SpMatDsptr mat)
{
    //Do nothing.
}

void AtPointConstraintIeJe::fillpFpydot(SpMatDsptr mat)
{
    //Do nothing.
}
