/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTAngleIJ.h"

namespace MbD {
    class ASMTAngleIJz : public ASMTAngleIJ
    {
        //
    public:
        static std::shared_ptr<ASMTAngleIJz> With();
        std::shared_ptr<KinematicIJ> mbdClassNew() override;

    };
}
