/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistIeqtJeq.h"

using namespace MbD;

std::shared_ptr<DistIeqtJeq> DistIeqtJeq::With()
{
    auto inst = std::make_shared<DistIeqtJeq>();
    inst->initialize();
    return inst;
}

std::shared_ptr<DistIeqtJeq> DistIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DistIeqtJeq>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DistIeqtJeq::initialize()
{
    DistIeqJeq::initialize();
    pprIeJepXIpt = FullRow<double>::With(3);
    pprIeJepEIpt = FullRow<double>::With(4);
    pprIeJepXJpt = FullRow<double>::With(3);
    pprIeJepEJpt = FullRow<double>::With(4);
}
