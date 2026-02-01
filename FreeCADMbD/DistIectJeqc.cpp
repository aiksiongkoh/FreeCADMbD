/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistIectJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DistIectJeqc> DistIectJeqc::With()
{
    auto inst = std::make_shared<DistIectJeqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<DistIectJeqc> DistIectJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistIectJeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistIectJeqc::initialize()
{
    DistIecJeqc::initialize();
    pprIeJepXJpt = FullRow<double>::With(3);
    pprIeJepEJpt = FullRow<double>::With(4);
}
