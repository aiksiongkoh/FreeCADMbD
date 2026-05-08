/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistIeqctJeqc.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DistIeqctJeqc> DistIeqctJeqc::With()
{
    auto inst = std::make_shared<DistIeqctJeqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<DistIeqctJeqc> DistIeqctJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistIeqctJeqc>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistIeqctJeqc::initialize()
{
    DistIeqcJeqc::initialize();
    pprIeJepXIpt = FullRow<double>::With(3);
    pprIeJepEIpt = FullRow<double>::With(4);
    pprIeJepXJpt = FullRow<double>::With(3);
    pprIeJepEJpt = FullRow<double>::With(4);
}
