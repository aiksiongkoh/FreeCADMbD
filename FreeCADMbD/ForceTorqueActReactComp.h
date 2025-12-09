/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueActReact.h"

namespace MbD {
    class ForceTorqueActReactComp : public ForceTorqueActReact
    {
        //
    public:
        ForceTorqueActReactComp() {}
        //ForceTorqueActReactComp(EndFrmsptr frmi, EndFrmsptr frmj) : ForceTorqueActReact(frmi, frmj) {}
        static std::shared_ptr<ForceTorqueActReactComp> With();
        
    };
}

