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
    class AtPointConstraintIeJe : public ConstraintIeJe
    {
    public:
        AtPointConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO) : axis(axisO), ConstraintIeJe(frmi, frmj) {}
        static std::shared_ptr<AtPointConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO);

        void simUpdateAll() override;
        void calcG() override;
        ConstraintType type() override;
        std::string constraintSpec() override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillVelICJacob(SpMatDsptr mat);
        void fillAccICIterError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;

        size_t axis = SIZE_MAX;
		//Reuse rIeJeO in ConstraintIeJe
    };
}

