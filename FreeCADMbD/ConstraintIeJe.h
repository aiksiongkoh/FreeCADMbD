/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Constraint.h"
#include "EndFrameqc.h"
#include "DispIecJecO.h"

namespace MbD {
    class EndFramec;
    using EndFrmsptr = std::shared_ptr<EndFramec>;
    
    class ConstraintIeJe : public Constraint
    {
    public:
        ConstraintIeJe() {}
        ConstraintIeJe(const std::string& str) : Constraint(str) {}
        ConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : frmIe(frmi), frmJe(frmj), Constraint() {}
        static std::shared_ptr<ConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
		
        void initialize() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void useEquationNumbers() override;
        void simUpdateAll() override;
        void fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) override;
        void fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints) override;
        void fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) override;
        void fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints) override;
        void fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) override;
        void prePosIC() override;
        void prePosKine() override;
        void preVelIC() override;
        void preAccIC() override;
        void preDyn() override;
        void preDynOutput() override;
        void postInput() override;
        void postPosICIteration() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;
        void postDynOutput() override;
        void fillPosICError(FColDsptr col) override;
        void fillPosICJacob(SpMatDsptr mat) override;
        void fillPosKineError(FColDsptr col) override;
        void fillPosKineJacob(SpMatDsptr mat) override;
        void fillVelICError(FColDsptr col) override;
        void fillVelICJacob(SpMatDsptr mat) override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void fillqsuddotlam(FColDsptr col) override;
        void fillqsulam(FColDsptr col) override;
        void fillpqsumu(FColDsptr col) override;
        void fillpqsumudot(FColDsptr col) override;
        void reactivateRedundantConstraints() override;
        void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos) override;
        void setConstant(double value);
        void setqsudotlam(FColDsptr col) override;
        void setqsuddotlam(FColDsptr col) override;
        void setqsulam(FColDsptr col) override;
        void setpqsumu(FColDsptr col) override;
        void setpqsumudot(FColDsptr col) override;
        void setpqsumuddot(FColDsptr col) override;
        virtual void calcG() = 0;
        virtual void calcpGpXI() = 0;
        virtual void calcpGpEI() = 0;
        virtual void calcpGpXJ() = 0;
        virtual void calcpGpEJ() = 0;
        virtual void calcppGpXIpXI() = 0;
        virtual void calcppGpXIpEI() = 0;
        virtual void calcppGpXIpXJ() = 0;
        virtual void calcppGpXIpEJ() = 0;
        virtual void calcppGpEIpEI() = 0;
        virtual void calcppGpEIpXJ() = 0;
        virtual void calcppGpEIpEJ() = 0;
        virtual void calcppGpXJpXJ() = 0;
        virtual void calcppGpXJpEJ() = 0;
        virtual void calcppGpEJpEJ() = 0;
        void addToJointForceI(FColDsptr col) override;
        void addToJointTorqueI(FColDsptr col) override;
        void addToJointForceJ(FColDsptr col) override;
        void addToJointTorqueJ(FColDsptr col) override;
        EndFrmsptr getfrmIe() { return frmIe; }
        EndFrmsptr getfrmJe() { return frmJe; }
        FColDsptr getrIeJeO();
        virtual ConstraintType type();
        virtual std::string constraintSpec() = 0;
        virtual bool isRedundant();



        size_t iG = SIZE_MAX;
        double aG = std::numeric_limits<double>::min();         //Constraint equation
        double aConstant = std::numeric_limits<double>::min();	//Constant in constraint equation
        double lam = std::numeric_limits<double>::min();        //Lambda is Lagrange Multiplier
        double mu = std::numeric_limits<double>::min();			//lam = muderiv to reduce DAE index
        double lamDeriv = std::numeric_limits<double>::min();	//Used in collision dynamics
        EndFrmsptr frmIe, frmJe;
        std::shared_ptr<DispIecJecO> dispIeJeO;
        size_t iqXI = SIZE_MAX, iqEI = SIZE_MAX;
        size_t iqXJ = SIZE_MAX, iqEJ = SIZE_MAX;
        FRowDsptr pGpXI, pGpEI, pGpXJ, pGpEJ;
        FMatDsptr ppGpXIpXI, ppGpXIpEI, ppGpXIpXJ, ppGpXIpEJ;
        FMatDsptr ppGpEIpEI, ppGpEIpXJ, ppGpEIpEJ;
        FMatDsptr ppGpXJpXJ, ppGpXJpEJ;
        FMatDsptr ppGpEJpEJ;
        double pGpt = std::numeric_limits<double>::min();
        FRowDsptr ppGpXIpt, ppGpEIpt, ppGpXJpt, ppGpEJpt;
        double ppGptpt = std::numeric_limits<double>::min();
    };
}

