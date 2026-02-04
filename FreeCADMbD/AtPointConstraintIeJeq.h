/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIeJe.h"

namespace MbD {
    class AtPointConstraintIeJeq : public ConstraintIeJe
    {
    public:
        AtPointConstraintIeJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : axis(axisO), ConstraintIeJe(frmi, frmj) {}
        static std::shared_ptr<AtPointConstraintIeJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void initialize() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void simUpdateAll() override;
        void calcG() override;
        void calcpGpXI() override;
        void calcpGpEI() override;
        void calcpGpXJ() override;
        void calcpGpEJ() override;
        void calcppGpXIpXI() override;
        void calcppGpXIpEI() override;
        void calcppGpXIpXJ() override;
        void calcppGpXIpEJ() override;
        void calcppGpEIpEI() override;
        void calcppGpEIpXJ() override;
        void calcppGpEIpEJ() override;
        void calcppGpXJpXJ() override;
        void calcppGpXJpEJ() override;
        void calcppGpEJpEJ() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        virtual void initriIeJeO();
        std::string constraintSpec() override;

        size_t axis = SIZE_MAX;
		//Reuse rIeJeO in ConstraintIeJe
    };
}

