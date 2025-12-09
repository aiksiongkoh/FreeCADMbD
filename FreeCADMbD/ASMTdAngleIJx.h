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
    class ASMTdAngleIJx : public ASMTAngleIJ
    {
        //
    public:
        static std::shared_ptr<ASMTdAngleIJx> With();
        std::shared_ptr<KinematicIJ> mbdClassNew() override;

    };
}
