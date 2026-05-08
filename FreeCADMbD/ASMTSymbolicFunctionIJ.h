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
        virtual std::shared_ptr<KinematicIJ> mbdKineIeJeWith(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJqct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJqct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJqct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJqc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJqct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJqc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual void withFrmIFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        void createMbD() override;
        virtual double asmtUnit();

        std::shared_ptr<ASMTItemIJ> geoIJ;
    };
}
