/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AtPointConstraintIeJe.h"

namespace MbD {
    class AtPointConstraintIeJeq : public AtPointConstraintIeJe
    {
    public:
        AtPointConstraintIeJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : AtPointConstraintIeJe(frmi, frmj, axisO) {}
        static std::shared_ptr<AtPointConstraintIeJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void simUpdateAll() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void calcpGpXJ() override;
        void calcpGpEJ() override;
        void calcppGpEJpEJ() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;
        size_t iqXJ = SIZE_MAX;
        size_t iqEJ = SIZE_MAX;
        FRowDsptr pGpXJ;
        FRowDsptr pGpEJ;
        FMatDsptr ppGpEJpEJ;
    };
}

