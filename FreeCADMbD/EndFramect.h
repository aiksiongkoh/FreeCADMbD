/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "EndFramec.h"
#include "Symbolic.h"

namespace MbD {

    class EndFramect : public EndFramec
    {
        //rOeO = rOpO + aAOp * rpep
        //rOeO = rOpO(qX) + aAOp(qE) * (rpmp + aApm * (rmem(t)))
        //aAOe = aAOp(qE) * aApm * aAme(t)
        //time rmemBlks prmemptBlks pprmemptptBlks phiThePsiBlks pPhiThePsiptBlks ppPhiThePsiptptBlks 
        //rmem prmempt pprmemptpt aAme pAmept ppAmeptpt prOeOpt pprOeOpEpt pprOeOptpt pAOept ppAOepEpt ppAOeptpt 
    public:
        EndFramect() {}
        EndFramect(const std::string& str) : EndFramec(str) {}
        static std::shared_ptr<EndFramect> With(const std::string& str);
        void initialize() override;

        void initializeLocally() override;
        void initializeGlobally() override;
        void initprmemptBlks();
        void initpprmemptptBlks();
        virtual void initpPhiThePsiptBlks();
        virtual void initppPhiThePsiptptBlks();
        void postInput() override;
        void prePosIC() override;
        void evalrmem() const;
        virtual void evalAme();
        void preVelIC() override;
        FColDsptr pAjOept(size_t j) const;
        FColDsptr ppAjOeptpt(size_t j) const;
        double time = 0.0;
        double priOeOpt(size_t i) const;
        double ppriOeOptpt(size_t i) const;
        void evalprmempt() const;
        virtual void evalpAmept();
        void evalpprmemptpt() const;
        virtual void evalppAmeptpt();
        //FColDsptr rpep() override;
        void preAccIC() override;
        void postDynPredictor() override;
        void preDynOutput() override;
        void postDynOutput() override;

        std::shared_ptr<FullColumn<Symsptr>> rmemBlks, prmemptBlks, pprmemptptBlks;
        std::shared_ptr<FullColumn<Symsptr>> phiThePsiBlks, pPhiThePsiptBlks, ppPhiThePsiptptBlks;
        FColDsptr prmempt, pprmemptpt, prOeOpt, pprOeOptpt;
        FMatDsptr pAmept, ppAmeptpt, pAOept, ppAOeptpt;
    };
}

