/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispIeJeqKe.h"

namespace MbD {
    class DispIetJeqKet : public DispIeJeqKe
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIetJeqKet() {}
        DispIetJeqKet(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeJeqKe(frmi, frmj) {}
        DispIetJeqKet(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk) : DispIeJeqKe(frmi, frmj, frmk) {}
        static std::shared_ptr<DispIetJeqKet> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void calcpVectorpt() override;
        void calcppVectorpXJpt() override;
        void calcppVectorpEJpt() override;
        void calcppVectorptpt() override;
        FColDsptr getpVectorpt() override;
        FMatDsptr getppVectorpXJpt() override;
        FMatDsptr getppVectorpEJpt() override;
        FColDsptr getppVectorptpt() override;
        void preVelIC() override;
        void preAccIC() override;

        FColDsptr prIeJeKept;
        FMatDsptr pprIeJeKepXJpt;
        FMatDsptr pprIeJeKepEJpt;
        FColDsptr pprIeJeKeptpt;
    };
}

