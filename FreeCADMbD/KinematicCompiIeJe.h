/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "KinematicIeJe.h"

namespace MbD {
    class KinematicVectorIeJe;

    class KinematicCompiIeJe : public KinematicIeJe
    {
    public:
        KinematicCompiIeJe() {}
        KinematicCompiIeJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) : KinematicIeJe(frmi, frmj), axis(axis) {}

        void useUniqueDispIeJeO() override;
        void simUpdateAll() override;
        FRowDsptr pvaluepXI() override;
        FRowDsptr pvaluepEI() override;
        FMatDsptr ppvaluepXIpXI() override;
        FMatDsptr ppvaluepXIpEI() override;
        FMatDsptr ppvaluepEIpEI() override;
        FRowDsptr pvaluepXJ() override;
        FRowDsptr pvaluepEJ() override;
        FMatDsptr ppvaluepXIpXJ() override;
        FMatDsptr ppvaluepXIpEJ() override;
        FMatDsptr ppvaluepEIpXJ() override;
        FMatDsptr ppvaluepEIpEJ() override;
        FMatDsptr ppvaluepXJpXJ() override;
        FMatDsptr ppvaluepXJpEJ() override;
        FMatDsptr ppvaluepEJpEJ() override;
        FRowDsptr pvaluepEK() override;
        FMatDsptr ppvaluepXIpEK() override;
        FMatDsptr ppvaluepEIpEK() override;
        FMatDsptr ppvaluepXJpEK() override;
        FMatDsptr ppvaluepEJpEK() override;
        FMatDsptr ppvaluepEKpEK() override;
        double pvaluept() override;
        double ppvalueptpt() override;
        FRowDsptr ppvaluepXIpt() override;
        FRowDsptr ppvaluepEIpt() override;
        FRowDsptr ppvaluepXJpt() override;
        FRowDsptr ppvaluepEJpt() override;
        FRowDsptr ppvaluepEKpt() override;
        double value() override;

        size_t axis = SIZE_MAX;

    protected:
        virtual std::shared_ptr<KinematicVectorIeJe> kineVector() const = 0;
        virtual FColDsptr currentVector() const = 0;

        double componentFrom(FColDsptr col) const;
        FRowDsptr componentRowFrom(FMatDsptr mat) const;
        FMatDsptr componentMatrixFrom(FMatFColDsptr mat) const;
    };
}
