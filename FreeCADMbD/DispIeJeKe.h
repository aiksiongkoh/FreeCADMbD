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
        DispIeJeKe(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk) : KinematicVectorIeJe(frmi, frmj), eFrmK(frmk) {}
        static std::shared_ptr<DispIeJeKe> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);

        void initialize() override;
        void initializeGlobally() override;
        void useUniqueDispIeJeO() override;
        void simUpdateAll() override;
        void calcVector() override;
        FColDsptr getVector() override;
        FMatDsptr getpVectorpXI() override;
        FMatDsptr getpVectorpEI() override;
        FMatDsptr getpVectorpXJ() override;
        FMatDsptr getpVectorpEJ() override;
        FMatDsptr getppCompipEIpEI(size_t axis) override;
        FMatDsptr getppCompipEJpEJ(size_t axis) override;
        FColDsptr getpVectorpt() override;
        FColDsptr getppVectorptpt() override;
        bool hasSameEndFrms(const std::shared_ptr<KinematicVectorIeJe> other) const override;

        EndFrmsptr eFrmK;
        std::shared_ptr<DispIeJeO> dispIeJeO;
        FMatDsptr aAOKe;
        FColDsptr rIeJeO;
        FColDsptr rIeJeKe;
    };
}

