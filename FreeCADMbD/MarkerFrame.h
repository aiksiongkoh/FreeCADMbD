/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <memory>
#include <functional>

#include "CartesianFrame.h"
#include "FullColumn.h"
#include "FullMatrix.h"
#include "EulerParametersDot.h"
#include "EulerParametersDDot.h"

namespace MbD {
    class CartesianFrame;
    class PartFrame;
    class EndFramec;
    using EndFrmsptr = std::shared_ptr<EndFramec>;

    class MarkerFrame : public CartesianFrame
    {
        //partFrame rpmp aApm rOmO aAOm prOmOpE pAOmpE pprOmOpEpE ppAOmpEpE endFrames 
    public:
        MarkerFrame();
        MarkerFrame(const std::string& str);
        static std::shared_ptr<MarkerFrame> With(const std::string& str);
        void initialize() override;
        System* root() override;
        void addEndFrame(EndFrmsptr x);
        void endFramesDo(const std::function <void(EndFrmsptr)>& f) const;

        FColDsptr aAdotjOm(size_t j);
        void setaApm(FMatDsptr mat) const;
        FMatDsptr aBOp();
        FColDsptr aOmO() const;
        void calcPostDynCorrectorIteration() override;
        void fillpqsumu(FColDsptr col) override;
        void fillpqsumudot(FColDsptr col) override;
        void fillqsu(FColDsptr col) override;
        void fillqsuddotlam(FColDsptr col) override;
        void fillqsudot(FColDsptr col) override;
        void fillqsudotPlam(FColDsptr col) override;
        void fillqsudotPlamDeriv(FColDsptr col) override;
        void fillqsudotWeights(DiagMatDsptr diagMat) override;
        void fillqsulam(FColDsptr col) override;
        void fillqsuWeights(DiagMatDsptr diagMat) override;
        void initializeGlobally() override;
        void initializeLocally() override;
        size_t iqE() const;
        size_t iqX() const;
        FColDsptr omeOmO() const;
        FMatDsptr pAdotjOmpE(size_t j);
        FMatDsptr pAdotjOmpET(size_t j);
        FColFMatDsptr pAOppE();
        PartFrame* getPartFrame() const;
        void setPartFrame(PartFrame* partFrm);
        FMatDsptr pomeOmOpE();
        FMatDsptr pomeOmOpEdot();
        void postDynCorrectorIteration() override;
        void postDynOutput() override;
        void postDynPredictor() override;
        void postDynStep() override;
        void postInput() override;
        void postPosIC() override;
        void postPosICIteration() override;
        void postStaticIteration() override;
        void postVelIC() override;
        void preAccIC() override;
        void preDyn() override;
        void preDynOutput() override;
        void prePosIC() override;
        void preStatic() override;
        void preVelIC() override;
        FMatDsptr pvOmOpE();
        FColDsptr qEddot() const;
        std::shared_ptr<EulerParametersDot<double>> qEdot() const;
        FColDsptr qX() const;
        FColDsptr qXddot() const;
        FColDsptr qXdot() const;
        FColDsptr rmemOFrOeO(FColDsptr rOeOCol) const;
        FColDsptr rOeOOFrmem(FColDsptr rmemCol) const;
        void setrpmp(FColDsptr x) const;
        void setpqsumu(FColDsptr col) override;
        void setpqsumuddot(FColDsptr col) override;
        void setpqsumudot(FColDsptr col) override;
        void setqsu(FColDsptr col) override;
        void setqsuddotlam(FColDsptr col) override;
        void setqsudot(FColDsptr col) override;
        void setqsudotlam(FColDsptr col) override;
        void setqsudotPlam(FColDsptr col) override;
        void setqsudotPlamDeriv(FColDsptr col) override;
        void setqsulam(FColDsptr col) override;
        void simUpdateAll() override;
        void storeDynState() override;
        FColDsptr vOmO() const;
        FColDsptr vOeO_of_rmem() const;

        PartFrame* partFrame = nullptr; //Use raw pointer when pointing backwards.
        FColDsptr rpmp = std::make_shared<FullColumn<double>>(3);
        FMatDsptr aApm = FullMatrix<double>::identitysptr(3);
        FColDsptr rOmO = std::make_shared<FullColumn<double>>(3);
        FMatDsptr aAOm = FullMatrix<double>::identitysptr(3);
        FMatDsptr prOmOpE;
        FColFMatDsptr pAOmpE;
        FMatFColDsptr pprOmOpEpE;
        FMatFMatDsptr ppAOmpEpE;
        std::shared_ptr<std::vector<EndFrmsptr>> endFrames;

    };
}

