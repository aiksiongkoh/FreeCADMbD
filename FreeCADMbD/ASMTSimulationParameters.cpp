/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTSimulationParameters.h"
#include "Numeric.h"

#include <algorithm>
#include <cmath>

using namespace MbD;

std::shared_ptr<ASMTSimulationParameters> ASMTSimulationParameters::With()
{
    auto inst = std::make_shared<ASMTSimulationParameters>();
    inst->initialize();
    return inst;
}

void ASMTSimulationParameters::initialize()
{
    // Do nothing.
}

void ASMTSimulationParameters::parseASMT(std::vector<std::string> &lines)
{
    // tstart, tend, hmin, hmax, hout, errorTol;

    size_t pos = lines[0].find_first_not_of("\t");
    auto leadingTabs = lines[0].substr(0, pos);
    assert(lines[0] == (leadingTabs + "tstart"));
    lines.erase(lines.begin());
    tstart = readDouble(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "tend"));
    lines.erase(lines.begin());
    tend = readDouble(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "hmin"));
    lines.erase(lines.begin());
    hmin = readDouble(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "hmax"));
    lines.erase(lines.begin());
    hmax = readDouble(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "hout"));
    lines.erase(lines.begin());
    hout = readDouble(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "errorTol"));
    lines.erase(lines.begin());
    seterrorTol(readDouble(lines[0]));
    lines.erase(lines.begin());
}

void ASMTSimulationParameters::settstart(double t)
{
    tstart = t;
}

void ASMTSimulationParameters::settend(double t)
{
    tend = t;
}

void ASMTSimulationParameters::sethmin(double h)
{
    hmin = h;
}

void ASMTSimulationParameters::sethmax(double h)
{
    hmax = h;
}

void ASMTSimulationParameters::sethout(double h)
{
    hout = h;
}

void ASMTSimulationParameters::seterrorTol(double tol)
{
    errorTol = tol;
    errorTolPosKine = tol;
    errorTolAccKine = tol;
    corAbsTol = tol;
    corRelTol = tol;
    intAbsTol = tol;
    intRelTol = tol;
}

void ASMTSimulationParameters::setAllTolForNDigit(int nDigit)
{
    const auto tol = std::pow(10.0, -nDigit);
    seterrorTol(tol * tol);
    hmin = tol * tol;
}

void ASMTSimulationParameters::setmaxIter(size_t maxIter)
{
    iterMaxPosKine = maxIter;
    iterMaxAccKine = maxIter;
}

void ASMTSimulationParameters::storeOnLevel(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "SimulationParameters");
    storeOnLevelString(os, level + 1, "tstart");
    storeOnLevelDouble(os, level + 2, tstart);
    storeOnLevelString(os, level + 1, "tend");
    storeOnLevelDouble(os, level + 2, tend);
    storeOnLevelString(os, level + 1, "hmin");
    storeOnLevelDouble(os, level + 2, hmin);
    storeOnLevelString(os, level + 1, "hmax");
    storeOnLevelDouble(os, level + 2, hmax);
    storeOnLevelString(os, level + 1, "hout");
    storeOnLevelDouble(os, level + 2, hout);
    storeOnLevelString(os, level + 1, "errorTol");
    storeOnLevelDouble(os, level + 2, errorTol);
}

std::string ASMTSimulationParameters::reportComparisonWith(std::shared_ptr<ASMTItem> otherItem)
{
    auto report = ASMTItem::reportComparisonWith(otherItem);
    if (!report.empty()) {
        return report;
    }
    auto other = std::dynamic_pointer_cast<ASMTSimulationParameters>(otherItem);
    if (!other) {
        return fullName("") + " comparison item is not an ASMTSimulationParameters.\n";
    }

    auto doubleReport = [this](const std::string& label, double value, double otherValue) {
        if (!Numeric::equaltol(value, otherValue, 1.0e-9)) {
            return fullName("") + " " + label + " " + std::to_string(value) + " != " + std::to_string(otherValue) + "\n";
        }
        return std::string{};
    };
    auto sizeReport = [this](const std::string& label, size_t value, size_t otherValue) {
        if (value != otherValue) {
            return fullName("") + " " + label + " " + std::to_string(value) + " != " + std::to_string(otherValue) + "\n";
        }
        return std::string{};
    };

    report = doubleReport("tstart", tstart, other->tstart);
    if (!report.empty()) return report;
    report = doubleReport("tend", tend, other->tend);
    if (!report.empty()) return report;
    report = doubleReport("hmin", hmin, other->hmin);
    if (!report.empty()) return report;
    report = doubleReport("hmax", hmax, other->hmax);
    if (!report.empty()) return report;
    report = doubleReport("hout", hout, other->hout);
    if (!report.empty()) return report;
    report = doubleReport("errorTol", errorTol, other->errorTol);
    if (!report.empty()) return report;
    report = doubleReport("errorTolPosKine", errorTolPosKine, other->errorTolPosKine);
    if (!report.empty()) return report;
    report = doubleReport("errorTolAccKine", errorTolAccKine, other->errorTolAccKine);
    if (!report.empty()) return report;
    report = doubleReport("corAbsTol", corAbsTol, other->corAbsTol);
    if (!report.empty()) return report;
    report = doubleReport("corRelTol", corRelTol, other->corRelTol);
    if (!report.empty()) return report;
    report = doubleReport("intAbsTol", intAbsTol, other->intAbsTol);
    if (!report.empty()) return report;
    report = doubleReport("intRelTol", intRelTol, other->intRelTol);
    if (!report.empty()) return report;
    report = doubleReport("translationLimit", translationLimit, other->translationLimit);
    if (!report.empty()) return report;
    report = doubleReport("rotationLimit", rotationLimit, other->rotationLimit);
    if (!report.empty()) return report;
    report = sizeReport("iterMaxPosKine", iterMaxPosKine, other->iterMaxPosKine);
    if (!report.empty()) return report;
    report = sizeReport("iterMaxAccKine", iterMaxAccKine, other->iterMaxAccKine);
    if (!report.empty()) return report;
    report = sizeReport("iterMaxDyn", iterMaxDyn, other->iterMaxDyn);
    if (!report.empty()) return report;
    return sizeReport("orderMax", orderMax, other->orderMax);
}
