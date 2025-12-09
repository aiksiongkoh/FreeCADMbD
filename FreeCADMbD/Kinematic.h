/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <memory>
#include "Item.h"

namespace MbD {
    class Kinematic : public Item
    {
    public:
        Kinematic() : Item() {}
        Kinematic(const std::string& str) : Item(str) {}
        void initialize() override;
    };

}