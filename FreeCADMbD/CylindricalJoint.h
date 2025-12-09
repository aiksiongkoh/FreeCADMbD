/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "InLineJoint.h"

namespace MbD {
    class CylindricalJoint : public InLineJoint
    {
        //eFrmI eFrmJ constraints friction 
    public:
        CylindricalJoint() {}
        CylindricalJoint(const std::string& str) : InLineJoint(str) {}
        static std::shared_ptr<CylindricalJoint> With();
        static std::shared_ptr<CylindricalJoint> With(const std::string& str);
        
        void initializeGlobally() override;
    };
}

