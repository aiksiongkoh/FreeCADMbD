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

#include "Item.h"
#include "EndFrameqc.h"
#include "TranslationConstraintIJ.h"
#include "DirectionCosineConstraintIJ.h"
#include "ConstraintSet.h"
#include "ConstraintIJ.h"

namespace MbD {
    class Constraint;
    class EndFramec;
    using EndFrmsptr = std::shared_ptr<EndFramec>;

    class ConstraintSet : public ConstraintIJ
    {
        //
    public:
		ConstraintSet() {}
		ConstraintSet(const std::string& str) : ConstraintIJ(str) {}
        ConstraintSet(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintIJ(frmi, frmj) {}
        void constraintsDo(const std::function <void(std::shared_ptr<Constraint>)>& f) const;
        void initialize() override;
        void initializeGlobally() override;
        void initializeLocally() override;
        void addConstraint(std::shared_ptr<Constraint> con);
        FColDsptr aFIeJtIe() const;
        FColDsptr aFIeJtO() const;
        FColDsptr aFX() const;
        FColDsptr aTIeJtIe() const;
        FColDsptr aTIeJtO() const;
        FColDsptr aTX() const;
        virtual void connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj);
        void constraintsReport() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) override;
        void fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints) override;
        void fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) override;
        void fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineError(FColDsptr col) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillqsuddotlam(FColDsptr col) override;
        void fillqsulam(FColDsptr col) override;
        void fillpqsumu(FColDsptr col) override;
        void fillpqsumudot(FColDsptr col) override;
        void fillqsudot(FColDsptr col) override;
        void fillqsudotWeights(DiagMatDsptr diagMat) override;
        void fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) override;
        void fillVelICError(FColDsptr col) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        FColDsptr jointForceI() const;
        FColDsptr jointTorqueI() const;
        void postDynCorrectorIteration() override;
        void postDynOutput() override;
        void postDynPredictor() override;
        void postDynStep() override;
        void postInput() override;
        void postPosIC() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void preDyn() override;
        void prePosIC() override;
        void prePosKine() override;
        void preVelIC() override;
        void reactivateRedundantConstraints() override;
        void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos) override;
        void setqsuddotlam(FColDsptr col) override;
        void setqsudotlam(FColDsptr col) override;
        void setqsulam(FColDsptr col) override;
        std::shared_ptr<StateData> stateData() override;
        void useEquationNumbers() override;
        std::string constraintSpecs();
        void setpqsumu(FColDsptr col) override;
        void setpqsumudot(FColDsptr col) override;
        void setpqsumuddot(FColDsptr col) override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void preDynOutput() override;

        std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> constraints;

    };
}
