/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Kinematic.h"

namespace MbD {
    class SpatialContainerFrame;
    class EndFramec;
    using EndFrmsptr = std::shared_ptr<EndFramec>;

    class KinematicIJ : public Kinematic
    {
        //eFrmI eFrmJ 
    public:
        KinematicIJ() : Kinematic() {}
        KinematicIJ(EndFrmsptr frmi, EndFrmsptr frmj) : eFrmI(frmi), eFrmJ(frmj), Kinematic() {}
        static std::shared_ptr<KinematicIJ> With();
        static std::shared_ptr<KinematicIJ> With(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual void withFrmIFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual void withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        virtual void withFrmIFrmJfrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);
        virtual void withFrmIFrmJFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis);

        void initializeLocally() override;
        void initializeGlobally() override;

        bool isKineIJ() override;
        virtual void calcvalue();
        virtual void calcpvaluepXI();
        virtual void calcpvaluepEI();
        virtual void calcppvaluepXIpXI();
        virtual void calcppvaluepXIpEI();
        virtual void calcppvaluepEIpEI();
        virtual void calcpvaluepXJ();
        virtual void calcpvaluepEJ();
        virtual void calcppvaluepXIpXJ();
        virtual void calcppvaluepXIpEJ();
        virtual void calcppvaluepEIpXJ();
        virtual void calcppvaluepEIpEJ();
        virtual void calcppvaluepXJpXJ();
        virtual void calcppvaluepXJpEJ();
        virtual void calcppvaluepEJpEJ();
        virtual void calcpvaluepXK();
        virtual void calcpvaluepEK();
        virtual void calcppvaluepXIpEK();
        virtual void calcppvaluepEIpEK();
        virtual void calcppvaluepXJpEK();
        virtual void calcppvaluepEJpEK();
        virtual void calcppvaluepEKpEK();
        virtual void calcpvaluept();
        virtual void calcppvaluepXIpt();
        virtual void calcppvaluepEIpt();
        virtual void calcppvaluepXJpt();
        virtual void calcppvaluepEJpt();
        virtual void calcppvaluepXKpt();
        virtual void calcppvaluepEKpt();
        virtual void calcppvalueptpt();

        FColDsptr getrIeJeO();
        virtual FRowDsptr pvaluepX(SpatialContainerFrame* partFrame);
        virtual FRowDsptr pvaluepE(SpatialContainerFrame* partFrame);
        virtual FRowDsptr pvaluepXI();
        virtual FRowDsptr pvaluepEI();
        virtual FMatDsptr ppvaluepXIpXI();
        virtual FMatDsptr ppvaluepXIpEI();
        virtual FMatDsptr ppvaluepEIpEI();
        virtual FRowDsptr pvaluepXJ();
        virtual FRowDsptr pvaluepEJ();
        virtual FMatDsptr ppvaluepXIpXJ();
        virtual FMatDsptr ppvaluepXIpEJ();
        virtual FMatDsptr ppvaluepEIpXJ();
        virtual FMatDsptr ppvaluepEIpEJ();
        virtual FMatDsptr ppvaluepXJpXJ();
        virtual FMatDsptr ppvaluepXJpEJ();
        virtual FMatDsptr ppvaluepEJpEJ();
        virtual FRowDsptr pvaluepXK();
        virtual FRowDsptr pvaluepEK();
        virtual FMatDsptr ppvaluepXIpEK();
        virtual FMatDsptr ppvaluepEIpEK();
        virtual FMatDsptr ppvaluepXJpEK();
        virtual FMatDsptr ppvaluepEJpEK();
        virtual FMatDsptr ppvaluepEKpEK();
        virtual FMatDsptr puIeJeOpEI();
        virtual FMatDsptr puIeJeOpXI();
        virtual FMatDsptr puIeJeOpEJ();
        virtual FMatDsptr puIeJeOpXJ();
        virtual double pvaluept();
        virtual double ppvalueptpt();
        virtual FRowDsptr ppvaluepXIpt();
        virtual FRowDsptr ppvaluepEIpt();
        virtual FRowDsptr ppvaluepXJpt();
        virtual FRowDsptr ppvaluepEJpt();
        virtual FRowDsptr ppvaluepXKpt();
        virtual FRowDsptr ppvaluepEKpt();
        virtual double value() override;
        SpatialContainerFrame* partFrameI();
        SpatialContainerFrame* partFrameJ();
        EndFrmsptr geteFrmI() override { return eFrmI; }
        EndFrmsptr geteFrmJ() override { return eFrmJ; }

        EndFrmsptr eFrmI, eFrmJ;
        SpatialContainerFrame* prtFrmI = nullptr;
        SpatialContainerFrame* prtFrmJ = nullptr;
        bool has_qI = false;
        bool has_qJ = false;
    };
}

