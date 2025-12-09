/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTItemIJ.h"

namespace MbD {
    class ConstraintSet;

    class ASMTConstraintSet : public ASMTItemIJ
    {
        //
    public:
        static std::shared_ptr<ASMTConstraintSet> With();
        
        void createMbD() override;
        virtual std::shared_ptr<ConstraintSet> mbdClassNew();
        void updateFromMbD() override;
        void compareResults(AnalysisType type) override;
        void outputResults(AnalysisType type) override;
        void updateFromInputState();

    };
}

