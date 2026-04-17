/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "DirectionCosineConstraintIeqtJeq.h"

namespace MbD {

    class AllowZRotationConstraintIeqtJeq : public DirectionCosineConstraintIeqtJeq
    {
    public:
        AllowZRotationConstraintIeqtJeq(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);
        static std::shared_ptr<AllowZRotationConstraintIeqtJeq> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

        void postInput() override;
        void postPosIC() override;
        std::string constraintSpec() override;

    };
}
