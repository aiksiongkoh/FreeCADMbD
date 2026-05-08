/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <memory>

#include "CartesianFrame.h"
#include "MarkerFrame.h"
#include "FullColumn.h"     //FColDsptr is defined
#include "FullMatrix.h"     //FMatDsptr is defined

namespace MbD {
    class SpatialContainerFrame;
    class EndFrameq;
    class EndFrame;
    class EndFramet;
    using EndFrmsptr = std::shared_ptr<EndFrame>;

    class EndFrame : public CartesianFrame
    {
        //markerFrame rOeO aAOe 
    public:
        EndFrame() {}
        EndFrame(const std::string& str) : CartesianFrame(str) {}
        static std::shared_ptr<EndFrame> With();
        static std::shared_ptr<EndFrame> With(const std::string& str);

        virtual FMatDsptr aAeO() const;
        virtual FColDsptr aAjOe(size_t j) const;
        virtual void aApm(FMatDsptr mat);
        virtual FMatDsptr aBOp() const;
        virtual FMatDsptr getaBOp() const;
        virtual FColDsptr aOeO() const;
        void simUpdateAll() override;
        virtual void fillContactEndFrames(std::set<EndFrame*> efrms);
        virtual std::shared_ptr<EndFrame> followEndFrame(EndFrmsptr frmi);
        virtual MarkerFrame* getMarkerFrame() const;
        virtual SpatialContainerFrame* getPartFrame() const;
        virtual FColDsptr ieO() const;
        void initialize() override;
        virtual void initEndFrameqt();
        virtual void initEndFrameqt2();
        virtual bool isEndFrameq();
        virtual FColDsptr jeO() const;
        virtual FColDsptr keO() const;
        virtual std::shared_ptr<EndFrameq> newCopyEndFrameq();
        virtual FColDsptr omeOeO();
        virtual FColFMatDsptr getpAOepE() const;
        virtual FColFMatDsptr pAOppE();
        virtual FMatDsptr pAjOepE(size_t j) const;
        virtual FMatDsptr pAjOepET(size_t j);
        virtual std::shared_ptr<EulerParameters<double>> qEOe() const;
        virtual double riOeO(size_t i) const;
        virtual FColDsptr rmeO();
        System* root() override;
        virtual FColDsptr rpep();
        virtual FColDsptr rpmp();
        virtual void setMarkerFrame(MarkerFrame* markerFrm);
        virtual void setTargetFrame(std::shared_ptr<EndFrame> targetFrm) {}
        virtual FColDsptr vOeO() const;
        virtual FMatDsptr getprOeOpE() const;
        virtual FMatFColDsptr getpprOeOpEpE() const;
        virtual FColDsptr getprOeOpt() const;
        virtual FMatDsptr getpprOeOpEpt() const;
        virtual FColDsptr getpprOeOptpt() const;
        virtual FMatDsptr getpAOept() const;
        virtual FColFMatDsptr getppAOepEpt() const;
        virtual FMatDsptr getppAOeptpt() const;
        virtual FMatDsptr pAOepEtimesFullColumn(FColDsptr col) const;
        virtual FMatDsptr pAOeTpEtimesFullColumn(FColDsptr col) const;
        virtual FMatFColDsptr ppAOeTpEpEtimesFullColumn(FColDsptr col) const;
        virtual FMatDsptr ppAOeTpEpttimesFullColumn(FColDsptr col) const;
        virtual FMatFColDsptr pAOeTpEtimesFullMatrix(FMatDsptr mat) const;

        FColDsptr rmem = std::make_shared<FullColumn<double>>(3);
        FMatDsptr aAme = FullMatrix<double>::identitysptr(3);
        MarkerFrame* markerFrame = nullptr; //Use raw pointer when pointing backwards.
        FColDsptr rOeO = std::make_shared<FullColumn<double>>(3);
        FMatDsptr aAOe = FullMatrix<double>::identitysptr(3);
        std::shared_ptr<EndFramet> endFramet;
    };
    //using EndFrmsptr = std::shared_ptr<EndFrame>;
}

