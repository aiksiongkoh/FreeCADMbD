/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueIJ.h"
#include "MarkerFrame.h"
#include "DistIecJec.h"

namespace MbD {
    class ForceTorqueInLine : public ForceTorqueIJ
    {
        //
    public:
        ForceTorqueInLine(EndFrmsptr frmi, EndFrmsptr frmj) : ForceTorqueIJ(frmi, frmj) {}
        static std::shared_ptr<ForceTorqueInLine> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void simUpdateAll() override;
        void calcuIeJeO();
        void calctension();
        void calctwist();
        void calcaFIeO() override;
        void calcpFIeOpX(SpatialContainerFrame* partFrame) override;
        void calcpFIeOpE(SpatialContainerFrame* partFrame) override;
        void calcpFIeOpXdot(SpatialContainerFrame* partFrame) override;
        void calcpFIeOpEdot(SpatialContainerFrame* partFrame) override;
        void calcaTIeO() override;
        void calcpTIeOpX(SpatialContainerFrame* partFrame) override;
        void calcpTIeOpE(SpatialContainerFrame* partFrame) override;
        void calcpTIeOpXdot(SpatialContainerFrame* partFrame) override;
        void calcpTIeOpEdot(SpatialContainerFrame* partFrame) override;
        void postDynCorrectorIteration() override;
        void postDynOutput() override;
        void postAccICIteration() override;
        void preDynOutput() override;
        void postDynPredictor() override;
        void preAccIC() override;
        void postInput() override;
        void initializeLocally() override;
        void initializeGlobally() override;
        void fillAccICIterError(FColDsptr col) override;
        void fillAccICIterJacob(SpMatDsptr mat) override;

        double getTension() override;
        double getTwist() override;
        void initialize() override;
        void setTension(Symsptr formula) override;
        void setTwist(Symsptr formula) override;
        void useEquationNumbers() override;

        std::shared_ptr<DistIecJec> distIeJe;
        FColDsptr uIeJeO;
        FMatDsptr puIeJeOpXI;
        FMatDsptr puIeJeOpEI;
        FMatDsptr puIeJeOpXJ;
        FMatDsptr puIeJeOpEJ;
        double tension;
        FRowDsptr ptensionpXI;
        FRowDsptr ptensionpEI;
        FRowDsptr ptensionpXJ;
        FRowDsptr ptensionpEJ;
        double twist;
        FRowDsptr ptwistXI;
        FRowDsptr ptwistEI;
        FRowDsptr ptwistXJ;
        FRowDsptr ptwistEJ;
    };
}
