/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "SymbolicParser.h"
#include "ASMTForceTorque.h"
#include "ASMTSymbolicFunctionIJ.h"

namespace MbD {
    class FunctionParser : public SymbolicParser
    {
        //
    public:
        static std::shared_ptr<FunctionParser> With();
        
        void initgeoIJs();
        bool geoIJ();
        bool displacement();
        bool velocity();
        bool force();
        bool namedFunction() override;
        std::shared_ptr<std::map<std::string, std::shared_ptr<ASMTSymbolicFunctionIJ>>> geoIJs;
    };
}
