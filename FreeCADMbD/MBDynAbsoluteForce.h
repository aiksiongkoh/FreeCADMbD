/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynForce.h"

namespace MbD {
    class MBDynAbsoluteForce : public MBDynForce
    {
    public:
        MBDynAbsoluteForce() {}
        static std::shared_ptr<MBDynAbsoluteForce> With();
        
        void parseMBDyn(std::string line) override;
        void createASMT() override;

        FColDsptr rnmn = std::make_shared<FullColumn<double>>(3);
        FMatDsptr aAnm = FullMatrix<double>::identitysptr(3);
    };
}

