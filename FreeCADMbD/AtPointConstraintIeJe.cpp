/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIeJe.h"
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

void AtPointConstraintIeJe::simUpdateAll()
{
    ConstraintIeJe::simUpdateAll();
}

void MbD::AtPointConstraintIeJe::calcG()
{
    auto rIeJeO = dispIeJeO->rIeJeO;
    aG = rIeJeO->at(axis) - aConstant;
}

ConstraintType MbD::AtPointConstraintIeJe::type()
{
    return displacement;
}

std::string MbD::AtPointConstraintIeJe::constraintSpec()
{
    return "AtPointConstraintIeJe";
}

void MbD::AtPointConstraintIeJe::fillPosICJacob(SpMatDsptr mat)
{
    //Do nothing.
}

void MbD::AtPointConstraintIeJe::fillVelICJacob(SpMatDsptr mat)
{
    //Do nothing.
}

void MbD::AtPointConstraintIeJe::fillAccICIterError(FColDsptr col)
{
    //Do nothing.
}

void MbD::AtPointConstraintIeJe::fillpFpy(SpMatDsptr mat)
{
    //Do nothing.
}

void MbD::AtPointConstraintIeJe::fillpFpydot(SpMatDsptr mat)
{
    //Do nothing.
}
