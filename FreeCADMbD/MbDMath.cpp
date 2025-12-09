/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "MbDMath.h"
#include <cassert>

using namespace MbD;

std::shared_ptr<MbDMath> MbDMath::With()
{
    auto inst = std::make_shared<MbDMath>();
    //inst->initialize();
    return inst;
}

void MbDMath::noop()
{
    //No Operations
}

std::string MbDMath::xyzFromInt(int i)
{
    switch (i) {
        case 0:
            return "x";    
        case 1:
            return "y";
        case 2:
            return "z";
        default:
            return std::to_string(i);
    }
}

std::string MbDMath::XYZFromInt(int i)
{
    switch (i) {
    case 0:
        return "X";
    case 1:
        return "Y";
    case 2:
        return "Z";
    default:
        return std::to_string(i);
    }
}
