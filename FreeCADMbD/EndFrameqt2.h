/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "EndFrameqt.h"
#include "Symbolic.h"
#include "EulerAngles.h"
#include "EulerAnglesDot.h"
#include "EulerAnglesDDot.h"

namespace MbD {
    class SymTime;

    class EndFrameqt2 : public EndFrameqt
    {
        //
    public:
        EndFrameqt2() {}
        EndFrameqt2(const std::string& str) : EndFrameqt(str) {}
        static std::shared_ptr<EndFrameqt2> With(const std::string& str);
        
        void initpthe1x2y3zptBlks() override;
        void initppthe1x2y3zptptBlks() override;
        void evalAme() override;
        void evalpAmept() override;
        void evalppAmeptpt() override;

    };
}

