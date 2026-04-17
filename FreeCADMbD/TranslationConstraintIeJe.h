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
#include "DispIeJeKe.h"

namespace MbD {
    class TranslationConstraintIeJe : public ConstraintIeJe
    {
    //frmIe = frmKe
    //rIeJeO = rOJeO - rOIeO
    //rIeJeKe = aAKeO * rIeJeO
    //prIeJeKepXI = aAOKeT * prIeJeOpXI
    //prIeJeKepEI = aAOKeT * prIeJeOpEI
    //prIeJeKepXJ = aAOKeT * prIeJeOpXJ
    //prIeJeKepEJ = aAOKeT * prIeJeOpEJ
    //prIeJeKepEK = pAOKeTpEK * rIeJeO
    //pprIeJeKepXIpEK = pAOKeTpEK * prIeJeOpXI
    //pprIeJeKepEIpEI = aAOKeT * pprIeJeOpEIpEI
    //pprIeJeKepEIpEK = pAOKeTpEK * prIeJeOpEI
    //pprIeJeKepXJpEK = pAOKeTpEK * prIeJeOpXJ
    //pprIeJeKepEJpEK = pAOKeTpEK * prIeJeOpEJ
    //pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO
    public:
        TranslationConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi) : ConstraintIeJe(frmi, frmj), axisI(axisi) {}
        static std::shared_ptr<TranslationConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi);
        void initialize() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void useUniqueDispIeJeO() override;
        void useUniqueDispIeJeKe() override;

        void simUpdateAll() override;
        void postInput() override;

        void prePosIC() override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void postPosICIteration() override;

        void preVelIC() override;
        void fillVelICJacob(SpMatDsptr mat) override;

        void preAccIC() override;
        void fillAccICIterError(FColDsptr col) override;

        void preDyn() override;
        void preDynOutput() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;
        void addToJointForceJ(FColDsptr col) override;
        void addToJointTorqueJ(FColDsptr col) override;

        void calcG() override;
        virtual void initriIeJeIe();
        ConstraintType type() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void postDynOutput() override;
        std::string constraintSpec() override;

        size_t axisI = SIZE_MAX;
        std::shared_ptr<DispCompIecJecKec> riIeJeIe;
        std::shared_ptr<DispIeJeKe> dispIeJeIe;
        //ToDo: Use DispCompIecJecIe instead of DispCompIecJecKec
    };
}

