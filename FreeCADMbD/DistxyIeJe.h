/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "KinematicIeJe.h"
#include "DispCompiIeJeIe.h"

namespace MbD {
    class DistxyIeJe : public KinematicIeJe
    {
        //distxy xIeJeIe yIeJeIe
    public:
        DistxyIeJe() {}
        DistxyIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIeJe(frmi, frmj) {}
        static std::shared_ptr<DistxyIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
        void initialize() override;

        void simUpdateAll() override;
        void initializeGlobally() override;
        void initializeLocally() override;
        void useUniqueDispIeJeO() override;
        void useUniqueDispIeJeKe() override;
        virtual void init_xyIeJeIe();
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC() override;
        void preStatic() override;
        void preVelIC() override;
        double value() override;

        double distxy = 0.0;
        std::shared_ptr<DispCompiIeJeIe> xIeJeIe, yIeJeIe;
    
    };
}

