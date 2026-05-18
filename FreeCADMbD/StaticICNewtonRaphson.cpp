/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC                                      *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "SystemSolver.h"
#include "StaticICNewtonRaphson.h"
#include "SimulationStoppingError.h"
#include "Part.h"

using namespace MbD;

std::shared_ptr<StaticICNewtonRaphson> StaticICNewtonRaphson::With()
{
    auto inst = std::make_shared<StaticICNewtonRaphson>();
    inst->initialize();
    return inst;
}

void MbD::StaticICNewtonRaphson::askSystemToUpdate()
{
    system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item)
                                                    { item->postStaticIteration(); });
}

void StaticICNewtonRaphson::assignEquationNumbers()
{
    auto parts = system->parts();
    // auto contactEndFrames = system->contactEndFrames();
    // auto uHolders = system->uHolders();
    auto constraints = system->allConstraints();
    size_t eqnNo = 0;
    for (auto part : *parts)
    {
        part->iqX(eqnNo);
        eqnNo = eqnNo + 3;
        part->iqE(eqnNo);
        eqnNo = eqnNo + 4;
    }
    // for (auto endFrm : *contactEndFrames) {
    //     endFrm->is(eqnNo);
    //     eqnNo = eqnNo + endFrm->sSize();
    // }
    // for (auto uHolder : *uHolders) {
    //     uHolder->iu(eqnNo);
    //     eqnNo += 1;
    // }
    auto nEqns = eqnNo; // C++ uses index 0.
    nqsu = nEqns;
    for (auto con : *constraints)
    {
        con->iG = eqnNo;
        eqnNo += 1;
    }
    // auto lastEqnNo = eqnNo - 1;
    nEqns = eqnNo; // C++ uses index 0.
    n = nEqns;
}

void MbD::StaticICNewtonRaphson::createVectorsAndMatrices()
{
    qsuOld = std::make_shared<FullColumn<double>>(nqsu);
    qsuWeights = DiagonalMatrix<double>::With(nqsu);
    SystemNewtonRaphson::createVectorsAndMatrices();
}

void StaticICNewtonRaphson::fillPyPx()
{
    pypx->zeroSelf();
    pypx->atijminusDiagonalMatrix(0, 0, qsuWeights);
    system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item)
                                                    {
                                                        item->fillStaticJacob(pypx);
                                                        // std::cout << *(pypx->at(3)) << std::endl;
                                                    });
    // std::cout << *pypx << std::endl;
}

void StaticICNewtonRaphson::fillY()
{
    auto newMinusOld = qsuOld->negated();
    newMinusOld->equalSelfPlusFullColumnAt(x, 0);
    y->zeroSelf();
    y->atiminusFullColumn(0, (qsuWeights->timesFullColumn(newMinusOld)));
    system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item)
                                                    {
                                                        item->fillStaticError(y);
                                                        // std::cout << item->name << *y << std::endl;
                                                    });
    // std::cout << "Final" << *y << std::endl;
}

void MbD::StaticICNewtonRaphson::incrementIterNo()
{
    iterNo++;
    if (iterNo > iterMax)
    {
        std::stringstream ss;
        ss << "MbD: No convergence after " << iterNo << " iterations.";
        auto str = ss.str();
        system->logString(str);
        ss.str("");
        ss << "A static solution cannot be found.";
        str = ss.str();
        system->logString(str);

        throw SimulationStoppingError("");
    }
}

void MbD::StaticICNewtonRaphson::initializeGlobally()
{
    SystemNewtonRaphson::initializeGlobally();
    system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item)
                                       {
        item->fillqsu(qsuOld);
        item->fillqsuWeights(qsuWeights);
        item->fillqsulam(x); });
    iterMax = system->iterMaxAccKine;
    dxTol = system->errorTolAccKine;
}

void MbD::StaticICNewtonRaphson::logSingularMatrixMessage()
{
    std::string str = "A static solution cannot be found.";
    system->logString(str);
}

void StaticICNewtonRaphson::passRootToSystem()
{
    system->partsJointsMotionsLimitsDo([&](std::shared_ptr<Item> item)
                                       { item->setqsulam(x); });
}

void MbD::StaticICNewtonRaphson::postRun()
{
    system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item)
                                                    { item->postStatic(); });
}

void MbD::StaticICNewtonRaphson::preRun()
{
    const std::string& str("Iterating for static solution.");
    system->logString(str);
    system->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item) { 
        item->preStatic(); 
        });
}
