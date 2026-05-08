/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DistxyIeqJeq.h"

namespace MbD {
    class DistxyIeqtJeq : public DistxyIeqJeq
    {
        //pdistxypt ppdistxypXIpt ppdistxypEIpt ppdistxypXJpt ppdistxypEJpt ppdistxyptpt 
    public:
        static std::shared_ptr<DistxyIeqtJeq> With();
        //ToDo: add member functions.

    };
}

