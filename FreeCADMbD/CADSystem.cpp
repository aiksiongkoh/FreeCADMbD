/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <string>
#include <iostream>

#include "CADSystem.h"
#include "System.h"
#include "Item.h"
#include "Product.h"
#include "Constant.h"
#include "ZRotation.h"
#include "RevoluteJoint.h"
#include "CylindricalJoint.h"
#include "SystemSolver.h"
#include "Part.h"
#include "MarkerFrame.h"
#include "MarkerFrameq.h"
#include "PartFrame.h"
#include "AssemblyFrame.h"
#include "SymTime.h"
#include "StateData.h"
#include "EulerParameters.h"

using namespace MbD;

std::shared_ptr<CADSystem> CADSystem::With()
{
    auto inst = std::make_shared<CADSystem>();
    inst->initialize();
    return inst;
}

void CADSystem::initialize()
{
    //Do nothing.
}

void CADSystem::noop()
{
    //No Operations
}

void CADSystem::outputFor(AnalysisType)
{
    auto str = std::to_string(mbdSystem->mbdTimeValue());
    logString(str);
    mbdSystem->partsJointsMotionsLimitsForcesTorquesDo([&](std::shared_ptr<Item> item) {
        std::cout << std::endl;
        std::cout << item->classname() << " " << item->name << std::endl;
        auto data = item->stateData();
        std::cout << *data << std::endl;
        });
}

void CADSystem::logString(const std::string& str)
{
    std::cout << str << std::endl;
}

void CADSystem::logString(double)
{
    throw SimulationStoppingError("To be implemented.");
}

void CADSystem::runSinglePendulum()
{
    //Double pendulum with easy input numbers for exact port from Smalltalk
    //GEOAssembly calcCharacteristicDimensions must set mbdUnits to unity.
    std::cout << "runSinglePendulum" << std::endl;
    auto TheSystemOrAssembly = mbdSystem;
    TheSystemOrAssembly->clear();
    std::string name = "TheSystemOrAssembly";
    TheSystemOrAssembly->name = name;
    std::cout << "TheSystemOrAssembly->name " << TheSystemOrAssembly->name << std::endl;
    auto systemSolver = TheSystemOrAssembly->systemSolver;
    systemSolver->errorTolPosKine = 1.0e-6;
    systemSolver->errorTolAccKine = 1.0e-6;
    systemSolver->iterMaxPosKine = 25;
    systemSolver->iterMaxAccKine = 25;
    systemSolver->tstart = 0.0;
    systemSolver->tend = 0.04;
    systemSolver->hmin = 1.0e-9;
    systemSolver->hmax = 1.0;
    systemSolver->hout = 0.01;
    systemSolver->corAbsTol = 1.0e-6;
    systemSolver->corRelTol = 1.0e-6;
    systemSolver->intAbsTol = 1.0e-6;
    systemSolver->intRelTol = 1.0e-6;
    systemSolver->iterMaxDyn = 4;
    systemSolver->orderMax = 5;
    systemSolver->translationLimit = 1.0e10;
    systemSolver->rotationLimit = 0.5;

    std::string str;
    FColDsptr qX, qE, qXdot, omeOpO, qXddot, alpOpO;
    FColDsptr rpmp;
    FMatDsptr aAap, aApm;
    FRowDsptr fullRow;
    //
    auto assemblyFrame = TheSystemOrAssembly->asmFrame;
    assemblyFrame->name = "/Assembly1";
    std::cout << "assembly1->name " << assemblyFrame->name << std::endl;
    {
        auto marker2 = assemblyFrame->createMarkerFrame("/Assembly1/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.0 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker2->setaApm(aApm);
        assemblyFrame->addMarkerFrame(marker2);
        //
        auto marker1 = assemblyFrame->createMarkerFrame("/Assembly1/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.0, 3.0, 0.0 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 0, 1 },
            { 0, -1, 0 }
            });
        marker1->setaApm(aApm);
        assemblyFrame->addMarkerFrame(marker1);
    }
    //
    auto pendulum = Part::With("/Assembly1/Part1");
    std::cout << "pendulum->name " << pendulum->name << std::endl;
    pendulum->m = 1.0;
    pendulum->aJ = DiagonalMatrix<double>::With(ListD{ 1, 1, 1 });
    qX = std::make_shared<FullColumn<double>>(ListD{ 0.4, 0.0, -0.05 });
    aAap = FullMatrix<double>::With(ListListD{
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
        });
    pendulum->setqX(qX);
    pendulum->setaAap(aAap);
    qXdot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    omeOpO = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    pendulum->setqXdot(qXdot);
    pendulum->setomeOpO(omeOpO);
    TheSystemOrAssembly->addPart(pendulum);
    {
        auto partFrame = pendulum->partFrame;
        auto marker1 = partFrame->createMarkerFrame("/Assembly1/Part1/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.4, 0.0, 0.05 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker1->setaApm(aApm);
        partFrame->addMarkerFrame(marker1);
        //
        auto marker2 = partFrame->createMarkerFrame("/Assembly1/Part1/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.4, 0.0, 0.05 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker2->setaApm(aApm);
        partFrame->addMarkerFrame(marker2);
    }
    //
    auto revJoint1 = RevoluteJoint::With("/Assembly1/Joint1");
    std::cout << "revJoint1->name " << revJoint1->name << std::endl;
    revJoint1->connectsItoJ(assemblyFrame->endFrame("/Assembly1/Marker2"), pendulum->partFrame->endFrame("/Assembly1/Part1/Marker1"));
    TheSystemOrAssembly->addJoint(revJoint1);
    //
    auto rotMotion1 = ZRotation::With("/Assembly1/Motion1");
    rotMotion1->connectsItoJ(assemblyFrame->endFrame("/Assembly1/Marker2"), pendulum->partFrame->endFrame("/Assembly1/Part1/Marker1"));
    std::cout << "rotMotion1->name " << rotMotion1->name << std::endl;
    rotMotion1->the3zBlk = std::make_shared<Constant>(1.0);
    std::cout << "rotMotion1->the3zBlk " << *(rotMotion1->the3zBlk) << std::endl;
    TheSystemOrAssembly->addMotion(rotMotion1);
    //
    TheSystemOrAssembly->runKINEMATIC(TheSystemOrAssembly);
}

void CADSystem::runOndselDoublePendulum()
{
    //Double pendulum with easy input numbers for exact port from Smalltalk
    //GEOAssembly calcCharacteristicDimensions must set mbdUnits to unity.
    std::cout << "runOndselDoublePendulum" << std::endl;
    auto TheSystemOrAssembly = mbdSystem;
    TheSystemOrAssembly->clear();
    std::string name = "TheSystemOrAssembly";
    TheSystemOrAssembly->name = name;
    std::cout << "TheSystemOrAssembly->name " << TheSystemOrAssembly->name << std::endl;
    auto systemSolver = TheSystemOrAssembly->systemSolver;
    systemSolver->errorTolPosKine = 1.0e-6;
    systemSolver->errorTolAccKine = 1.0e-6;
    systemSolver->iterMaxPosKine = 25;
    systemSolver->iterMaxAccKine = 25;
    systemSolver->tstart = 0.0;
    systemSolver->tend = 0.04;
    systemSolver->hmin = 1.0e-9;
    systemSolver->hmax = 1.0;
    systemSolver->hout = 0.01;
    systemSolver->corAbsTol = 1.0e-6;
    systemSolver->corRelTol = 1.0e-6;
    systemSolver->intAbsTol = 1.0e-6;
    systemSolver->intRelTol = 1.0e-6;
    systemSolver->iterMaxDyn = 4;
    systemSolver->orderMax = 5;
    systemSolver->translationLimit = 1.0e10;
    systemSolver->rotationLimit = 0.5;

    std::string str;
    FColDsptr qX, qE, qXdot, omeOpO, qXddot, alpOpO;
    FColDsptr rpmp;
    FMatDsptr aAap, aApm;
    FRowDsptr fullRow;
    //
    auto assemblyFrame = TheSystemOrAssembly->asmFrame;
    assemblyFrame->name = "/Assembly1";
    std::cout << "assembly1->name " << assemblyFrame->name << std::endl;
    {
        auto marker2 = assemblyFrame->createMarkerFrame("/Assembly1/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.0 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker2->setaApm(aApm);
        assemblyFrame->addMarkerFrame(marker2);
        //
        auto marker1 = assemblyFrame->createMarkerFrame("/Assembly1/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.0, 3.0, 0.0 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 0, 1 },
            { 0, -1, 0 }
            });
        marker1->setaApm(aApm);
        assemblyFrame->addMarkerFrame(marker1);
    }
    //
    auto crankPart1 = Part::With("/Assembly1/Part1");
    std::cout << "crankPart1->name " << crankPart1->name << std::endl;
    crankPart1->m = 1.0;
    crankPart1->aJ = DiagonalMatrix<double>::With(ListD{ 1, 1, 1 });
    qX = std::make_shared<FullColumn<double>>(ListD{ 0.4, 0.0, -0.05 });
    aAap = FullMatrix<double>::With(ListListD{
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
        });
    crankPart1->setqX(qX);
    crankPart1->setaAap(aAap);
    qXdot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    omeOpO = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    crankPart1->setqXdot(qXdot);
    crankPart1->setomeOpO(omeOpO);
    TheSystemOrAssembly->addPart(crankPart1);
    {
        auto partFrame = crankPart1->partFrame;
        auto marker1 = partFrame->createMarkerFrame("/Assembly1/Part1/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.4, 0.0, 0.05 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker1->setaApm(aApm);
        partFrame->addMarkerFrame(marker1);
        //
        auto marker2 = partFrame->createMarkerFrame("/Assembly1/Part1/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.4, 0.0, 0.05 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker2->setaApm(aApm);
        partFrame->addMarkerFrame(marker2);
    }
    //
    auto conrodPart2 = Part::With("/Assembly1/Part2");
    std::cout << "conrodPart2->name " << conrodPart2->name << std::endl;
    conrodPart2->m = 1.0;
    conrodPart2->aJ = DiagonalMatrix<double>::With(ListD{ 1, 1, 1 });
    qX = std::make_shared<FullColumn<double>>(ListD{ 0.15, 0.1, 0.05 });
    qE = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 1.0, 0.0 });
    auto eulerParameters = EulerParameters<double>::With(ListD{ 0.0, 0.0, 1.0, 0.0 });
    eulerParameters->calcABC();
    aAap = eulerParameters->aA;
    conrodPart2->setqX(qX);
    conrodPart2->setaAap(aAap);
    qXdot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    omeOpO = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    conrodPart2->setqXdot(qXdot);
    conrodPart2->setomeOpO(omeOpO);
    TheSystemOrAssembly->addPart(conrodPart2);
    {
        auto partFrame = conrodPart2->partFrame;
        auto marker1 = partFrame->createMarkerFrame("/Assembly1/Part2/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.65, 0.0, -0.05 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
            });
        marker1->setaApm(aApm);
        partFrame->addMarkerFrame(marker1);
        //
        auto marker2 = partFrame->createMarkerFrame("/Assembly1/Part2/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.65, 0.0, -0.05 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
            });
        marker2->setaApm(aApm);
        partFrame->addMarkerFrame(marker2);
    }
    //
    auto revJoint1 = RevoluteJoint::With("/Assembly1/Joint1");
    std::cout << "revJoint1->name " << revJoint1->name << std::endl;
    revJoint1->connectsItoJ(assemblyFrame->endFrame("/Assembly1/Marker2"), crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker1"));
    TheSystemOrAssembly->addJoint(revJoint1);

    auto revJoint2 = RevoluteJoint::With("/Assembly1/Joint2");
    std::cout << "revJoint2->name " << revJoint2->name << std::endl;
    revJoint2->connectsItoJ(crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker2"), conrodPart2->partFrame->endFrame("/Assembly1/Part2/Marker1"));
    TheSystemOrAssembly->addJoint(revJoint2);
    //
    TheSystemOrAssembly->runKINEMATIC(TheSystemOrAssembly);
}

void CADSystem::runOndselPiston()
{
    //Piston with easy input numbers for exact port from Smalltalk
    //GEOAssembly calcCharacteristicDimensions must set mbdUnits to unity.
    std::cout << "runOndselPiston" << std::endl;
    auto TheSystemOrAssembly = mbdSystem;
    TheSystemOrAssembly->clear();
    std::string name = "TheSystemOrAssembly";
    TheSystemOrAssembly->name = name;
    std::cout << "TheSystemOrAssembly->name " << TheSystemOrAssembly->name << std::endl;
    auto systemSolver = TheSystemOrAssembly->systemSolver;
    systemSolver->errorTolPosKine = 1.0e-6;
    systemSolver->errorTolAccKine = 1.0e-6;
    systemSolver->iterMaxPosKine = 25;
    systemSolver->iterMaxAccKine = 25;
    systemSolver->tstart = 0.0;
    systemSolver->tend = 1.0;
    systemSolver->hmin = 1.0e-9;
    systemSolver->hmax = 1.0;
    systemSolver->hout = 0.04;
    systemSolver->corAbsTol = 1.0e-6;
    systemSolver->corRelTol = 1.0e-6;
    systemSolver->intAbsTol = 1.0e-6;
    systemSolver->intRelTol = 1.0e-6;
    systemSolver->iterMaxDyn = 4;
    systemSolver->orderMax = 5;
    systemSolver->translationLimit = 1.0e10;
    systemSolver->rotationLimit = 0.5;

    std::string str;
    FColDsptr qX, qE, qXdot, omeOpO, qXddot, qEddot;
    FColDsptr rpmp;
    FMatDsptr aApm;
    FRowDsptr fullRow;
    //
    auto assemblyFrame = TheSystemOrAssembly->asmFrame;
    assemblyFrame->name = "/Assembly1";
    std::cout << "assemblyFrame->name " << assemblyFrame->name << std::endl;
    {
        auto marker2 = assemblyFrame->createMarkerFrame("/Assembly1/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.0 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker2->setaApm(aApm);
        assemblyFrame->addMarkerFrame(marker2);
        //
        auto marker1 = assemblyFrame->createMarkerFrame("/Assembly1/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.0, 3.0, 0.0 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 0, 1 },
            { 0, -1, 0 }
            });
        marker1->setaApm(aApm);
        assemblyFrame->addMarkerFrame(marker1);
    }
    //
    auto crankPart1 = Part::With("/Assembly1/Part1");
    std::cout << "crankPart1->name " << crankPart1->name << std::endl;
    crankPart1->m = 1.0;
    crankPart1->aJ = DiagonalMatrix<double>::With(ListD{ 1, 1, 1 });
    qX = std::make_shared<FullColumn<double>>(ListD{ 0.4, 0.0, -0.05 });
    qE = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.0, 1.0 });
    crankPart1->setqX(qX);
    crankPart1->setqE(qE);
    qXdot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    omeOpO = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    crankPart1->setqXdot(qXdot);
    crankPart1->setomeOpO(omeOpO);
    qXddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    qEddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0, 0 });
    crankPart1->setqXddot(qXddot);
    crankPart1->setqEddot(qEddot);
    TheSystemOrAssembly->addPart(crankPart1);
    {
        auto partFrame = crankPart1->partFrame;
        auto marker1 = partFrame->createMarkerFrame("/Assembly1/Part1/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.4, 0.0, 0.05 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker1->setaApm(aApm);
        partFrame->addMarkerFrame(marker1);
        //
        auto marker2 = partFrame->createMarkerFrame("/Assembly1/Part1/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.4, 0.0, 0.05 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker2->setaApm(aApm);
        partFrame->addMarkerFrame(marker2);
    }
    //
    auto conrodPart2 = Part::With("/Assembly1/Part2");
    std::cout << "conrodPart2->name " << conrodPart2->name << std::endl;
    conrodPart2->m = 1.0;
    conrodPart2->aJ = DiagonalMatrix<double>::With(ListD{ 1, 1, 1 });
    qX = std::make_shared<FullColumn<double>>(ListD{ 0.15, 0.1, 0.05 });
    qE = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 1.0, 0.0 });
    conrodPart2->setqX(qX);
    conrodPart2->setqE(qE);
    qXdot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    omeOpO = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    conrodPart2->setqXdot(qXdot);
    conrodPart2->setomeOpO(omeOpO);
    qXddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    qEddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0, 0 });
    conrodPart2->setqXddot(qXddot);
    conrodPart2->setqEddot(qEddot);
    TheSystemOrAssembly->addPart(conrodPart2);
    {
        auto partFrame = conrodPart2->partFrame;
        auto marker1 = partFrame->createMarkerFrame("/Assembly1/Part2/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.65, 0.0, -0.05 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
            });
        marker1->setaApm(aApm);
        partFrame->addMarkerFrame(marker1);
        //
        auto marker2 = partFrame->createMarkerFrame("/Assembly1/Part2/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.65, 0.0, -0.05 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
            });
        marker2->setaApm(aApm);
        partFrame->addMarkerFrame(marker2);
    }
    //
    auto pistonPart3 = Part::With("/Assembly1/Part3");
    std::cout << "pistonPart3->name " << pistonPart3->name << std::endl;
    pistonPart3->m = 1.0;
    pistonPart3->aJ = DiagonalMatrix<double>::With(ListD{ 1, 1, 1 });
    qX = std::make_shared<FullColumn<double>>(ListD{ -0.0, 1.5, 0.0 });
    qE = std::make_shared<FullColumn<double>>(ListD{ 0.70710678118655, 0.70710678118655, 0.0, 0.0 });
    pistonPart3->setqX(qX);
    pistonPart3->setqE(qE);
    qXdot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    omeOpO = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    pistonPart3->setqXdot(qXdot);
    pistonPart3->setomeOpO(omeOpO);
    qXddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    qEddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0, 0 });
    pistonPart3->setqXddot(qXddot);
    pistonPart3->setqEddot(qEddot);
    TheSystemOrAssembly->addPart(pistonPart3);
    {
        auto partFrame = pistonPart3->partFrame;
        auto marker1 = partFrame->createMarkerFrame("/Assembly1/Part3/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.5, 0.0, 0.0 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {0.0, 1.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, 0.0, -1.0}
            });
        marker1->setaApm(aApm);
        partFrame->addMarkerFrame(marker1);
        //
        auto marker2 = partFrame->createMarkerFrame("/Assembly1/Part3/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.5, 0.0, 0.0 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
            });
        marker2->setaApm(aApm);
        partFrame->addMarkerFrame(marker2);
    }
    //
    auto revJoint1 = RevoluteJoint::With("/Assembly1/Joint1");
    std::cout << "revJoint1->name " << revJoint1->name << std::endl;
    revJoint1->connectsItoJ(assemblyFrame->endFrame("/Assembly1/Marker2"), crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker1"));
    TheSystemOrAssembly->addJoint(revJoint1);

    auto revJoint2 = RevoluteJoint::With("/Assembly1/Joint2");
    std::cout << "revJoint2->name " << revJoint2->name << std::endl;
    revJoint2->connectsItoJ(crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker2"), conrodPart2->partFrame->endFrame("/Assembly1/Part2/Marker1"));
    TheSystemOrAssembly->addJoint(revJoint2);

    auto revJoint3 = RevoluteJoint::With("/Assembly1/Joint3");
    std::cout << "revJoint3->name " << revJoint3->name << std::endl;
    revJoint3->connectsItoJ(conrodPart2->partFrame->endFrame("/Assembly1/Part2/Marker2"), pistonPart3->partFrame->endFrame("/Assembly1/Part3/Marker1"));
    TheSystemOrAssembly->addJoint(revJoint3);

    auto cylJoint4 = CylindricalJoint::With("/Assembly1/Joint4");
    std::cout << "cylJoint4->name " << cylJoint4->name << std::endl;
    cylJoint4->connectsItoJ(pistonPart3->partFrame->endFrame("/Assembly1/Part3/Marker2"), assemblyFrame->endFrame("/Assembly1/Marker1"));
    TheSystemOrAssembly->addJoint(cylJoint4);

    auto rotMotion1 = ZRotation::With("/Assembly1/Motion1");
    rotMotion1->connectsItoJ(assemblyFrame->endFrame("/Assembly1/Marker2"), crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker1"));
    std::cout << "rotMotion1->name " << rotMotion1->name << std::endl;
    auto omega = std::make_shared<Constant>(6.2831853071796);
    auto timeScale = std::make_shared<Constant>(1.0);
    auto time = std::make_shared<Product>(timeScale, TheSystemOrAssembly->time);
    rotMotion1->the3zBlk = std::make_shared<Product>(omega, time);
    std::cout << "rotMotion1->the3zBlk " << *(rotMotion1->the3zBlk) << std::endl;
    TheSystemOrAssembly->addMotion(rotMotion1);
    //
    TheSystemOrAssembly->runKINEMATIC(TheSystemOrAssembly);
    str = "";
    TheSystemOrAssembly->jointsMotionsLimitsDo([&](std::shared_ptr<ConstraintSet> jm) {
        str += jm->constraintSpecs();
        });
    str = "";
    TheSystemOrAssembly->jointsMotionsLimitsDo([&](std::shared_ptr<ConstraintSet> jm) {
        str += jm->name + " constraints\n";
        jm->constraintsDo([&](std::shared_ptr<Constraint> con) {
            str += "    " + con->constraintSpec() + "\n";
            });
        });
    std::cout << str << std::endl;
}

void CADSystem::runPiston()
{
    std::cout << "runPiston" << std::endl;
    auto TheSystemOrAssembly = mbdSystem;
    TheSystemOrAssembly->clear();
    std::string name = "TheSystemOrAssembly";
    TheSystemOrAssembly->name = name;
    std::cout << "TheSystemOrAssembly->name " << TheSystemOrAssembly->name << std::endl;
    auto systemSolver = TheSystemOrAssembly->systemSolver;
    systemSolver->errorTolPosKine = 1.0e-6;
    systemSolver->errorTolAccKine = 1.0e-6;
    systemSolver->iterMaxPosKine = 25;
    systemSolver->iterMaxAccKine = 25;
    systemSolver->tstart = 0.0;
    systemSolver->tend = 25.0;
    systemSolver->hmin = 2.5e-8;
    systemSolver->hmax = 25.0;
    systemSolver->hout = 1.0;
    systemSolver->corAbsTol = 1.0e-6;
    systemSolver->corRelTol = 1.0e-6;
    systemSolver->intAbsTol = 1.0e-6;
    systemSolver->intRelTol = 1.0e-6;
    systemSolver->iterMaxDyn = 4;
    systemSolver->orderMax = 5;
    systemSolver->translationLimit = 9.6058421285615e9;
    systemSolver->rotationLimit = 0.5;

    FColDsptr qX, qE, qXdot, omeOpO, qXddot, qEddot;
    FColDsptr rpmp;
    FMatDsptr aApm;
    FRowDsptr fullRow;
    //
    auto assemblyFrame = TheSystemOrAssembly->asmFrame;
    assemblyFrame->name = "/Assembly1";
    std::cout << "assemblyFrame->name " << assemblyFrame->name << std::endl;
    {
        auto marker2 = assemblyFrame->createMarkerFrame("/Assembly1/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.0 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker2->setaApm(aApm);
        assemblyFrame->addMarkerFrame(marker2);
        //
        auto marker1 = assemblyFrame->createMarkerFrame("/Assembly1/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.0, 2.8817526385684, 0.0 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 0, 1 },
            { 0, -1, 0 }
            });
        marker1->setaApm(aApm);
        assemblyFrame->addMarkerFrame(marker1);
    }
    //
    auto crankPart1 = Part::With("/Assembly1/Part1");
    std::cout << "crankPart1->name " << crankPart1->name << std::endl;
    crankPart1->m = 0.045210530089461;
    crankPart1->aJ = DiagonalMatrix<double>::With(ListD{ 1.7381980042084e-4, 0.003511159968501, 0.0036154518487535 });
    qX = std::make_shared<FullColumn<double>>(ListD{ 0.38423368514246, 2.6661567755108e-17, -0.048029210642807 });
    qE = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.0, 1.0 });
    crankPart1->setqX(qX);
    crankPart1->setqE(qE);
    qXdot = std::make_shared<FullColumn<double>>(ListD{ 0, 0.096568457800423, 0 });
    omeOpO = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0.25132741228718 });
    crankPart1->setqXdot(qXdot);
    crankPart1->setomeOpO(omeOpO);
    qXddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    qEddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0, 0 });
    crankPart1->setqXddot(qXddot);
    crankPart1->setqEddot(qEddot);
    TheSystemOrAssembly->addPart(crankPart1);
    {
        auto partFrame = crankPart1->partFrame;
        auto marker1 = partFrame->createMarkerFrame("/Assembly1/Part1/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.38423368514246, -2.6661567755108e-17, 0.048029210642807 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker1->setaApm(aApm);
        partFrame->addMarkerFrame(marker1);
        //
        auto marker2 = partFrame->createMarkerFrame("/Assembly1/Part1/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.38423368514246, -2.6661567755108e-17, 0.048029210642807 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
            });
        marker2->setaApm(aApm);
        partFrame->addMarkerFrame(marker2);
    }
    //
    auto conrodPart2 = Part::With("/Assembly1/Part2");
    std::cout << "conrodPart2->name " << conrodPart2->name << std::endl;
    conrodPart2->m = 0.067815795134192;
    conrodPart2->aJ = DiagonalMatrix<double>::With(ListD{ 2.6072970063126e-4, 0.011784982468533, 0.011941420288912 });
    qX = std::make_shared<FullColumn<double>>(ListD{ 0.38423368514246, 0.49215295678475, 0.048029210642807 });
    qE = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.89871703427292, 0.43852900965351 });
    conrodPart2->setqX(qX);
    conrodPart2->setqE(qE);
    qXdot = std::make_shared<FullColumn<double>>(ListD{ 0, 0.19313691560085, 0 });
    omeOpO = std::make_shared<FullColumn<double>>(ListD{ 1.670970041317e-34, 1.3045598281729e-34, -1.2731200314796e-35 });
    conrodPart2->setqXdot(qXdot);
    conrodPart2->setomeOpO(omeOpO);
    qXddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    qEddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0, 0 });
    conrodPart2->setqXddot(qXddot);
    conrodPart2->setqEddot(qEddot);
    TheSystemOrAssembly->addPart(conrodPart2);
    {
        auto partFrame = conrodPart2->partFrame;
        auto marker1 = partFrame->createMarkerFrame("/Assembly1/Part2/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.6243797383565, 1.1997705489799e-16, -0.048029210642807 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {1.0, 2.7755575615629e-16, 0.0},
            {-2.7755575615629e-16, 1.0, 0.0},
            {0.0, 0.0, 1.0}
            });
        marker1->setaApm(aApm);
        partFrame->addMarkerFrame(marker1);
        //
        auto marker2 = partFrame->createMarkerFrame("/Assembly1/Part2/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.6243797383565, -2.1329254204087e-16, -0.048029210642807 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {1.0, 2.4980018054066e-16, 2.2204460492503e-16},
            {-2.4980018054066e-16, 1.0, 4.1633363423443e-17},
            {-2.2204460492503e-16, -4.1633363423443e-17, 1.0}
            });
        marker2->setaApm(aApm);
        partFrame->addMarkerFrame(marker2);
    }
    //
    auto pistonPart3 = Part::With("/Assembly1/Part3");
    std::cout << "pistonPart3->name " << pistonPart3->name << std::endl;
    pistonPart3->m = 1.730132083368;
    pistonPart3->aJ = DiagonalMatrix<double>::With(ListD{ 0.19449049546716, 0.23028116340971, 0.23028116340971 });
    qX = std::make_shared<FullColumn<double>>(ListD{ -1.283972762056e-18, 1.4645980199976, -4.7652385308244e-17 });
    qE = std::make_shared<FullColumn<double>>(ListD{ 0.70710678118655, 0.70710678118655, 0.0, 0.0 });
    pistonPart3->setqX(qX);
    pistonPart3->setqE(qE);
    qXdot = std::make_shared<FullColumn<double>>(ListD{ -6.3364526821409e-32, 0.19313691560085, -1.933731897626e-34 });
    omeOpO = std::make_shared<FullColumn<double>>(ListD{ 1.670970041317e-34, 1.3045598281729e-34, 1.8896472173894e-50 });
    pistonPart3->setqXdot(qXdot);
    pistonPart3->setomeOpO(omeOpO);
    qXddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
    qEddot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0, 0 });
    pistonPart3->setqXddot(qXddot);
    pistonPart3->setqEddot(qEddot);
    TheSystemOrAssembly->addPart(pistonPart3);
    {
        auto partFrame = pistonPart3->partFrame;
        auto marker1 = partFrame->createMarkerFrame("/Assembly1/Part3/Marker1");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.48029210642807, 7.6201599718927e-18, -2.816737703896e-17 });
        marker1->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {9.2444637330587e-33, 1.0, 2.2204460492503e-16},
            {1.0, -9.2444637330587e-33, -1.0785207688569e-32},
            {-1.0785207688569e-32, 2.2204460492503e-16, -1.0}
            });
        marker1->setaApm(aApm);
        partFrame->addMarkerFrame(marker1);
        //
        auto marker2 = partFrame->createMarkerFrame("/Assembly1/Part3/Marker2");
        rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.48029210642807, 1.7618247880058e-17, 2.5155758471256e-17 });
        marker2->setrpmp(rpmp);
        aApm = FullMatrix<double>::With(ListListD{
            {6.9388939039072e-18, -6.4146353042213e-50, 1.0},
            {1.0, -6.9388939039072e-18, 6.9388939039072e-18},
            {-6.9388939039072e-18, 1.0, -7.4837411882581e-50}
            });
        marker2->setaApm(aApm);
        partFrame->addMarkerFrame(marker2);
    }
    //
    auto revJoint1 = RevoluteJoint::With("/Assembly1/Joint1");
    std::cout << "revJoint1->name " << revJoint1->name << std::endl;
    revJoint1->connectsItoJ(assemblyFrame->endFrame("/Assembly1/Marker2"), crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker1"));
    TheSystemOrAssembly->addJoint(revJoint1);

    auto revJoint2 = RevoluteJoint::With("/Assembly1/Joint2");
    std::cout << "revJoint2->name " << revJoint2->name << std::endl;
    revJoint2->connectsItoJ(crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker2"), conrodPart2->partFrame->endFrame("/Assembly1/Part2/Marker1"));
    TheSystemOrAssembly->addJoint(revJoint2);

    auto revJoint3 = RevoluteJoint::With("/Assembly1/Joint3");
    std::cout << "revJoint3->name " << revJoint3->name << std::endl;
    revJoint3->connectsItoJ(conrodPart2->partFrame->endFrame("/Assembly1/Part2/Marker2"), pistonPart3->partFrame->endFrame("/Assembly1/Part3/Marker1"));
    TheSystemOrAssembly->addJoint(revJoint3);

    auto cylJoint4 = CylindricalJoint::With("/Assembly1/Joint4");
    std::cout << "cylJoint4->name " << cylJoint4->name << std::endl;
    cylJoint4->connectsItoJ(pistonPart3->partFrame->endFrame("/Assembly1/Part3/Marker2"), assemblyFrame->endFrame("/Assembly1/Marker1"));
    TheSystemOrAssembly->addJoint(cylJoint4);

    auto rotMotion1 = ZRotation::With("/Assembly1/Motion1");
    rotMotion1->connectsItoJ(assemblyFrame->endFrame("/Assembly1/Marker2"), crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker1"));
    std::cout << "rotMotion1->name " << rotMotion1->name << std::endl;
    auto omega = std::make_shared<Constant>(6.2831853071796);
    auto timeScale = std::make_shared<Constant>(0.04);
    auto time = std::make_shared<Product>(timeScale, TheSystemOrAssembly->time);
    rotMotion1->the3zBlk = std::make_shared<Product>(omega, time);
    std::cout << "rotMotion1->the3zBlk " << *(rotMotion1->the3zBlk) << std::endl;
    TheSystemOrAssembly->addMotion(rotMotion1);
    //
    TheSystemOrAssembly->runKINEMATIC(TheSystemOrAssembly);
}

void CADSystem::preMbDrun(std::shared_ptr<System>)
{
    //Do nothing.
}

void CADSystem::postMbDrun()
{
    //Do nothing.
}

void CADSystem::updateFromMbD()
{
    //Do nothing.
}
