/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ForceTorqueData.h"

using namespace MbD;

std::shared_ptr<ForceTorqueData> ForceTorqueData::With()
{
    auto inst = std::make_shared<ForceTorqueData>();
    inst->initialize();
    return inst;
}

std::ostream& ForceTorqueData::printOn(std::ostream& s) const
{
    s << "aFIO = " << *aFIO << std::endl;
    s << "aTIO = " << *aTIO << std::endl;
    return s;
}
