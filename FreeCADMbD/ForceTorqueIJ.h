/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"

namespace MbD {
    class EndFramec;
    using EndFrmsptr = std::shared_ptr<EndFramec>;

    class ForceTorqueIJ : public ForceTorqueItem
    {
    public:
        ForceTorqueIJ() {}
        ForceTorqueIJ(const std::string& str) : ForceTorqueItem(str) {}
        ForceTorqueIJ(EndFrmsptr frmi, EndFrmsptr frmj) : eFrmI(frmi), eFrmJ(frmj), ForceTorqueItem() {}

        virtual FColDsptr aFX() const;
        virtual FColDsptr aTX() const;
        EndFrmsptr geteFrmI() override { return eFrmI; }
        EndFrmsptr geteFrmJ() override { return eFrmJ; }

        EndFrmsptr eFrmI, eFrmJ;
    };
}

