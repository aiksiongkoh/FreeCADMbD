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
    class DispIeJeqKeq : public DispIeJeqKe
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeJeqKeq() {}
        DispIeJeqKeq(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeJeqKe(frmi, frmj) {}
        static std::shared_ptr<DispIeJeqKeq> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcppVectorpXJpEK() override;
        void calcppVectorpEJpEK() override;
        FMatDsptr getprIeJeKepXJ() override;
        FMatDsptr getprIeJeKepEJ() override;
        FMatDsptr getppriIeJeKepEJpEJ(size_t axis) override;
        FMatDsptr prIeJeKepEK;
        FMatFColDsptr pprIeJeKepXJpEK;
        FMatFColDsptr pprIeJeKepEJpEK;
        FMatFColDsptr pprIeJeKepEKpEK;

    };
}

