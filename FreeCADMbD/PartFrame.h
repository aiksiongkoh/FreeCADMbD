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

    class PartFrame : public SpatialContainerFrame
    {
        //ToDo: part iqX iqE qX qE qXdot qEdot qXddot qEddot aGeu aGabs markerFrames 
    public:
        PartFrame() {}
        PartFrame(const std::string& str);
        static std::shared_ptr<PartFrame> With();
        static std::shared_ptr<PartFrame> With(const std::string& str);
        void initialize() override;
        bool has_qX() const override;
        std::shared_ptr<MarkerFramec> createMarkerFrame(const std::string& str) override;
        System* root() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void asFixed();
        void postInput() override;
        void simUpdateAll() override;

        void setqX(FColDsptr x) const;
        FColDsptr getqX() const;
        void setqE(FColDsptr x) const;
        void setaAap(FMatDsptr mat);
        FColDsptr getqE() const;
        void setqXdot(FColDsptr x);
        FColDsptr getqXdot() const;
        void setomeOpO(FColDsptr x);
        FColDsptr getomeOpO() const;
        void setqXddot(FColDsptr x);
        FColDsptr getqXddot() const;
        void setqEddot(FColDsptr x);
        FColDsptr getqEddot() const;
        FColDsptr omeOpO() override;

        void setPart(Part* x);
        Part* getPart() const;
        void addMarkerFrame(std::shared_ptr<MarkerFramec> x);
        EndFrmsptr endFrame(std::string name);
        void aGabsDo(const std::function <void(std::shared_ptr<Constraint>)>& f) const;
        void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos) override;
        void reactivateRedundantConstraints() override;
        void constraintsReport() override;

        void prePosIC() override;
        void prePosKine() override;
        FColDsptr rOpO() const;
        FMatDsptr aAOp() override;
        FMatDsptr aC() override;
        FMatDsptr aCdot() override;
        FColDsptr alpOpO() override;
        FColFMatDsptr pAOppE() override;
        FColFMatDsptr pAdotOppE() override;
        FMatDsptr pomeOpOpE() override;
        FMatDsptr pomeOpOpEdot() override;
        FColDsptr vOpO() override;
        FMatDsptr aAdotOp() override;
        FColDsptr aOpO() override;
        FMatDsptr aAddotOp() override;
        FMatDsptr aBOp() const override;
        void fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) override;
        void fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) override;
        void fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) override;
        void fillqsu(FColDsptr col) override;
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
        double suggestSmallerOrAcceptDynStepSize(double hnew) override;
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

        Part* part = nullptr; //Use raw pointer when pointing backwards.
        size_t iqX = SIZE_MAX;
        size_t iqE = SIZE_MAX;    //Position index of frame variables qX and qE in system list of variables
        FColDsptr qX = std::make_shared<FullColumn<double>>(3);
        std::shared_ptr<EulerParameters<double>> qE = EulerParameters<double>::With(4);
        FColDsptr qXdot = std::make_shared<FullColumn<double>>(3);
        std::shared_ptr<EulerParametersDot<double>> qEdot = EulerParametersDot<double>::With(4);
        FColDsptr qXddot = std::make_shared<FullColumn<double>>(3);
        FColDsptr qEddot = std::make_shared<FullColumn<double>>(4);
        std::shared_ptr<Constraint> aGeu;
        std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> aGabs;
    };
}

