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
#include "FullColumn.h"     //FColDsptr is defined
#include "FullMatrix.h"     //FMatDsptr is defined

namespace MbD {
    class PartFrame;
    class MarkerFrame;
    class EndFrameqc;
    class EndFramec;
    using EndFrmsptr = std::shared_ptr<EndFramec>;

    class EndFramec : public CartesianFrame
    {
        //markerFrame rOeO aAOe 
    public:
        EndFramec() {}
        EndFramec(const std::string& str) : CartesianFrame(str) {}
        static std::shared_ptr<EndFramec> With(const std::string& str);
        void initialize() override;
        System* root() override;
        virtual void initEndFrameqct();
        virtual void initEndFrameqct2();

        FMatDsptr aAeO() const;
        FColDsptr aAjOe(size_t j);
        void aApm(FMatDsptr mat);
        void calcPostDynCorrectorIteration() override;
        virtual void fillContactEndFrames(std::set<EndFramec*> efrms);
        FColDsptr ieO();
        FColDsptr jeO();
        FColDsptr keO();
        MarkerFrame* getMarkerFrame() const;
        void setMarkerFrame(MarkerFrame* markerFrm);
        std::shared_ptr<EndFrameqc> newCopyEndFrameqc();
        virtual std::shared_ptr<EndFrameqc> followEndFrame(EndFrmsptr frmi);
        PartFrame* getPartFrame();
        std::shared_ptr<EulerParameters<double>> qEOe();
        double riOeO(size_t i);
        virtual FColDsptr rpmp();
        virtual FColDsptr rmeO();
        virtual FColDsptr rpep();
        virtual FColFMatDsptr pAOppE();
        virtual FMatDsptr aBOp();
        virtual bool isEndFrameqc();
        FColDsptr vOeO();
        FColDsptr aOeO();

        MarkerFrame* markerFrame = nullptr; //Use raw pointer when pointing backwards.
        FColDsptr rOeO = std::make_shared<FullColumn<double>>(3);
        FMatDsptr aAOe = FullMatrix<double>::identitysptr(3);
    };
    //using EndFrmsptr = std::shared_ptr<EndFramec>;
}

