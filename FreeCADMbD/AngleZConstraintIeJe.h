/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ConstraintIeJe.h"
#include "AngleZIeJe.h"

namespace MbD {
    class AngleZConstraintIeJe : public ConstraintIeJe
    {
        //thezIeJe 
    public:
        AngleZConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintIeJe(frmi, frmj) {}

        static std::shared_ptr<AngleZConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) = 0;
        virtual void initthezIeJe();
        void initialize() override;
        void initializeGlobally() override;
        void initializeLocally() override;
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preVelIC() override;
        ConstraintType type() override;
        std::string constraintSpec() override;

        std::shared_ptr<AngleZIeJe> thezIeJe;
    };
}
