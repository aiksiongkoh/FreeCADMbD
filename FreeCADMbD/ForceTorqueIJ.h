/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"
#include "DistIecJec.h"
#include "ForceTorqueFunction.h"
#include "DispIeJeO.h"
#include "SpatialContainerFrame.h"

namespace MbD
{
    class EndFrame;
    using EndFrmsptr = std::shared_ptr<EndFrame>;

    class ForceTorqueIJ : public ForceTorqueItem
    {
    public:
        ForceTorqueIJ() {}
        ForceTorqueIJ(const std::string &str) : ForceTorqueItem(str) {}
        ForceTorqueIJ(EndFrmsptr frmi, EndFrmsptr frmj) : eFrmI(frmi), eFrmJ(frmj), ForceTorqueItem() {}
        ForceTorqueIJ(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk) : eFrmI(frmi), eFrmJ(frmj), ForceTorqueItem() {}

        void simUpdateAll() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillDynError(FColDsptr col) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        virtual void calcaFIeO() = 0;
        void calcaFJeO();
        virtual void calcpFIeOpX(SpatialContainerFrame *partFrame) = 0;
        virtual void calcpFIeOpE(SpatialContainerFrame *partFrame) = 0;
        virtual void calcpFIeOpXdot(SpatialContainerFrame *partFrame) = 0;
        virtual void calcpFIeOpEdot(SpatialContainerFrame *partFrame) = 0;
        void calcpFIeOpXI();
        void calcpFIeOpEI();
        void calcpFIeOpXJ();
        void calcpFIeOpEJ();
        void calcpFJeOpXI();
        void calcpFJeOpEI();
        void calcpFJeOpXJ();
        void calcpFJeOpEJ();
        void calcpFIeOpXdotI();
        void calcpFIeOpEdotI();
        void calcpFIeOpXdotJ();
        void calcpFIeOpEdotJ();
        void calcpFJeOpXdotI();
        void calcpFJeOpEdotI();
        void calcpFJeOpXdotJ();
        void calcpFJeOpEdotJ();

        virtual void calcaTIeO() = 0;
        void calcaTJeO();
        virtual void calcpTIeOpX(SpatialContainerFrame *partFrame) = 0;
        virtual void calcpTIeOpE(SpatialContainerFrame *partFrame) = 0;
        void calcpTIeOpXI();
        void calcpTIeOpEI();
        void calcpTIeOpXJ();
        void calcpTIeOpEJ();
        void calcpTJeOpXI();
        void calcpTJeOpEI();
        void calcpTJeOpXJ();
        void calcpTJeOpEJ();
        virtual void calcpTIeOpXdot(SpatialContainerFrame *partFrame) = 0;
        virtual void calcpTIeOpEdot(SpatialContainerFrame *partFrame) = 0;
        void calcpTIeOpXdotI();
        void calcpTIeOpEdotI();
        void calcpTIeOpXdotJ();
        void calcpTIeOpEdotJ();
        void calcpTJeOpXdotI();
        void calcpTJeOpEdotI();
        void calcpTJeOpXdotJ();
        void calcpTJeOpEdotJ();
        virtual FColDsptr aFX() const;
        virtual FColDsptr aTX() const;
        EndFrmsptr geteFrmI() override { return eFrmI; }
        EndFrmsptr geteFrmJ() override { return eFrmJ; }
        void setForceFunctions(FColsptr<Symsptr> col) override;
        void setTorqueFunctions(FColsptr<Symsptr> col) override;
        void initialize() override;
        void initializeGlobally() override;
        void initializeLocally() override;
        void postAccICIteration() override;
        void postCollisionCorrectorIteration() override;
        void postCollisionPredictor() override;
        void postDynCorrectorIteration() override;
        void postDynOutput() override;
        void postDynPredictor() override;
        void postInput() override;
        void postStaticIteration() override;
        void preAccIC() override;
        void preDynOutput() override;
        void preStatic() override;
        void useEquationNumbers() override;

        void calcaQXI();
        void calcaQEI();
        void calcaQXJ();
        void calcaQEJ();
        void calcpQXIpXI();
        void calcpQXIpEI();
        void calcpQXIpXJ();
        void calcpQXIpEJ();
        void calcpQEIpXI();
        void calcpQEIpEI();
        void calcpQEIpXJ();
        void calcpQEIpEJ();
        void calcpQXJpXI();
        void calcpQXJpEI();
        void calcpQXJpXJ();
        void calcpQXJpEJ();
        void calcpQEJpXI();
        void calcpQEJpEI();
        void calcpQEJpXJ();
        void calcpQEJpEJ();

        void calcpQXIpXdotI();
        void calcpQXIpEdotI();
        void calcpQXIpXdotJ();
        void calcpQXIpEdotJ();
        void calcpQEIpXdotI();
        void calcpQEIpEdotI();
        void calcpQEIpXdotJ();
        void calcpQEIpEdotJ();
        void calcpQXJpXdotI();
        void calcpQXJpEdotI();
        void calcpQXJpXdotJ();
        void calcpQXJpEdotJ();
        void calcpQEJpXdotI();
        void calcpQEJpEdotI();
        void calcpQEJpXdotJ();
        void calcpQEJpEdotJ();
        virtual void useUniqueDispIeJeO();
        virtual void useUniqueDispIeJeKe();

        EndFrmsptr eFrmI, eFrmJ;
        SpatialContainerFrame *prtFrmI = nullptr;
        SpatialContainerFrame *prtFrmJ = nullptr;
        bool has_qI = false;
        bool has_qJ = false;
        size_t iqXI = SIZE_MAX, iqEI = SIZE_MAX;
        size_t iqXJ = SIZE_MAX, iqEJ = SIZE_MAX;
        FMatDsptr prOIeOpEIT;
        FMatDsptr prOJeOpEJT;
        FMatFColDsptr pprOIeOpEIpEI;
        FMatFColDsptr pprOJeOpEJpEJ;
        FMatDsptr twoBOIT;
        FMatDsptr twoBOJT;
        FColDsptr aFIeO;
        FColDsptr aTIeO;
        FColDsptr aFJeO;
        FColDsptr aTJeO;
        FMatDsptr pFIeOpXI;
        FMatDsptr pFIeOpEI;
        FMatDsptr pFIeOpXJ;
        FMatDsptr pFIeOpEJ;
        FMatDsptr pTIeOpXI;
        FMatDsptr pTIeOpEI;
        FMatDsptr pTIeOpXJ;
        FMatDsptr pTIeOpEJ;
        FMatDsptr pFJeOpXI;
        FMatDsptr pFJeOpEI;
        FMatDsptr pFJeOpXJ;
        FMatDsptr pFJeOpEJ;
        FMatDsptr pTJeOpXI;
        FMatDsptr pTJeOpEI;
        FMatDsptr pTJeOpXJ;
        FMatDsptr pTJeOpEJ;
        FMatDsptr pFIeOpXdotI;
        FMatDsptr pFIeOpEdotI;
        FMatDsptr pFIeOpXdotJ;
        FMatDsptr pFIeOpEdotJ;
        FMatDsptr pTIeOpXdotI;
        FMatDsptr pTIeOpEdotI;
        FMatDsptr pTIeOpXdotJ;
        FMatDsptr pTIeOpEdotJ;
        FMatDsptr pFJeOpXdotI;
        FMatDsptr pFJeOpEdotI;
        FMatDsptr pFJeOpXdotJ;
        FMatDsptr pFJeOpEdotJ;
        FMatDsptr pTJeOpXdotI;
        FMatDsptr pTJeOpEdotI;
        FMatDsptr pTJeOpXdotJ;
        FMatDsptr pTJeOpEdotJ;
        FColDsptr aQXI;
        FColDsptr aQEI;
        FColDsptr aQXJ;
        FColDsptr aQEJ;
        FMatDsptr pQXIpXI;
        FMatDsptr pQXIpEI;
        FMatDsptr pQXIpXJ;
        FMatDsptr pQXIpEJ;
        FMatDsptr pQEIpXI;
        FMatDsptr pQEIpEI;
        FMatDsptr pQEIpXJ;
        FMatDsptr pQEIpEJ;
        FMatDsptr pQXJpXI;
        FMatDsptr pQXJpEI;
        FMatDsptr pQXJpXJ;
        FMatDsptr pQXJpEJ;
        FMatDsptr pQEJpXI;
        FMatDsptr pQEJpEI;
        FMatDsptr pQEJpXJ;
        FMatDsptr pQEJpEJ;
        FMatDsptr pQXIpXdotI;
        FMatDsptr pQXIpEdotI;
        FMatDsptr pQXIpXdotJ;
        FMatDsptr pQXIpEdotJ;
        FMatDsptr pQEIpXdotI;
        FMatDsptr pQEIpEdotI;
        FMatDsptr pQEIpXdotJ;
        FMatDsptr pQEIpEdotJ;
        FMatDsptr pQXJpXdotI;
        FMatDsptr pQXJpEdotI;
        FMatDsptr pQXJpXdotJ;
        FMatDsptr pQXJpEdotJ;
        FMatDsptr pQEJpXdotI;
        FMatDsptr pQEJpEdotI;
        FMatDsptr pQEJpXdotJ;
        FMatDsptr pQEJpEdotJ;
        // dispIeJeO is updated at global level
        FColDsptr rIeJeO;
        std::shared_ptr<DispIeJeO> dispIeJeO;
        std::shared_ptr<std::vector<std::shared_ptr<ForceTorqueFunction>>> forceFunctions;
        std::shared_ptr<std::vector<std::shared_ptr<ForceTorqueFunction>>> torqueFunctions;
    };
}
