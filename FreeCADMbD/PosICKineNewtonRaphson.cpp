/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "PosICKineNewtonRaphson.h"
#include "SystemSolver.h"
#include "Part.h"
#include "Constraint.h"

using namespace MbD;

std::shared_ptr<PosICKineNewtonRaphson> PosICKineNewtonRaphson::With()
{
    auto inst = std::make_shared<PosICKineNewtonRaphson>();
    inst->initialize();
    return inst;
}

void PosICKineNewtonRaphson::run()
{
    //VectorNewtonRaphson::run();   //Inlined to help debugging
    preRun();
    initializeLocally();
    initializeGlobally();
    iterate();
    postRun();
}

void PosICKineNewtonRaphson::iterate()
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

void PosICKineNewtonRaphson::initializeGlobally()
{
    AnyPosICNewtonRaphson::initializeGlobally();
    iterMax = system->iterMaxPosKine;
    dxTol = system->errorTolPosKine;
}

void PosICKineNewtonRaphson::assignEquationNumbers()
{
    auto parts = system->parts();
    //auto contactEndFrames = system->contactEndFrames();
    //auto uHolders = system->uHolders();
    auto constraints = system->allConstraints();
    size_t eqnNo = 0;
    for (auto& part : *parts) {
        part->iqX(eqnNo);
        eqnNo = eqnNo + 3;
        part->iqE(eqnNo);
        eqnNo = eqnNo + 4;
    }
    //for (auto& endFrm : *contactEndFrames) {
    //    endFrm->is(eqnNo);
    //    eqnNo = eqnNo + endFrm->sSize();
    //}
    //for (auto& uHolder : *uHolders) {
    //    uHolder->iu(eqnNo);
    //    eqnNo += 1;
    //}
    auto nEqns = eqnNo;    //C++ uses index 0.
    nqsu = nEqns;
    for (auto& con : *constraints) {
        con->iG = eqnNo;
        eqnNo += 1;
    }
    //auto lastEqnNo = eqnNo - 1;
    nEqns = eqnNo;    //C++ uses index 0.
    n = nEqns;
}

void PosICKineNewtonRaphson::preRun()
{
    system->logString("MbD: Solving for quasi kinematic position.");
    PosNewtonRaphson::preRun();
}

bool PosICKineNewtonRaphson::isConverged()
{
    return dxNorms->at(iterNo) < dxTol || isConvergedToNumericalLimit();
}
