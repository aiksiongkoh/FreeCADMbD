/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "EndFrame.h"
#include "Symbolic.h"
#include "EulerParametersDot.h"
#include "EulerParametersDDot.h"
#include "FullColumn.h"     //FColDsptr is defined
#include "FullMatrix.h"     //FMatDsptr is defined

namespace MbD {
    class EndFrameqt;

    class EndFrameccq : public EndFrame
    {
        //prOeOpE pprOeOpEpE pAOepE ppAOepEpE
    public:
        EndFrameccq() {}
        EndFrameccq(const std::string& str) : EndFrame(str) {}
        static std::shared_ptr<EndFrameccq> With();
        static std::shared_ptr<EndFrameccq> With(const std::string& str);
        void initialize() override;

        void initializeGlobally() override;
        void initEndFrameqt() override;
        void initEndFrameqt2() override;
        FMatFColDsptr ppAjOepEpE(size_t j) const;
        void simUpdateAll() override;
        FMatDsptr pAjOepE(size_t j) const override;
        FMatDsptr pAjOepET(size_t j) const;
        FMatDsptr ppriOeOpEpE(size_t i) const;
        size_t iqX() const override;
        size_t iqE() const override;
        FRowDsptr priOeOpE(size_t i) const;
        FColDsptr qXdot();
        std::shared_ptr<EulerParametersDot<double>> qEdot();
        FColDsptr qXddot();
        FColDsptr qEddot();
        FColDsptr rpep() override;
        FColFMatDsptr pAOppE() override;
        FMatDsptr aBOp() const override;
        bool isEndFrameq() override;
        FMatDsptr pvOeOpE();
        FColDsptr omeOeO() override;
        FMatDsptr pomeOeOpE();
        FMatDsptr pomeOeOpEdot();
        EndFrmsptr followEndFrame(EndFrmsptr frmi) override;
        bool has_qX() const override;
        void setTargetFrame(EndFrmsptr targetFrm) override;

        FMatDsptr prOeOpE;
        FMatFColDsptr pprOeOpEpE;
        FColFMatDsptr pAOepE;
        FMatFMatDsptr ppAOepEpE;
        EndFrmsptr targetFrame;
        std::shared_ptr<EndFrameqt> endFrameqt;
    };
}

