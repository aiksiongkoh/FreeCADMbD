/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispIeqtJeqKeqt.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispIeqtJeqKeqt> DispIeqtJeqKeqt::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    auto inst = std::make_shared<DispIeqtJeqKeqt>(frmi, frmj);
    inst->initialize();
    return inst;
}

void DispIeqtJeqKeqt::initializeGlobally()
{
    //Variables are constants.
}

void MbD::DispIeqtJeqKeqt::preVelIC()
{
    DispIeqJeqKeq::preVelIC();
    calcpvaluept();
}

void MbD::DispIeqtJeqKeqt::preAccIC()
{
    DispIeqJeqKeq::preAccIC();
    calcppvaluepXJpt();
    calcppvaluepEJpt();
    calcppvalueptpt();
}
