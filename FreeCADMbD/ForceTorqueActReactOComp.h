/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueActReactComp.h"

namespace MbD {
    class ForceTorqueActReactOComp : public ForceTorqueActReactComp
    {
        //aFTJeOi
    public:
        ForceTorqueActReactOComp() {}
        //ForceTorqueActReactOComp(EndFrmsptr frmi, EndFrmsptr frmj) : ForceTorqueActReactComp(frmi, frmj) {}
        static std::shared_ptr<ForceTorqueActReactOComp> With();
        void initialize() override;
        static std::shared_ptr<ForceTorqueActReactOComp> ForceOnFrmIandFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        static std::shared_ptr<ForceTorqueActReactOComp> TorqueOnFrmIandFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);

        void forceOnFrmIandFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        void torqueOnFrmIandFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        void postDynPredictor() override;

        double aFTJeOi;
    };
}

