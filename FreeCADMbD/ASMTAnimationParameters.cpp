/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTAnimationParameters.h"

using namespace MbD;

std::shared_ptr<ASMTAnimationParameters> ASMTAnimationParameters::With()
{
    auto inst = std::make_shared<ASMTAnimationParameters>();
    inst->initialize();
    return inst;
}

void ASMTAnimationParameters::initialize()
{
    nframe = 1000000;
    icurrent = 1;
    istart = 1;
    iend = 1000000;
    isForward = true;
    framesPerSecond = 30;
}

void ASMTAnimationParameters::parseASMT(std::vector<std::string>& lines)
{
    //size_t nframe, icurrent, istart, iend, framesPerSecond;
    //bool isForward;
    auto pos = lines[0].find_first_not_of("\t");
    auto leadingTabs = lines[0].substr(0, pos);
    assert(lines[0] == (leadingTabs + "nframe"));
    lines.erase(lines.begin());
    nframe = readSize_t(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "icurrent"));
    lines.erase(lines.begin());
    icurrent = readSize_t(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "istart"));
    lines.erase(lines.begin());
    istart = readSize_t(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "iend"));
    lines.erase(lines.begin());
    iend = readSize_t(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "isForward"));
    lines.erase(lines.begin());
    isForward = readBool(lines[0]);
    lines.erase(lines.begin());
    assert(lines[0] == (leadingTabs + "framesPerSecond"));
    lines.erase(lines.begin());
    framesPerSecond = readSize_t(lines[0]);
    lines.erase(lines.begin());

}

void ASMTAnimationParameters::storeOnLevel(std::ofstream& os, size_t level)
{
    storeOnLevelString(os, level, "AnimationParameters");
    storeOnLevelString(os, level + 1, "nframe");
    storeOnLevelSize_t(os, level + 2, nframe);
    storeOnLevelString(os, level + 1, "icurrent");
    storeOnLevelSize_t(os, level + 2, icurrent);
    storeOnLevelString(os, level + 1, "istart");
    storeOnLevelSize_t(os, level + 2, istart);
    storeOnLevelString(os, level + 1, "iend");
    storeOnLevelSize_t(os, level + 2, iend);
    storeOnLevelString(os, level + 1, "isForward");
    storeOnLevelBool(os, level + 2, isForward);
    storeOnLevelString(os, level + 1, "framesPerSecond");
    storeOnLevelSize_t(os, level + 2, framesPerSecond);
}

std::string ASMTAnimationParameters::reportComparisonWith(std::shared_ptr<ASMTItem> otherItem)
{
    auto report = ASMTItem::reportComparisonWith(otherItem);
    if (!report.empty()) {
        return report;
    }
    auto other = std::dynamic_pointer_cast<ASMTAnimationParameters>(otherItem);
    if (!other) {
        return fullName("") + " comparison item is not an ASMTAnimationParameters.\n";
    }

    auto sizeReport = [this](const std::string& label, size_t value, size_t otherValue) {
        if (value != otherValue) {
            return fullName("") + " " + label + " " + std::to_string(value) + " != " + std::to_string(otherValue) + "\n";
        }
        return std::string{};
    };
    report = sizeReport("nframe", nframe, other->nframe);
    if (!report.empty()) return report;
    report = sizeReport("icurrent", icurrent, other->icurrent);
    if (!report.empty()) return report;
    report = sizeReport("istart", istart, other->istart);
    if (!report.empty()) return report;
    report = sizeReport("iend", iend, other->iend);
    if (!report.empty()) return report;
    if (isForward != other->isForward) {
        return fullName("") + " isForward differs.\n";
    }
    return sizeReport("framesPerSecond", framesPerSecond, other->framesPerSecond);
}
