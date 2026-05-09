/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTSymbolicFunction.h"
#include "KinematicIeJe.h"

namespace MbD {
    class ASMTSymbolicFunctionIJ : public ASMTSymbolicFunction
    {
        //
    public:
        ASMTSymbolicFunctionIJ() {}
        ASMTSymbolicFunctionIJ(std::shared_ptr<ASMTItemIJ> itemIJ);
        static std::shared_ptr<ASMTSymbolicFunctionIJ> With();

        virtual std::shared_ptr<KinematicIeJe> mbdClassNew();
        virtual std::shared_ptr<KinematicIeJe> mbdKineIeJeWith(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJqct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJqct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJqct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJqc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJqct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJqc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJct(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJc(EndFrmsptr frmi, EndFrmsptr frmj);
        virtual void withFrmIFrmJ(EndFrmsptr frmi, EndFrmsptr frmj);
        void createMbD() override;
        virtual double asmtUnit();

        std::shared_ptr<ASMTItemIJ> geoIJ;
    };
}
