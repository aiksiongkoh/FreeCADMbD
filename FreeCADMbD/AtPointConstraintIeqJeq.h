/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AtPointConstraintIeqJe.h"

namespace MbD {
    class AtPointConstraintIeqJeq : public AtPointConstraintIeqJe
    {
    public:
        AtPointConstraintIeqJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : AtPointConstraintIeqJe(frmi, frmj, axisO) {}
        static std::shared_ptr<AtPointConstraintIeqJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void initializeLocally() override;
        void initializeGlobally() override;
        void calcpGpXJ() override;
        void calcpGpEJ() override;
        void calcppGpEJpEJ() override;
        void useEquationNumbers() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
    };
}

