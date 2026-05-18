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
    class EndFrame;
    
    class ConstraintIeJe : public Constraint
    {
    public:
        ConstraintIeJe() {}
        ConstraintIeJe(const std::string& str) : Constraint(str) {}
        ConstraintIeJe(EndFrmsptr frmi, EndFrmsptr frmj)
            : Constraint(), eFrmI(frmi), eFrmJ(frmj) {}
        static std::shared_ptr<ConstraintIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);
		
        void initialize() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void useUniqueDispIeJeO() override;
        void useUniqueDispIeJeKe() override;

        void postInput() override;
        void simUpdateAll() override;

        void prePosIC() override;
        void postPosICIteration() override;

        void preVelIC() override;

        void preAccIC() override;

        void preDyn() override;
        void preDynOutput() override;
        void preStatic() override;
        void addToJointForceJ(FColDsptr col) override;
        void addToJointTorqueJ(FColDsptr col) override;

        virtual void calcG();
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
        EndFrmsptr getfrmIe() { return eFrmI; }
        EndFrmsptr getfrmJe() { return eFrmJ; }
        virtual ConstraintType type() override;
        virtual std::string constraintSpec() override;
        EndFrmsptr eFrmI, eFrmJ;
        // dispIeJeO is usefull for action and reactioon calculation
        // dispIeJeO is updated at global level
        std::shared_ptr<DispIeJeO> dispIeJeO; 
        FColDsptr rIeJeO;
    };
}

