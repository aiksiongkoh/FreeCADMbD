/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineConstraintIeqJeq.h"
#include "DirectionCosineIecJec.h"

namespace MbD {
    class DirectionCosineConstraintIeqtJeq : public DirectionCosineConstraintIeqJeq
    {
    public:
        DirectionCosineConstraintIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineConstraintIeqJeq(frmi, frmj, axisi, axisj) {}
        static std::shared_ptr<DirectionCosineConstraintIeqtJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

        void initializeLocally() override;
        void initializeGlobally() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        virtual void initaAijIeJe();

    };
}

