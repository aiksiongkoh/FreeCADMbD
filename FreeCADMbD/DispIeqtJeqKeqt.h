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
        static std::shared_ptr<DispIeqtJeqKeqt> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        virtual void calcpVectorpt();
        virtual void calcppVectorpXIpt();
        virtual void calcppVectorpEIpt();
        virtual void calcppVectorpXJpt();
        virtual void calcppVectorpEJpt();
        virtual void calcppVectorpEKpt();
        virtual void calcppVectorptpt();
        void preVelIC() override;
        void preAccIC() override;

        FColDsptr prIeJeKept;
        FMatDsptr pprIeJeKepXIpt;
        FMatDsptr pprIeJeKepEIpt;
        FMatDsptr pprIeJeKepXJpt;
        FMatDsptr pprIeJeKepEJpt;
        FMatDsptr pprIeJeKepXKpt;
        FMatDsptr pprIeJeKepEKpt;
        FColDsptr pprIeJeKeptpt;
    };
}

