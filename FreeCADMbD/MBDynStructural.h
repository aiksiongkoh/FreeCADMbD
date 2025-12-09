/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynNode.h"

namespace MbD {
    class MBDynStructural : public MBDynNode
    {
    public:
		MBDynStructural() : MBDynNode() {}
        void initialize() override;
        static std::shared_ptr<MBDynStructural> newStructural(std::string line);

        void parseMBDyn(std::string line) override;
        virtual void readPosition(std::vector<std::string>& args);
        virtual void readOrientation(std::vector<std::string>& args);
        void readVelocity(std::vector<std::string>& args);
        void readOmega(std::vector<std::string>& args);
        void createASMT() override;

        std::string strucString, baseRefName, baseNodeName;
        FColDsptr rOfO, vOfO, omeOfO;
        FMatDsptr aAOf;
    };
}
