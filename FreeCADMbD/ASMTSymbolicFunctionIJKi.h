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
        virtual std::shared_ptr<KinematicIeJe> mbdKineIJaxisWith(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIJKaxisKWith(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqctJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIqcJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIctJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIeJe> mbdKineIcJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);

        std::string markerKSign;
        std::shared_ptr<ASMTMarker> markerK;
        size_t axisK = SIZE_MAX;
    };
}

