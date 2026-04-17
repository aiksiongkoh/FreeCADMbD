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
        static std::shared_ptr<DispIetJeqKet> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        virtual void calcpVectorpt();
        virtual void calcppVectorpXJpt();
        virtual void calcppVectorpEJpt();
        virtual void calcppVectorptpt();
        void preVelIC() override;
        void preAccIC() override;

        FColDsptr prIeJeKept;
        FMatDsptr pprIeJeKepXJpt;
        FMatDsptr pprIeJeKepEJpt;
        FColDsptr pprIeJeKeptpt;
    };
}

