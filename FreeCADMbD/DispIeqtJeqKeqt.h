/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DispIeqJeqKeq.h"

namespace MbD {
    class DispIeqtJeqKeqt : public DispIeqJeqKeq
    {
        //prIeJeOpXJ prIeJeOpEJ pprIeJeOpEJpEJ 
    public:
        DispIeqtJeqKeqt() {}
        DispIeqtJeqKeqt(EndFrmsptr frmi, EndFrmsptr frmj) : DispIeqJeqKeq(frmi, frmj) {}
        DispIeqtJeqKeqt(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk) : DispIeqJeqKeq(frmi, frmj, frmk) {}
        static std::shared_ptr<DispIeqtJeqKeqt> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void calcpVectorpt() override;
        void calcppVectorpXIpt() override;
        void calcppVectorpEIpt() override;
        void calcppVectorpXJpt() override;
        void calcppVectorpEJpt() override;
        void calcppVectorpEKpt() override;
        void calcppVectorptpt() override;
        FColDsptr getpVectorpt() override;
        FMatDsptr getppVectorpXIpt() override;
        FMatDsptr getppVectorpEIpt() override;
        FMatDsptr getppVectorpXJpt() override;
        FMatDsptr getppVectorpEJpt() override;
        FMatDsptr getppVectorpEKpt() override;
        FColDsptr getppVectorptpt() override;
        void preVelIC() override;
        void preAccIC() override;

        FColDsptr prIeJeKept;
        FMatDsptr pprIeJeKepXIpt;
        FMatDsptr pprIeJeKepEIpt;
        FMatDsptr pprIeJeKepXJpt;
        FMatDsptr pprIeJeKepEJpt;
        FMatDsptr pprIeJeKepEKpt;
        FColDsptr pprIeJeKeptpt;
    };
}

