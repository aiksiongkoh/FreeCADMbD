/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "EndFrameq.h"

namespace MbD {
    class SymTime;
    class Symbolic;

    class EndFrameqt : public EndFrameq
    {
        //rOeO = rOpO + aAOp * rpep
        //rOeO = rOpO(qX) + aAOp(qE) * (rpmp + aApm * (rmem(t)))
        //aAOe = aAOp(qE) * aApm * aAme(t)
        //Note: Do not subclass from EndFramet. 
        // Code duplication in EndFramet and EndFrameqt is less that in EndFrameq and EndFrameqt
        //prOeOpE pprOeOpEpE pAOepE ppAOepEpE
        //time rmemBlks prmemptBlks pprmemptptBlks the1x2y3zBlks pthe1x2y3zptBlks ppthe1x2y3zptptBlks 
        //rmem prmempt pprmemptpt aAme pAmept ppAmeptpt prOeOpt pprOeOpEpt pprOeOptpt pAOept ppAOepEpt ppAOeptpt 
    public:
        EndFrameqt() {}
        EndFrameqt(const std::string& str) : EndFrameq(str) {}
        static std::shared_ptr<EndFrameqt> With();
        static std::shared_ptr<EndFrameqt> With(const std::string& str);
        void initialize() override;

        void initializeLocally() override;
        void initializeGlobally() override;
        void initprmemptBlks();
        void initpprmemptptBlks();
        virtual void initpthe1x2y3zptBlks();
        virtual void initppthe1x2y3zptptBlks();
        void postInput() override;
        void simUpdateAll() override;
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
        void preStatic() override;
        bool isEndFrameq() override;
        void postDynPredictor() override;
        void preDynOutput() override;
        void postDynOutput() override;
        FColDsptr getprOeOpt() const override;
        FMatDsptr getpprOeOpEpt() const override;
        FColDsptr getpprOeOptpt() const override;
        FMatDsptr getpAOept() const override;
        FColFMatDsptr getppAOepEpt() const override;
        FMatDsptr getppAOeptpt() const override;
        FMatDsptr ppAOeTpEpttimesFullColumn(FColDsptr col) const override;

        double time = 0.0;
        std::shared_ptr<FullColumn<Symsptr>> rmemBlks, prmemptBlks, pprmemptptBlks;
        std::shared_ptr<FullColumn<Symsptr>> the1x2y3zBlks, pthe1x2y3zptBlks, ppthe1x2y3zptptBlks;
        FColDsptr prmempt, pprmemptpt, prOeOpt, pprOeOptpt;
        FMatDsptr pAmept, ppAmeptpt, pAOept, ppAOeptpt;
        FMatDsptr pprOeOpEpt;
        FColFMatDsptr ppAOepEpt;
    };
}

