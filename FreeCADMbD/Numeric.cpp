/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cmath>
#include <numbers>
#include <stdexcept>

#include "Numeric.h"

using namespace MbD;

double Numeric::arcTan0to2piYoverX(double y, double x)
{
    //"(y/x) arcTan in the range 0 to 2*pi."
    //"Double arcTan0to2piY: 1.0d overX: 1.0d."

    if (y >= 0)
    {
        //"First and second quadrants."
        return std::atan2(y, x);
    }
    else
    {
        //"Third and forth quadrants."
        return 2.0 * std::numbers::pi + std::atan2(y, x);
    }
}

bool Numeric::equaltol(double x, double xx, double tol)
{
    return std::abs(x - xx) < tol;
}

bool Numeric::equalDigitTol(double x, double xx, size_t nDigit, double tol)
{
    if (std::abs(x) < tol && std::abs(xx) < tol)
        return true;
    auto ratio = x / xx;
    if (ratio < 0.0)
        return false; // Sign error.
    auto relDiff = ratio - 1.0;
    return std::abs(relDiff) < std::pow(10, -int(nDigit));
}

bool Numeric::anglesEqual(double a, double b, double tol)
{
    double d = std::remainder(a - b, 2.0 * std::numbers::pi); // in [-pi, pi]
    return std::abs(d) <= tol;
}
