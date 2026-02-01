/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueIJ.h"

namespace MbD {
    class ForceTorqueGeneral : public ForceTorqueIJ
    {
    public:
        ForceTorqueGeneral() {}
        ForceTorqueGeneral(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk) : eFrmK(frmk), ForceTorqueIJ(frmi, frmj) {}
        static std::shared_ptr<ForceTorqueGeneral> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);

        void initialize() override;
        FColDsptr aFX() const override;
        FColDsptr aTX() const override;
        void calcPostDynCorrectorIteration() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillStaticError(FColDsptr col) override;
        void fillStaticJacob(SpMatDsptr mat) override;
        void setforceFunctions(FColsptr<Symsptr> col);
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
        void simUpdateAll() override;
        void settorqueFunctions(FColsptr<Symsptr> col);
        void useEquationNumbers() override;
        void calcaFIeKe();
        void calcaTIeKe();
        void calcaFIeO() override;
        void calcpFIeOpX(SpatialContainerFrame* partFrame) override;
        void calcpFIeOpE(SpatialContainerFrame* partFrame) override;
        void calcpFIeOpXdot(SpatialContainerFrame* partFrame) override;
        void calcpFIeOpEdot(SpatialContainerFrame* partFrame) override;
        void calcpFIeOpEK();
        void calcpFJeOpEK();

        void calcaTIeO() override;
        void calcpTIeOpX(SpatialContainerFrame* partFrame) override;
        void calcpTIeOpE(SpatialContainerFrame* partFrame) override;
        void calcpTIeOpXdot(SpatialContainerFrame* partFrame) override;
        void calcpTIeOpEdot(SpatialContainerFrame* partFrame) override;
        void calcpTIeOpEK();
        void calcpTJeOpEK();
        void calcpQXIpEK();
        void calcpQEIpEK();
        void calcpQXJpEK();
        void calcpQEJpEK();
        FColDsptr getaFIeK() const;
        FColDsptr getaTIeK() const;

        EndFrmsptr eFrmK;
        size_t iqEK = SIZE_MAX;
        FColDsptr aFIeKe;
        FColDsptr aTIeKe;
        FMatDsptr aAOKe;
        FMatDsptr pFIeKepXI;
        FMatDsptr pFIeKepEI;
        FMatDsptr pFIeKepXJ;
        FMatDsptr pFIeKepEJ;
        FMatDsptr pTIeKepXI;
        FMatDsptr pTIeKepEI;
        FMatDsptr pTIeKepXJ;
        FMatDsptr pTIeKepEJ;

        FMatDsptr pFIeOpEK;
        FMatDsptr pFJeOpEK;
        FMatDsptr pTIeOpEK;
        FMatDsptr pTJeOpEK;

        FMatDsptr pQXIpXK;
        FMatDsptr pQXIpEK;
        FMatDsptr pQEIpXK;
        FMatDsptr pQEIpEK;
        FMatDsptr pQXJpXK;
        FMatDsptr pQXJpEK;
        FMatDsptr pQEJpXK;
        FMatDsptr pQEJpEK;

    };
}


