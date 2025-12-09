/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <iostream>
 
#include "AnyPosICNewtonRaphson.h"
#include "SystemSolver.h"
#include "Item.h"
#include "Part.h"
#include "Constraint.h"

using namespace MbD;

void AnyPosICNewtonRaphson::initialize()
{
    NewtonRaphson::initialize();
    nSingularMatrixError = 0;
}

void AnyPosICNewtonRaphson::initializeGlobally()
{
    SystemNewtonRaphson::initializeGlobally();
    system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) {
        item->fillqsu(qsuOld);
        item->fillqsuWeights(qsuWeights);
        item->fillqsulam(x);
        });
}

void AnyPosICNewtonRaphson::createVectorsAndMatrices()
{
    qsuOld = std::make_shared<FullColumn<double>>(nqsu);
    qsuWeights = DiagonalMatrix<double>::With(nqsu);
    SystemNewtonRaphson::createVectorsAndMatrices();
}

void AnyPosICNewtonRaphson::fillY()
{
    auto newMinusOld = qsuOld->negated();
    newMinusOld->equalSelfPlusFullColumnAt(x, 0);
    y->zeroSelf();
    y->atiminusFullColumn(0, (qsuWeights->timesFullColumn(newMinusOld)));
    system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) {
        item->fillPosICError(y);
        //std::cout << item->name << *y << std::endl;
        //noop();
        });
    //std::cout << "Final" << *y << std::endl;
}

void AnyPosICNewtonRaphson::fillPyPx()
{
    pypx->zeroSelf();
    pypx->atijminusDiagonalMatrix(0, 0, qsuWeights);
    system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) {
        item->fillPosICJacob(pypx);
        //std::cout << *(pypx->at(3)) << std::endl;
        });
    //std::cout << *pypx << std::endl;
}

void AnyPosICNewtonRaphson::passRootToSystem()
{
    system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item) { item->setqsulam(x); });
}

void AnyPosICNewtonRaphson::assignEquationNumbers()
{
    //Subclasses must implement.
    throw SimulationStoppingError("To be implemented.");
}

bool AnyPosICNewtonRaphson::isConverged()
{
    return false;
}
