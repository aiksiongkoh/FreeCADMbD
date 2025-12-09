/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AccKineNewtonRaphson.h"
#include "SystemSolver.h"

using namespace MbD;

std::shared_ptr<AccKineNewtonRaphson> AccKineNewtonRaphson::With()
{
    auto inst = std::make_shared<AccKineNewtonRaphson>();
    inst->initialize();
    return inst;
}

void AccKineNewtonRaphson::run()
{
    //VectorNewtonRaphson::run();   //Inlined to help debugging
    preRun();
    initializeLocally();
    initializeGlobally();
    iterate();
    postRun();
}

void AccKineNewtonRaphson::iterate()
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

void AccKineNewtonRaphson::initializeGlobally()
{
    AccNewtonRaphson::initializeGlobally();
    iterMax = system->iterMaxAccKine;
    dxTol = system->errorTolAccKine;
}

void AccKineNewtonRaphson::preRun()
{
    std::string str("MbD: Solving for kinematic acceleration.");
    system->logString(str);
    AccNewtonRaphson::preRun();
}
