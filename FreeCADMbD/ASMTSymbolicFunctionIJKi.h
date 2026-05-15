/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTSymbolicFunctionIJ.h"

namespace MbD {
    class ASMTSymbolicFunctionIJKi : public ASMTSymbolicFunctionIJ
    {
        //
    public:
        static std::shared_ptr<ASMTSymbolicFunctionIJKi> With();
        void createMbD() override;
        virtual std::shared_ptr<KinematicIeJe> kinematicWith(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);

        std::string markerKSign;
        std::shared_ptr<ASMTMarker> markerK;
        size_t axisK = SIZE_MAX;
    };
}

