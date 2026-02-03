/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <memory>

#include "enum.h"
#include "Item.h"

namespace MbD {
    class Constraint : public Item
    {
        //iG aG lam mu lamDeriv owner 
    public:
        Constraint() : Item() {}
        Constraint(const std::string& str) : Item(str) {}
        void initialize() override;

        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) override;
        void fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints) override;
        void fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) override;
        void fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints) override;
        void fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) override;
        void fillPosICError(FColDsptr col) override;
        void fillPosKineError(FColDsptr col) override;
        void fillDynError(FColDsptr col) override;
        void fillqsuddotlam(FColDsptr col) override;
        void fillqsulam(FColDsptr col) override;
        void fillpqsumu(FColDsptr col) override;
        void fillpqsumudot(FColDsptr col) override;
        virtual bool isRedundant();
        void postInput() override;
        void preAccIC() override;
        void preDyn() override;
        void prePosIC() override;
        void prePosKine() override;
        void reactivateRedundantConstraints() override;
        void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos) override;
        void setConstant(double value);
        void setqsudotlam(FColDsptr col) override;
        void setqsuddotlam(FColDsptr col) override;
        void setqsulam(FColDsptr col) override;
        virtual ConstraintType type();
        virtual std::string constraintSpec() = 0;
        void setpqsumu(FColDsptr col) override;
        void setpqsumudot(FColDsptr col) override;
        void setpqsumuddot(FColDsptr col) override;
        virtual void addToJointForceI(FColDsptr col);
        virtual void addToJointTorqueI(FColDsptr col);
        virtual void addToJointForceJ(FColDsptr col);
        virtual void addToJointTorqueJ(FColDsptr col);

        size_t iG = SIZE_MAX;
        double aG = 0.0;        //Constraint function
        double aConstant = 0.0;
        double lam = 0.0;        //Lambda is Lagrange Multiplier
        double mu = 0.0, lamDeriv = 0.0;
    };
}

