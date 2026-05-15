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
    class EndFrame;

    class KinematicVectorIeJe : public Kinematic
    {
        //eFrmI eFrmJ 
    public:
        KinematicVectorIeJe() : Kinematic() {}
        KinematicVectorIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : eFrmI(frmi), eFrmJ(frmj), Kinematic() {}
        static std::shared_ptr<KinematicVectorIeJe> With();
        static std::shared_ptr<KinematicVectorIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);

        void initializeLocally() override;
        void initializeGlobally() override;

        bool isKineIJ() override;
        virtual void calcVector();
        virtual void calcpVectorpXI();
        virtual void calcpVectorpEI();
        virtual void calcppVectorpXIpXI();
        virtual void calcppVectorpXIpEI();
        virtual void calcppVectorpEIpEI();
        virtual void calcpVectorpXJ();
        virtual void calcpVectorpEJ();
        virtual void calcppVectorpXIpXJ();
        virtual void calcppVectorpXIpEJ();
        virtual void calcppVectorpEIpXJ();
        virtual void calcppVectorpEIpEJ();
        virtual void calcppVectorpXJpXJ();
        virtual void calcppVectorpXJpEJ();
        virtual void calcppVectorpEJpEJ();
        virtual void calcpVectorpXK();
        virtual void calcpVectorpEK();
        virtual void calcppVectorpXIpEK();
        virtual void calcppVectorpEIpEK();
        virtual void calcppVectorpXJpEK();
        virtual void calcppVectorpEJpEK();
        virtual void calcppVectorpEKpEK();
        virtual void calcpVectorpt();
        virtual void calcppVectorpXIpt();
        virtual void calcppVectorpEIpt();
        virtual void calcppVectorpXJpt();
        virtual void calcppVectorpEJpt();
        virtual void calcppVectorpXKpt();
        virtual void calcppVectorpEKpt();
        virtual void calcppVectorptpt();

        virtual FColDsptr getVector();
        virtual FMatDsptr getpVectorpXI();
        virtual FMatDsptr getpVectorpEI();
        virtual FMatFColDsptr getppVectorpXIpXI();
        virtual FMatFColDsptr getppVectorpXIpEI();
        virtual FMatFColDsptr getppVectorpEIpEI();
        virtual FMatDsptr getpVectorpXJ();
        virtual FMatDsptr getpVectorpEJ();
        virtual FMatFColDsptr getppVectorpXIpXJ();
        virtual FMatFColDsptr getppVectorpXIpEJ();
        virtual FMatFColDsptr getppVectorpEIpXJ();
        virtual FMatFColDsptr getppVectorpEIpEJ();
        virtual FMatFColDsptr getppVectorpXJpXJ();
        virtual FMatFColDsptr getppVectorpXJpEJ();
        virtual FMatFColDsptr getppVectorpEJpEJ();
        virtual FMatDsptr getpVectorpXK();
        virtual FMatDsptr getpVectorpEK();
        virtual FMatFColDsptr getppVectorpXIpEK();
        virtual FMatFColDsptr getppVectorpEIpEK();
        virtual FMatFColDsptr getppVectorpXJpEK();
        virtual FMatFColDsptr getppVectorpEJpEK();
        virtual FMatFColDsptr getppVectorpEKpEK();
        virtual FMatDsptr puIeJeOpEI();
        virtual FMatDsptr puIeJeOpXI();
        virtual FMatDsptr puIeJeOpEJ();
        virtual FMatDsptr puIeJeOpXJ();
        virtual FColDsptr getpVectorpt();
        virtual FColDsptr getppVectorptpt();
        virtual FMatDsptr getppVectorpXIpt();
        virtual FMatDsptr getppVectorpEIpt();
        virtual FMatDsptr getppVectorpXJpt();
        virtual FMatDsptr getppVectorpEJpt();
        virtual FMatDsptr getppVectorpXKpt();
        virtual FMatDsptr getppVectorpEKpt();
        virtual FMatDsptr getppCompipEIpEI(size_t axis);
        virtual FMatDsptr getppCompipEJpEJ(size_t axis);
        virtual double value() override;
        EndFrmsptr geteFrmI() override { return eFrmI; }
        EndFrmsptr geteFrmJ() override { return eFrmJ; }
        virtual bool hasSameEndFrms(const std::shared_ptr<KinematicVectorIeJe> other) const;

        EndFrmsptr eFrmI, eFrmJ;
    };
}

