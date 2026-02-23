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
        void fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) override;
        void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos) override;
        void constraintsReport() override;
        void fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) override;
        void fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) override;
        void reactivateRedundantConstraints();
    };
}