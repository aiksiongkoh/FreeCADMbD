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
        ConstraintType type() override;
        std::string constraintSpec() override;

        size_t axis = SIZE_MAX;
		//Reuse rIeJeO in ConstraintIeJe
    };
}

