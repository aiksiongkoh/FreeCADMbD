/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicVectorIeJe.h"
#include "DispIeJeO.h"

namespace MbD {
    class DispIeJeKe : public KinematicVectorIeJe
    {
    public:
        DispIeJeKe() {}
        DispIeJeKe(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicVectorIeJe(frmi, frmj) {}
        static std::shared_ptr<DispIeJeKe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void initialize() override;
        void initializeGlobally() override;
        void simUpdateAll() override;
        void calcVector() override;
        virtual FMatDsptr getprIeJeKepXI();
        virtual FMatDsptr getprIeJeKepEI();
        virtual FMatDsptr getprIeJeKepXJ();
        virtual FMatDsptr getprIeJeKepEJ();
        virtual FMatDsptr getppriIeJeKepEIpEI(size_t axis);
        virtual FMatDsptr getppriIeJeKepEJpEJ(size_t axis);
        FColDsptr getprIeJeKept();
        virtual FColDsptr getpprIeJeKeptpt();
        bool hasSameEndFrms(const std::shared_ptr<DispIeJeKe> other) const;
        void useUniqueDispIeJeO();

        SpatialContainerFrame* frmKp = nullptr;
        bool has_qK = false;

        EndFrmsptr frmKe;
        std::shared_ptr<DispIeJeO> dispIeJeO;
        FMatDsptr aAOKe;
        FColDsptr rIeJeO;
        FColDsptr rIeJeKe;
    };
}

