/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "KinematicCompiIeJe.h"
#include "DispIeJeKe.h"

namespace MbD {
    class DispCompiIeJeKe : public KinematicCompiIeJe
    {
    public:
        DispCompiIeJeKe() {}
        DispCompiIeJeKe(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis) : KinematicCompiIeJe(frmi, frmj, axis), eFrmK(frmk) {}

        static std::shared_ptr<DispCompiIeJeKe> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis);

        void initialize() override;
        void useUniqueDispIeJeO() override;
        void useUniqueDispIeJeKe() override;
        EndFrmsptr geteFrmK() override { return eFrmK; }

        FRowDsptr pvaluepXI() override;
        FRowDsptr pvaluepEI() override;
        FRowDsptr pvaluepXJ() override;
        FRowDsptr pvaluepEJ() override;
        FMatDsptr ppvaluepEIpEI() override;
        FMatDsptr ppvaluepEJpEJ() override;
        double pvaluept() override;
        double ppvalueptpt() override;

        std::shared_ptr<DispIeJeKe> dispIeJeKe;
        EndFrmsptr eFrmK;

    protected:
        std::shared_ptr<KinematicVectorIeJe> kineVector() const override;
        FColDsptr currentVector() const override;
    };
}
