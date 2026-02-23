/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicIeJe.h"
#include "DispIeJeO.h"

namespace MbD {
    class DispIeJeKe : public KinematicIeJe
    {
    public:
        DispIeJeKe() {}
        DispIeJeKe(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIeJe(frmi, frmj) {}
        static std::shared_ptr<DispIeJeKe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void initialize() override;
        void simUpdateAll() override;
        void calcvalue() override;
        void calcpvaluepXI() override;
        void calcpvaluepEI() override;
        void calcpvaluepXJ() override;
        void calcpvaluepEJ() override;
        void calcpvaluepXK() override;
        void calcpvaluepEK() override;
        void calcppvaluepXIpXI() override;
        void calcppvaluepXIpEI() override;
        void calcppvaluepXIpXJ() override;
        void calcppvaluepXIpEJ() override;
        void calcppvaluepXIpEK() override;
        void calcppvaluepEIpEI() override;
        void calcppvaluepEIpXJ() override;
        void calcppvaluepEIpEJ() override;
        void calcppvaluepEIpEK() override;
        void calcppvaluepXJpXJ() override;
        void calcppvaluepXJpEJ() override;
        void calcppvaluepXJpEK() override;
        void calcppvaluepEJpEJ() override;
        void calcppvaluepEJpEK() override;
        void calcppvaluepEKpEK() override;
        virtual FMatDsptr getprIeJeOpXI();
        virtual FMatDsptr getprIeJeOpEI();
        virtual FMatDsptr getprIeJeOpXJ();
        virtual FMatDsptr getprIeJeOpEJ();
        virtual FMatDsptr getppriIeJeOpEIpEI(size_t axis);
        virtual FMatDsptr getppriIeJeOpEJpEJ(size_t axis);
        FColDsptr getprIeJeOpt();
        virtual FColDsptr getpprIeJeOptpt();
        bool hasSameEndFrms(const std::shared_ptr<DispIeJeKe> other) const;

        SpatialContainerFrame* frmKp = nullptr;
        bool has_qK = false;

        EndFrmsptr frmKe;
        std::shared_ptr<DispIeJeO> dispIeJeO;
        FMatDsptr aAOKe;
        FColDsptr rIeJeO;
        FColDsptr rIeJeKe;
        FMatDsptr prIeJeKepXI, prIeJeKepEI;
        FMatDsptr prIeJeKepXJ, prIeJeKepEJ;
        FMatDsptr prIeJeKepXK, prIeJeKepEK;
        FMatFColDsptr pprIeJeKepXIpXI;
        FMatFColDsptr pprIeJeKepXIpEI;
        FMatFColDsptr pprIeJeKepXIpXJ;
        FMatFColDsptr pprIeJeKepXIpEJ;
        FMatFColDsptr pprIeJeKepXIpXK;
        FMatFColDsptr pprIeJeKepXIpEK;
        FMatFColDsptr pprIeJeKepEIpEI;
        FMatFColDsptr pprIeJeKepEIpXJ;
        FMatFColDsptr pprIeJeKepEIpEJ;
        FMatFColDsptr pprIeJeKepEIpXK;
        FMatFColDsptr pprIeJeKepEIpEK;
        FMatFColDsptr pprIeJeKepXJpXJ;
        FMatFColDsptr pprIeJeKepXJpEJ;
        FMatFColDsptr pprIeJeKepXJpXK;
        FMatFColDsptr pprIeJeKepXJpEK;
        FMatFColDsptr pprIeJeKepEJpEJ;
        FMatFColDsptr pprIeJeKepEJpXK;
        FMatFColDsptr pprIeJeKepEJpEK;
        FMatFColDsptr pprIeJeKepXKpXK;
        FMatFColDsptr pprIeJeKepXKpEK;
        FMatFColDsptr pprIeJeKepEKpEK;
    };
}

