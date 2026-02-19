/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

 //#include <memory>
 //#include <vector>
 //#include <functional>

#include "CartesianFrame.h"
#include "EndFrameqc.h"
#include "FullColumn.h"
#include "EulerParameters.h"
#include "EulerParametersDot.h"
#include "MarkerFramec.h"

namespace MbD {
    class Part;
    class MarkerFramec;
    class EulerConstraint;
    class AbsConstraint;

    class SpatialContainerFrame : public CartesianFrame
    {
        //ToDo: part iqX iqE qX qE qXdot qEdot qXddot qEddot aGeu aGabs markerFrames 
    public:
        SpatialContainerFrame() {}
        SpatialContainerFrame(const std::string& str) : CartesianFrame(str) {}

        virtual std::shared_ptr<MarkerFramec> createMarkerFrame(const std::string& str) = 0;

        void initialize() override;

        void initializeLocally() override;
        void initializeGlobally() override;
        void postInput() override;

        void addMarkerFrame(std::shared_ptr<MarkerFramec> x);
        EndFrmsptr endFrame(std::string name) const;
        void markerFramesDo(const std::function <void(std::shared_ptr<MarkerFramec>)>& f) const;

        void prePosIC() override;
        void prePosKine() override;
        void fillqsuWeights(DiagMatDsptr mat) override;
        void fillqsuddotlam(FColDsptr col) override;
        void fillqsulam(FColDsptr col) override;
        void fillpqsumu(FColDsptr col) override;
        void fillpqsumudot(FColDsptr col) override;
        void fillqsudot(FColDsptr col) override;
        void fillqsudotWeights(DiagMatDsptr mat) override;
        void useEquationNumbers() override;
        void setqsu(FColDsptr col) override;
        void setqsulam(FColDsptr col) override;
        void setqsudotlam(FColDsptr col) override;
        void setqsudot(FColDsptr col) override;
        void setqsuddotlam(FColDsptr col) override;
        void postPosICIteration() override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void postPosIC() override;
        void preDyn() override;
        void storeDynState() override;
        void fillPosKineError(FColDsptr col) override;
        void preVelIC() override;
        void postVelIC() override;
        void fillVelICError(FColDsptr col) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void preAccIC() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void postDynStep() override;
        void setpqsumu(FColDsptr col) override;
        void setpqsumudot(FColDsptr col) override;
        void setpqsumuddot(FColDsptr col) override;
        void postDynPredictor() override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
        void postDynOutput() override;
        size_t iqX() const override;
        size_t iqE() const override;
        virtual FColDsptr qX();
        virtual std::shared_ptr<EulerParameters<double>> qE();
        virtual FColDsptr qXdot();
        virtual std::shared_ptr<EulerParametersDot<double>> qEdot();
        virtual FColDsptr qXddot();
        virtual FColDsptr qEddot();
        virtual FMatDsptr aAOp();
        virtual FMatDsptr aC();
        virtual FMatDsptr aCdot();
        virtual FColDsptr alpOpO();
        virtual FColFMatDsptr pAOppE();
        virtual FColFMatDsptr pAdotOppE();
        virtual FMatDsptr pomeOpOpE();
        virtual FMatDsptr pomeOpOpEdot();
        virtual FColDsptr vOpO();
        virtual FMatDsptr aAdotOp();
        virtual FColDsptr aOpO();
        virtual FMatDsptr aAddotOp();
        virtual FColDsptr omeOpO();
        virtual FMatDsptr aBOp() const;
        virtual FColDsptr aOmO() const;

        std::shared_ptr<std::vector<std::shared_ptr<MarkerFramec>>> markerFrames;
    };
}

