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
    class AtPointConstraintIcJqc : public AtPointConstraintIJ
    {
        //pGpEJ ppGpEJpEJ iqXJminusOnePlusAxis iqEJ 
    public:
        AtPointConstraintIcJqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : AtPointConstraintIJ(frmi, frmj, axisO) {}
        static std::shared_ptr<AtPointConstraintIcJqc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void initializeGlobally() override;
        void initriIeJeO() override;
        void useEquationNumbers() override;
        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;

        FRowDsptr pGpEJ;
        FMatDsptr ppGpEJpEJ;
        size_t iqXJminusOnePlusAxis = SIZE_MAX, iqEJ = SIZE_MAX;
    };
}

