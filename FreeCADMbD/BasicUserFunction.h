/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <string>

#include "UserFunction.h"

namespace MbD {
    class Units;

    class BasicUserFunction : public UserFunction
    {
        //funcText myUnit units 
    public:
        BasicUserFunction() {}
        BasicUserFunction(const std::string& expression, double myUnt);
        static std::shared_ptr<BasicUserFunction> With();
        void initialize();
        
            
        std::string funcText;
        double myUnit = 1.0;
        std::shared_ptr<Units> units;
    };
}

