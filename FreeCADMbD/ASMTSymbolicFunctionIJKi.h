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
        virtual void withFrmIFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
        virtual void withFrmIFrmJfrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);

        std::string markerKSign;
        std::shared_ptr<ASMTMarker> markerK;
        size_t axisK;
    };
}

