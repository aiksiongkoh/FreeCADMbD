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
        virtual std::shared_ptr<KinematicIJ> mbdKineIJaxisWith(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIJKaxisKWith(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqctJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIqcJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIctJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);
        virtual std::shared_ptr<KinematicIJ> mbdKineIcJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK);

        std::string markerKSign;
        std::shared_ptr<ASMTMarker> markerK;
        size_t axisK = SIZE_MAX;
    };
}

