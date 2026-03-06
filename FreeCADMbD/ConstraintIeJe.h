/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Constraint.h"
#include "DispIeJeO.h"

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
        virtual void useUniqueDispIeJeO();
        virtual void useUniqueDispIeJeKe();

        void postInput() override;
        void simUpdateAll() override;

        void prePosIC() override;
        void postPosICIteration() override;

        void preVelIC() override;

        void preAccIC() override;

        void preDyn() override;
        void preDynOutput() override;
        void addToJointForceJ(FColDsptr col) override;
        void addToJointTorqueJ(FColDsptr col) override;

        virtual void calcG() = 0;
        virtual void calcpGpXI();
        virtual void calcpGpEI();
        virtual void calcpGpXJ();
        virtual void calcpGpEJ();
        virtual void calcppGpXIpXI();
        virtual void calcppGpXIpEI();
        virtual void calcppGpXIpXJ();
        virtual void calcppGpXIpEJ();
        virtual void calcppGpEIpEI();
        virtual void calcppGpEIpXJ();
        virtual void calcppGpEIpEJ();
        virtual void calcppGpXJpXJ();
        virtual void calcppGpXJpEJ();
        virtual void calcppGpEJpEJ();
        EndFrmsptr getfrmIe() { return frmIe; }
        EndFrmsptr getfrmJe() { return frmJe; }
        FColDsptr getrIeJeO();
        virtual ConstraintType type() override = 0 ;
        virtual std::string constraintSpec() override = 0;



        EndFrmsptr frmIe, frmJe;
        std::shared_ptr<DispIeJeO> dispIeJeO;
    };
}

