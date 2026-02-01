/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Item.h"
#include "ForceFunctionParser.h"

namespace MbD {
    class ForceTorqueItem : public Item
    {
        //
    public:
        ForceTorqueItem() {}
        ForceTorqueItem(const std::string& str) : Item(str) {}
        
        void fillStaticError(FColDsptr col) override;
        void fillStaticJacob(SpMatDsptr mat) override;
        void postAccICIteration() override;
        void postCollisionCorrectorIteration() override;
        void postCollisionPredictor() override;
        virtual FColDsptr getFTIeO() const;
        EndFrmsptr geteFrmI() override { return owner->geteFrmI(); }
        EndFrmsptr geteFrmJ() override { return owner->geteFrmJ(); }
        EndFrmsptr geteFrmK() override { return owner->geteFrmK(); }
        virtual double getTension() { return 0.0; }
        virtual double getTwist() { return 0.0; }
        virtual void setTension(Symsptr formula) {}
        virtual void setTwist(Symsptr formula) {}
        virtual FColDsptr getForceComponents(FColsptr<Symsptr> col) { return nullptr; }
        virtual FColDsptr getTorqueComponents(FColsptr<Symsptr> col) { return nullptr; }
        virtual void setForceFunctions(FColsptr<Symsptr> col) {}
        virtual void setTorqueFunctions(FColsptr<Symsptr> col) {}

    };
}

