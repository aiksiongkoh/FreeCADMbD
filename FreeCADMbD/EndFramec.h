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
#include "MarkerFramec.h"
#include "FullColumn.h"     //FColDsptr is defined
#include "FullMatrix.h"     //FMatDsptr is defined

namespace MbD {
    class SpatialContainerFrame;
    class EndFrameqc;
    class EndFramec;
    class EndFramect;
    using EndFrmsptr = std::shared_ptr<EndFramec>;

    class EndFramec : public CartesianFrame
    {
        //markerFrame rOeO aAOe 
    public:
        EndFramec() {}
        EndFramec(const std::string& str) : CartesianFrame(str) {}
        static std::shared_ptr<EndFramec> With();
        static std::shared_ptr<EndFramec> With(const std::string& str);

        virtual FMatDsptr aAeO() const;
        virtual FColDsptr aAjOe(size_t j) const;
        virtual void aApm(FMatDsptr mat);
        virtual FMatDsptr aBOp() const;
        virtual FMatDsptr getaBOp() const;
        virtual FColDsptr aOeO() const;
        void simUpdateAll() override;
        virtual void fillContactEndFrames(std::set<EndFramec*> efrms);
        virtual std::shared_ptr<EndFramec> followEndFrame(EndFrmsptr frmi);
        virtual MarkerFramec* getMarkerFrame() const;
        virtual SpatialContainerFrame* getPartFrame() const;
        virtual FColDsptr ieO() const;
        void initialize() override;
        virtual void initEndFrameqct();
        virtual void initEndFrameqct2();
        virtual bool isEndFrameqc();
        virtual FColDsptr jeO() const;
        virtual FColDsptr keO() const;
        virtual std::shared_ptr<EndFrameqc> newCopyEndFrameqc();
        virtual FColDsptr omeOeO();
        virtual FColFMatDsptr pAOepE() const;
        virtual FColFMatDsptr pAOppE();
        virtual FMatDsptr pAjOepE(size_t j) const;
        virtual FMatDsptr pAjOepET(size_t j);
        virtual std::shared_ptr<EulerParameters<double>> qEOe() const;
        virtual double riOeO(size_t i) const;
        virtual FColDsptr rmeO();
        System* root() override;
        virtual FColDsptr rpep();
        virtual FColDsptr rpmp();
        virtual void setMarkerFrame(MarkerFramec* markerFrm);
        virtual void setTargetFrame(std::shared_ptr<EndFramec> targetFrm) {}
        virtual FColDsptr vOeO() const;
        virtual FMatDsptr getprOeOpE() const;
        virtual FMatFColDsptr getpprOeOpEpE() const;
        virtual FMatDsptr pAOepEtimesFullColumn(FColDsptr col) const;

        FColDsptr rmem = std::make_shared<FullColumn<double>>(3);
        FMatDsptr aAme = FullMatrix<double>::identitysptr(3);
        MarkerFramec* markerFrame = nullptr; //Use raw pointer when pointing backwards.
        FColDsptr rOeO = std::make_shared<FullColumn<double>>(3);
        FMatDsptr aAOe = FullMatrix<double>::identitysptr(3);
        std::shared_ptr<EndFramect> endFramect;
    };
    //using EndFrmsptr = std::shared_ptr<EndFramec>;
}

