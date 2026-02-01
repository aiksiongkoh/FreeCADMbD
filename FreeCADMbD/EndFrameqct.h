/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "EndFrameqc.h"

namespace MbD {
    class SymTime;
    class Symbolic;

    class EndFrameqct : public EndFrameqc
    {
        //Note: Do not subclass from EndFramect. 
        // Code duplication in EndFramect and EndFrameqct is less that in EndFrameqc and EndFrameqct
        //prOeOpE pprOeOpEpE pAOepE ppAOepEpE
        //time rmemBlks prmemptBlks pprmemptptBlks phiThePsiBlks pPhiThePsiptBlks ppPhiThePsiptptBlks 
        //rmem prmempt pprmemptpt aAme pAmept ppAmeptpt prOeOpt pprOeOpEpt pprOeOptpt pAOept ppAOepEpt ppAOeptpt 
    public:
        EndFrameqct() {}
        EndFrameqct(const std::string& str) : EndFrameqc(str) {}
        static std::shared_ptr<EndFrameqct> With();
        static std::shared_ptr<EndFrameqct> With(const std::string& str);
        void initialize() override;

        void initializeLocally() override;
        void initializeGlobally() override;
        void initprmemptBlks();
        void initpprmemptptBlks();
        virtual void initpPhiThePsiptBlks();
        virtual void initppPhiThePsiptptBlks();
        void postInput() override;
        void calcPostDynCorrectorIteration() override;
        FRowDsptr ppriOeOpEpt(size_t i) const;
        FMatDsptr ppAjOepETpt(size_t j) const;
        void prePosIC() override;
        void evalrmem() const;
        virtual void evalAme();
        void preVelIC() override;
        void postVelIC() override;
        FColDsptr pAjOept(size_t j) const;
        FMatDsptr ppAjOepETpt(size_t j);
        FColDsptr ppAjOeptpt(size_t j) const;
        double priOeOpt(size_t i) const;
        FRowDsptr ppriOeOpEpt(size_t i);
        double ppriOeOptpt(size_t i) const;
        void evalprmempt() const;
        virtual void evalpAmept();
        void evalpprmemptpt() const;
        virtual void evalppAmeptpt();
        FColDsptr rmeO() override;
        FColDsptr rpep() override;
        void preAccIC() override;
        bool isEndFrameqc() override;
        void postDynPredictor() override;
        void preDynOutput() override;
        void postDynOutput() override;

        double time = 0.0;
        std::shared_ptr<FullColumn<Symsptr>> rmemBlks, prmemptBlks, pprmemptptBlks;
        std::shared_ptr<FullColumn<Symsptr>> phiThePsiBlks, pPhiThePsiptBlks, ppPhiThePsiptptBlks;
        FColDsptr rmem, prmempt, pprmemptpt, prOeOpt, pprOeOptpt;
        FMatDsptr aAme, pAmept, ppAmeptpt, pAOept, ppAOeptpt;
        FMatDsptr pprOeOpEpt;
        FColFMatDsptr ppAOepEpt;
    };
}

