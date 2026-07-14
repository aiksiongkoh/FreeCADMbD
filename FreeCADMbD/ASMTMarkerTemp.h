/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTMarker.h"
#include "ASMTPart.h"
#include "FullColumn.h"
#include "FullMatrix.h"
#include "DiagonalMatrix.h"

namespace MbD {
    class ASMTMarkerTemp : public ASMTMarker
    {
        //
    public:
        ASMTMarkerTemp() {}
        static std::shared_ptr<ASMTMarkerTemp> With();
        void initialize() override;

        void parseASMT(std::vector<std::string>& lines) override;
        void createMbD() override;
        void setMass(double mass);
        void setDensity(double density);
        void setMomentOfInertias(DiagMatDsptr momentOfInertias);
        FColDsptr rpmp() override;
        FMatDsptr aApm() override;

        // Overloads to simplify syntax.
        void setMomentOfInertias(double a, double b, double c);
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void zeroMass();
        std::string reportComparisonWith(std::shared_ptr<ASMTItem> other) override;

        double mass = 1.0;
        double density = 10.0;
        DiagMatDsptr momentOfInertias = DiagonalMatrix<double>::With(ListD{ 1.0, 2.0, 3.0 });

    };
}

