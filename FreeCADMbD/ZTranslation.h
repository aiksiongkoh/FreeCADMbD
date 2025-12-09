/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "PrescribedMotion.h"

namespace MbD {
    class ZTranslation : public PrescribedMotion
    {
        //
    public:
        ZTranslation() {}
        ZTranslation(const std::string& str);
        static std::shared_ptr<ZTranslation> With();
        static std::shared_ptr<ZTranslation> With(const std::string& str);

        void initializeGlobally() override;

    };
}

