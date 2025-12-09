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
        
        virtual void forceOnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual void torqueOnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        void fillStaticError(FColDsptr col) override;
        void fillStaticJacob(SpMatDsptr mat) override;
        void postAccICIteration() override;
        void postCollisionCorrectorIteration() override;
        void postCollisionPredictor() override;
        virtual FColDsptr getFTIeO() const;

    };
}

