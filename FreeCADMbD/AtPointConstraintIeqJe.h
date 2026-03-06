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
    class AtPointConstraintIeqJe : public AtPointConstraintIeJe
    {
    public:
        AtPointConstraintIeqJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : AtPointConstraintIeJe(frmi, frmj, axisO) {}
        static std::shared_ptr<AtPointConstraintIeqJe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void simUpdateAll() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void calcpGpXI() override;
        void calcpGpEI() override;
        void calcppGpEIpEI() override;
        void fillAccICIterError(FColDsptr col) override;
        void addToJointForceI(FColDsptr col);
        void addToJointTorqueI(FColDsptr col);
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        size_t iqXI = SIZE_MAX;
        size_t iqEI = SIZE_MAX;
        FRowDsptr pGpXI;
        FRowDsptr pGpEI;
        FMatDsptr ppGpEIpEI;
    };
}


