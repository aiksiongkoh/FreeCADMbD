/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AtPointConstraintIJ.h"

namespace MbD {
    class AtPointConstraintIqcJc : public AtPointConstraintIJ
    {
        //pGpEI ppGpEIpEI iqXIminusOnePlusAxis iqEI 
    public:
        AtPointConstraintIqcJc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : AtPointConstraintIJ(frmi, frmj, axisO) {}
        static std::shared_ptr<AtPointConstraintIqcJc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;
        void calcPostDynCorrectorIteration() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void initializeGlobally() override;
        void initriIeJeO() override;
        void useEquationNumbers() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        std::string constraintSpec() override;

        FRowDsptr pGpEI;
        FMatDsptr ppGpEIpEI;
        size_t iqXIminusOnePlusAxis = SIZE_MAX;
        size_t iqEI = SIZE_MAX;
    };
}

