/***************************************************************************
 *   Copyright (c) 2025 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "PosICDragLimitNewtonRaphson.h"
#include "SystemSolver.h"
#include "SimulationStoppingError.h"
#include "Part.h"
#include "Constraint.h"
#include <algorithm>

using namespace MbD;

std::shared_ptr<PosICDragLimitNewtonRaphson> PosICDragLimitNewtonRaphson::With()
{
    auto newtonRaphson = std::make_shared<PosICDragLimitNewtonRaphson>();
    newtonRaphson->initialize();
    return newtonRaphson;
}

void PosICDragLimitNewtonRaphson::preRun()
{
    std::string str("MbD: Assembling system with limits. ");
    system->logString(str);
    system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) { item->prePosIC(); });

}

void PosICDragLimitNewtonRaphson::initializeGlobally()
{
    AnyPosICNewtonRaphson::initializeGlobally();
    iterMax = system->iterMaxPosKine;
    dxTol = system->errorTolPosKine;
}

void PosICDragLimitNewtonRaphson::setdragParts(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts)
{
    (void) dragParts;
    throw SimulationStoppingError("To be implemented.");
}

void PosICDragLimitNewtonRaphson::run()
{
    preRun();
    system->deactivateLimits();
    if (system->limitsSatisfied()) {
        std::string str("MbD: No limits reached. ");
        system->logString(str);
        return;
    }
    auto limits = system->limits();
    std::partition(limits->begin(), limits->end(), [](auto limit) { return !limit->satisfied(); });
    //Violated limits are in front.
    for (auto it = limits->begin(); it != limits->end(); it++) {
        auto limit = *it;
        limit->activate();
        preRun();
        initializeLocally();
        initializeGlobally();
        iterate();
        postRun();
        system->deactivateLimits();
        if (system->limitsSatisfied()) return;
    }
    throw SimulationStoppingError("Limits cannot be satisfiled.");
}

void PosICDragLimitNewtonRaphson::iterate()
{
    //VectorNewtonRaphson::iterate();    //Inlined to help debugging
    iterNo = SIZE_MAX;
    fillY();
    calcyNorm();
    yNorms->push_back(yNorm);

    while (true) {
        incrementIterNo();
        fillPyPx();
        //outputSpreadsheet();
        solveEquations();
        calcDXNormImproveRootCalcYNorm();
        if (isConverged()) {
            //std::cout << "iterNo = " << iterNo << std::endl;
            break;
        }
    }
}
