/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIeqcJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIeqcJeqcO> DispCompIeqcJeqcO::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompIeqcJeqcO>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompIeqcJeqcO::initializeGlobally()
{
    DispCompIeqcJecO::initializeGlobally();
    priIeJeOpXJ = FullRow<double>::With(3, 0.0);
    priIeJeOpXJ->at(axis) = 1.0;
    ppriIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->ppriOeOpEpE(axis);
}

void DispCompIeqcJeqcO::calcPostDynCorrectorIteration()
{
    DispCompIeqcJecO::calcPostDynCorrectorIteration();
    priIeJeOpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->priOeOpE(axis);
}

FRowDsptr DispCompIeqcJeqcO::pvaluepXJ()
{
    return priIeJeOpXJ;
}

FRowDsptr DispCompIeqcJeqcO::pvaluepEJ()
{
    return priIeJeOpEJ;
}

FMatDsptr DispCompIeqcJeqcO::ppvaluepEJpEJ()
{
    return ppriIeJeOpEJpEJ;
}
