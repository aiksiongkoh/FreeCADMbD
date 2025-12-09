/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

 /*********************************************************************
  * @file  MbDCode.cpp
  *
  * @brief Program to assemble a piston crank system.
  *********************************************************************/

#include <iostream>	
#include <fstream>	
#include <filesystem>
#include <string>

#include "../OndselMbD/CADSystem.h"
#include "../OndselMbD/GESpMatParPvPrecise.h"
#include "../OndselMbD/ASMTAssembly.h"
#include "../OndselMbD/MBDynSystem.h"
#include "../OndselMbD/MomentOfInertiaSolver.h"

using namespace MbD;
void doublePrecisionTest();
void runSpMat();
void sharedptrTest();

int main(int argc, char* argv[])
{
	if (argc > 1) {
		//For command line execution ./ondselmbd filename.mbd
		MBDynSystem::runDynFile(argv[1]);
		return 0;
	}

	//MBDynSystem::runDynFile("../testapp/MBDyn/Unicycle simulation attempt 1/MBDCase.mbd");	//Need to handle subassemblies
	ASMTAssembly::runKineFile("../testapp/ASMT/piston.asmt");
	ASMTAssembly::runDynFile("../testapp/ASMT/piston.asmt");
	MBDynSystem::runDynFile("../testapp/MBDyn/SingleRigidPendulum07-02-2024/MBDCaseOndsel.mbd");
	MBDynSystem::runDynFile("../testapp/MBDyn/markers.mbd");
	MBDynSystem::runDynFile("../testapp/MBDyn/General force using Rod joint/Bungee/MBDCase.mbd");
	ASMTAssembly::runDynFile("../testapp/ASMT/torsion.asmt");
	ASMTAssembly::runDynFile("../testapp/ASMT/springdamper.asmt");
	MBDynSystem::runDynFile("../testapp/MBDyn/penduRod5deg2.mbd");
	MBDynSystem::runDynFile("../testapp/MBDyn/penduBeam.mbd");
	MBDynSystem::runDynFile("../testapp/MBDyn/penduRod90deg.mbd");
	MBDynSystem::runDynFile("../testapp/MBDyn/penduPointMass8.mbd");
	ASMTAssembly::readWriteDynFile("../testapp/ASMT/rotatingCrank2.asmt");
	ASMTAssembly::readWriteDynFile("../testapp/ASMT/pistonClean.asmt");
	ASMTAssembly::runDynFile("../testapp/ASMT/simplePendu3.asmt");

	ASMTAssembly::runDynFile("../testapp/ASMT/Schmidt_Coupling_Ass_1-1.asmt");
	ASMTAssembly::runDynFile("../testapp/ASMT/RevRevJt.asmt");
	ASMTAssembly::runDynFile("../testapp/ASMT/RevCylJt.asmt");
	ASMTAssembly::runDynFile("../testapp/ASMT/CylSphJt.asmt");
	ASMTAssembly::runDynFile("../testapp/ASMT/SphSphJt.asmt");
	MBDynSystem::runDynFile("../testapp/MBDyn/MBDynCase(Cosine-half drive).mbd");
	MBDynSystem::runDynFile("../testapp/MBDyn/MBDynCase(Sine-forever drive).mbd");
	MBDynSystem::runDynFile("../testapp/MBDyn/MBDynCase9orig.mbd");	//SimulationStoppingError
	MBDynSystem::runDynFile("../testapp/MBDyn/MBDynCase8orig.mbd");	//Incompatible geometry at t=3.15
	MBDynSystem::runDynFile("../testapp/MBDyn/MBDynCase5orig.mbd");	//Test Product::integrateWRT
	ASMTAssembly::readWriteKineFile("../testapp/ASMT/Gears.asmt");
	ASMTAssembly::readWriteKineFile("../testapp/ASMT/anglejoint.asmt");
	ASMTAssembly::readWriteKineFile("../testapp/ASMT/constvel.asmt");
	ASMTAssembly::readWriteKineFile("../testapp/ASMT/rackscrew.asmt");
	ASMTAssembly::readWriteKineFile("../testapp/ASMT/planarbug.asmt");
	MBDynSystem::runDynFile("../testapp/MBDyn/InitialConditions.mbd");
	MBDynSystem::runDynFile("../testapp/MBDyn/SphericalHinge.mbd");
	ASMTAssembly::runDynFile("../testapp/ASMT/cirpendu2.asmt");	//Under constrained. Testing ICKine.
	ASMTAssembly::runDynFile("../testapp/ASMT/quasikine.asmt");	//Under constrained. Testing ICKine.
	ASMTAssembly::readWriteKineFile("../testapp/ASMT/piston.asmt");
	//MBDynSystem::runDynFile("../testapp/MBDyn/MBDynCaseDebug2.mbd");
	//return 0;
	MBDynSystem::runDynFile("../testapp/MBDyn/MBDynCase2.mbd");
	//MBDynSystem::runDynFile("../testapp/MBDyn/MBDynCase.mbd");	//Very large but works
	MBDynSystem::runDynFile("../testapp/MBDyn/CrankSlider2.mbd");
	//MBDynSystem::runDynFile("../testapp/MBDyn/crank_slider.mbd");	//Needs integration of product
	ASMTAssembly::runDynFile("../testapp/ASMT/piston.asmt");
	ASMTAssembly::runDynFile("../testapp/ASMT/00backhoe.asmt");
	//ASMTAssembly::runDynFile("../testapp/ASMT/circular.asmt");	//Needs checking
	//ASMTAssembly::runDynFile("../testapp/ASMT/cirpendu.asmt");	//Under constrained. Testing ICKine.
	//ASMTAssembly::runDynFile("../testapp/ASMT/engine1.asmt");	//Needs checking
	ASMTAssembly::runDynFile("../testapp/ASMT/fourbar.asmt");
	//ASMTAssembly::runDynFile("../testapp/ASMT/fourbot.asmt");	//Very large but works
	ASMTAssembly::runDynFile("../testapp/ASMT/wobpump.asmt");

	////ASMTAssembly::runSinglePendulumSuperSimplified();	//Mass is missing
	////ASMTAssembly::runSinglePendulumSuperSimplified2();	//DOF has infinite acceleration due to zero mass and inertias
	ASMTAssembly::runSinglePendulumSimplified();
	ASMTAssembly::runSinglePendulum();
	auto cadSystem = std::make_shared<CADSystem>();
	cadSystem->runOndselSinglePendulum();
	cadSystem->runOndselDoublePendulum();
	//cadSystem->runOndselPiston();		//For debugging
	cadSystem->runPiston();
	runSpMat();
	MomentOfInertiaSolver::example1();
	sharedptrTest();
}

void sharedptrTest() {
	auto assm = ASMTAssembly::With();

	auto assm1 = assm;	//New shared_ptr to old object. Reference count incremented.
	assert(assm == assm1);
	assert(assm.get() == assm1.get());
	assert(&assm != &assm1);
	assert(assm->constantGravity == assm1->constantGravity);
	assert(&(assm->constantGravity) == &(assm1->constantGravity));

	auto assm2 = std::make_shared<ASMTAssembly>(*assm);	//New shared_ptr to new object. Member variables copy old member variables
	assert(assm != assm2);
	assert(assm.get() != assm2.get());
	assert(&assm != &assm2);
	assert(assm->constantGravity == assm2->constantGravity);	//constantGravity is same object pointed to
	assert(&(assm->constantGravity) != &(assm2->constantGravity)); //Different shared_ptrs of same reference counter
}

void doublePrecisionTest()
{
	double pi = OS_M_PI;
	std::string str = "3.141592653589793238462643";
	std::istringstream iss(str);
	double d;
	iss >> d;

}

void runSpMat() {
	auto spMat = std::make_shared<SparseMatrix<double>>(3, 3);
	spMat->atandput(0, 0, 1.0);
	spMat->atandput(0, 1, 1.0);
	spMat->atandput(1, 0, 1.0);
	spMat->atandput(1, 1, 1.0);
	spMat->atandput(1, 2, 1.0);
	spMat->atandput(2, 1, 1.0);
	spMat->atandput(2, 2, 1.0);
	auto fullCol = std::make_shared<FullColumn<double>>(3);
	fullCol->atput(0, 1.0);
	fullCol->atput(1, 2.0);
	fullCol->atput(2, 3.0);
	auto matSolver = GESpMatParPvPrecise::With();
	auto answer = matSolver->solvewithsaveOriginal(spMat, fullCol, true);
	auto aAx = spMat->timesFullColumn(answer);
}
