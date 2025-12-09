/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueVector.h"

namespace MbD {
    class TorqueVector : public ForceTorqueVector
    {
        //
    public:
        TorqueVector() {}
        static std::shared_ptr<TorqueVector> OnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        static std::shared_ptr<TorqueVector> OnFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);

        void onFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        void onFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);
    };
}
