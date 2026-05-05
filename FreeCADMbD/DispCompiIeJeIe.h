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
    class DispCompiIeJeIe : public KinematicCompiIeJe
    {
    public:
        DispCompiIeJeIe() {}
        DispCompiIeJeIe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) : KinematicCompiIeJe(frmi, frmj, axis) {}

        static std::shared_ptr<DispCompiIeJeIe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);

        void initialize() override;
        void simUpdateAll() override;
        void useUniqueDispIeJeKe() override;
        double value() override;
        FRowDsptr pvaluepEI() override;
        FMatDsptr ppvaluepXIpEI() override;
        FMatDsptr ppvaluepEIpEI() override;
        FMatDsptr ppvaluepEIpXJ() override;
        FMatDsptr ppvaluepEIpEJ() override;
        FRowDsptr ppvaluepXIpt() override;
        FRowDsptr ppvaluepEIpt() override;

        std::shared_ptr<DispIeJeKe> dispIeJeIe;

    protected:
        std::shared_ptr<KinematicVectorIeJe> kineVector() const override;
        FColDsptr currentVector() const override;
    };
}
