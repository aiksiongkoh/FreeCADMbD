/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <memory>

#include "DirectionCosineIeJe.h"
#include "FullColumn.h"
#include "EndFrame.h"
#include "EndFramet.h"
#include "EndFrameqt.h"
#include "DirectionCosineIeqtJeq.h"
#include "DirectionCosineIeJeq.h"
#include "DirectionCosineIetJeq.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIeJe> DirectionCosineIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    std::shared_ptr<DirectionCosineIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DirectionCosineIeqtJeq>(frmi, frmj, axisi, axisj);
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
            inst = std::make_shared<DirectionCosineIeqJeq>(frmi, frmj, axisi, axisj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = std::make_shared<DirectionCosineIeqJe>(frmi, frmj, axisi, axisj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throw SimulationStoppingError("To be implemented.");
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = std::make_shared<DirectionCosineIetJeq>(frmi, frmj, axisi, axisj);
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
            inst = std::make_shared<DirectionCosineIeJeq>(frmi, frmj, axisi, axisj);
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

void DirectionCosineIeJe::simUpdateAll()
{
    //cos(the) = aAijIeJe = aAcoliOIe->dot(aAcoljOJe);
    aAjOIe = eFrmI->aAjOe(axisI);
    aAjOJe = eFrmJ->aAjOe(axisJ);
    aAijIeJe = aAjOIe->dot(aAjOJe);
}

double DirectionCosineIeJe::value()
{
    return aAijIeJe;
}
