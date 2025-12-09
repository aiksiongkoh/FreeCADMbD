/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "AnyPosICNewtonRaphson.h"

namespace MbD {
    class Part;

    class PosICDragLimitNewtonRaphson : public AnyPosICNewtonRaphson
    {
        //Kinematics with under constrained system
    public:
        static std::shared_ptr<PosICDragLimitNewtonRaphson> With();
        void run() override;
        void iterate() override;
        void preRun() override;
        void initializeGlobally() override;
        void setdragParts(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts);

        std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts;
    };
}
