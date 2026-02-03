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

#include "SpatialContainerFrame.h"
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

    class AssemblyFrame : public SpatialContainerFrame
    {
        //ToDo: part iqX iqE qX qE qXdot qEdot qXddot qEddot aGeu aGabs markerFrames 
    public:
        AssemblyFrame() {}
        AssemblyFrame(const std::string& str);
        static std::shared_ptr<AssemblyFrame> With();
        static std::shared_ptr<AssemblyFrame> With(const std::string& str);

        std::shared_ptr<MarkerFramec> createMarkerFrame(const std::string& str) override;
        System* root() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void postInput() override;
        void simUpdateAll() override;
        void setAssembly(System* x);
        System* getAssembly() const;

        void setPart(Part* x);
        FColFMatDsptr pAOppE() override;

        void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos) override;
        void reactivateRedundantConstraints() override;
        void constraintsReport() override;
        void fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) override;
        void fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) override;
        void fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) override;
        void fillqsu(FColDsptr col) override;
        void fillqsuWeights(DiagMatDsptr diagMat) override;
        void fillqsuddotlam(FColDsptr col) override;
        void fillqsulam(FColDsptr col) override;
        void fillpqsumu(FColDsptr col) override;
        void fillpqsumudot(FColDsptr col) override;
        void fillqsudot(FColDsptr col) override;
        void fillqsudotWeights(DiagMatDsptr diagMat) override;
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
        double suggestSmallerOrAcceptDynStepSize(double hnew) override;

        System* assembly = nullptr; //Use raw pointer when pointing backwards.
    };
}

