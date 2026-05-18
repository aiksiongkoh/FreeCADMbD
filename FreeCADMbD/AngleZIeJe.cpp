/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cmath>
#include <numbers>

#include <iostream>
#include "AngleZIeJe.h"
#include "Numeric.h"
#include "AngleZIeJeq.h"
#include "AngleZIeqJe.h"
#include "AngleZIeqJeq.h"
#include "EndFrameqt.h"
#include "EndFrameq.h"
#include "EndFramet.h"
#include "EndFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

void AngleZIeJe::postStaticIteration()
{
    aA00IeJe->postStaticIteration();
    aA10IeJe->postStaticIteration();
    KinematicIeJe::postStaticIteration();
}

void AngleZIeJe::preStatic()
{
    aA00IeJe->preStatic();
    aA10IeJe->preStatic();
    KinematicIeJe::preStatic();
}

std::shared_ptr<AngleZIeJe> AngleZIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
    const auto factoryName = "AngleZIeJe::With";
    std::shared_ptr<AngleZIeJe> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi))
    {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameq>(frmi))
    {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj))
        {
            inst = std::make_shared<AngleZIeqJeq>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj))
        {
            inst = std::make_shared<AngleZIeqJe>(frmi, frmj);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi))
    {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrame>(frmi))
    {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj))
        {
            inst = std::make_shared<AngleZIeJeq>(frmi, frmj);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj))
        {
            throwUnsupportedFrameCombination(factoryName);
        }
    }
    assert(inst);
    inst->initialize();
    return inst;
}

void AngleZIeJe::initialize()
{
    KinematicIeJe::initialize();
    this->init_aAijIeJe();
}

void AngleZIeJe::simUpdateAll()
{
    // thezIeJe = atan2(sthez, cthez)
    // thezIeJe = atan2(aA10IeJe, aA00IeJe)
    auto cthez = aA00IeJe->value();
    auto sthez = aA10IeJe->value();
    auto sumOfSquares = cthez * cthez + (sthez * sthez);
    auto diffOfSquares = sthez * sthez - (cthez * cthez);
    auto sumOfSquaresSquared = sumOfSquares * sumOfSquares;
    auto thez0to2pi = Numeric::arcTan0to2piYoverX(sthez, cthez);
    thez = std::round((thez - thez0to2pi) / (2.0 * std::numbers::pi)) * (2.0 * std::numbers::pi) + thez0to2pi;
    cosOverSSq = cthez / sumOfSquares;
    sinOverSSq = sthez / sumOfSquares;
    twoCosSinOverSSqSq = 2.0 * cthez * sthez / sumOfSquaresSquared;
    dSqOverSSqSq = diffOfSquares / sumOfSquaresSquared;
}

void AngleZIeJe::init_aAijIeJe()
{
    // Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

void AngleZIeJe::initializeGlobally()
{
    aA00IeJe->initializeGlobally();
    aA10IeJe->initializeGlobally();
}

void AngleZIeJe::initializeLocally()
{
    KinematicIeJe::initializeLocally();
    if (!aA00IeJe)
        init_aAijIeJe();
    aA00IeJe->initializeLocally();
    aA10IeJe->initializeLocally();
}

void AngleZIeJe::postInput()
{
    aA00IeJe->postInput();
    aA10IeJe->postInput();
    if (thez == std::numeric_limits<double>::min())
    {
        auto cthez = aA00IeJe->value();
        auto sthez = aA10IeJe->value();
        if (cthez > 0.0)
        {
            thez = std::atan2(sthez, cthez);
        }
        else
        {
            thez = Numeric::arcTan0to2piYoverX(sthez, cthez);
        }
    }
    KinematicIeJe::postInput();
}

void AngleZIeJe::postPosICIteration()
{
    aA00IeJe->postPosICIteration();
    aA10IeJe->postPosICIteration();
    KinematicIeJe::postPosICIteration();
}

void AngleZIeJe::preAccIC()
{
    aA00IeJe->preAccIC();
    aA10IeJe->preAccIC();
    KinematicIeJe::preAccIC();
}

void AngleZIeJe::prePosIC()
{
    aA00IeJe->prePosIC();
    aA10IeJe->prePosIC();
    assert(thez != std::numeric_limits<double>::min());
    KinematicIeJe::prePosIC();
}

void AngleZIeJe::preVelIC()
{
    aA00IeJe->preVelIC();
    aA10IeJe->preVelIC();
    KinematicIeJe::preVelIC();
}

double AngleZIeJe::value()
{
    return thez;
}

void AngleZIeJe::postDynPredictor()
{
    aA00IeJe->postDynPredictor();
    aA10IeJe->postDynPredictor();
    KinematicIeJe::postDynPredictor();
}

void AngleZIeJe::postDynCorrectorIteration()
{
    aA00IeJe->postDynCorrectorIteration();
    aA10IeJe->postDynCorrectorIteration();
    KinematicIeJe::postDynCorrectorIteration();
}

void AngleZIeJe::preDynOutput()
{
    aA00IeJe->preDynOutput();
    aA10IeJe->preDynOutput();
    KinematicIeJe::preDynOutput();
}

void AngleZIeJe::postDynOutput()
{
    aA00IeJe->postDynOutput();
    aA10IeJe->postDynOutput();
    KinematicIeJe::postDynOutput();
}
