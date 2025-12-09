/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTSymbolicFunction.h"
#include "KinematicIJ.h"

namespace MbD {
    class ASMTSymbolicFunctionIJ : public ASMTSymbolicFunction
    {
        //
    public:
        ASMTSymbolicFunctionIJ() {}
        ASMTSymbolicFunctionIJ(std::shared_ptr<ASMTItemIJ> itemIJ);
        static std::shared_ptr<ASMTSymbolicFunctionIJ> With();

        virtual std::shared_ptr<KinematicIJ> mbdClassNew();
        virtual void withFrmIFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        void createMbD() override;
        virtual double asmtUnit();

        std::shared_ptr<ASMTItemIJ> geoIJ;
    };
}
