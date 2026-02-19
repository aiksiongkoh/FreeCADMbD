/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIeJe.h"
#include "DispCompIecJecKec.h"

namespace MbD {
    class TranslationConstraintIeJe : public ConstraintIeJe
    {
        //riIeJeIe
    public:
        TranslationConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi) : ConstraintIeJe(frmi, frmj), axisI(axisi) {}
        static std::shared_ptr<TranslationConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi);
        void initialize() override;

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
        void initializeGlobally() override;
        void initializeLocally() override;
        virtual void initriIeJeIe();
        void useUniqueDispIeJeO() override;
        void useUniqueDispIeJeKe() override;
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC()override;
        void preVelIC() override;
        ConstraintType type() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;
        std::string constraintSpec() override;

        size_t axisI = SIZE_MAX;
        std::shared_ptr<DispCompIecJecKec> riIeJeIe;
        //ToDo: Use DispCompIecJecIe instead of DispCompIecJecKec
    };
}

