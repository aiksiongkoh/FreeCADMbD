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

#include <filesystem>

#include "../FreeCADMbD/CADSystem.h"
#include "../FreeCADMbD/GESpMatParPvPrecise.h"
#include "../FreeCADMbD/ASMTAssembly.h"
#include "../FreeCADMbD/MBDynSystem.h"
#include "../FreeCADMbD/MomentOfInertiaSolver.h"

using namespace MbD;
void runSpMat();
void sharedptrTest();

int main(int argc, char* argv[])
{
	if (argc > 1) {
		//For command line execution ./ondselmbd filename.mbd
		std::string str = argv[1];
		if (str.find(".asmt") != std::string::npos) {
			ASMTAssembly::runDynFile(str);
		}
		else if (str.find(".mbd") != std::string::npos) {
			MBDynSystem::runDynFile(str);
		}
		return 0;
	}

	ASMTAssembly::runKineFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/Schmidt_Coupling_Ass_1-1.asmt");
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/RevRevJt.asmt");
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/RevCylJt.asmt");
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/CylSphJt.asmt");
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/SphSphJt.asmt");
	MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/MBDynCase(Cosine-half drive).mbd");
	MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/MBDynCase(Sine-forever drive).mbd");
	MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/MBDynCase9orig.mbd");	//SimulationStoppingError
	MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/MBDynCase8orig.mbd");	//Incompatible geometry at t=3.15
	MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/MBDynCase5orig.mbd");	//Test Product::integrateWRT
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/Gears.asmt");
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/anglejoint.asmt");
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/constvel.asmt");
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/rackscrew.asmt");
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/planarbug.asmt");
	MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/InitialConditions.mbd");
	MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/SphericalHinge.mbd");
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/cirpendu2.asmt");	//Under constrained. Testing ICKine.
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/quasikine.asmt");	//Under constrained. Testing ICKine.
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");
	//MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/MBDynCaseDebug2.mbd");
	//return 0;
	MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/MBDynCase2.mbd");
	//MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/MBDynCase.mbd");	//Very large but works
	MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/CrankSlider2.mbd");
	//MBDynSystem::runDynFile(std::string(TEST_DATA_PATH) + "/MBDyn/crank_slider.mbd");	//Needs integration of product
	////ASMTAssembly::runSinglePendulumSuperSimplified();	//Mass is missing
	////ASMTAssembly::runSinglePendulumSuperSimplified2();	//DOF has infinite acceleration due to zero mass and inertias
	ASMTAssembly::runSinglePendulumSimplified();
	ASMTAssembly::runSinglePendulum();
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/00backhoe.asmt");
	//ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/circular.asmt");	//Needs checking
	//ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/engine1.asmt");	//Needs checking
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/fourbar.asmt");
	//ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/fourbot.asmt");	//Very large but works
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/wobpump.asmt");

	auto cadSystem = CADSystem::With();
	cadSystem->runOndselSinglePendulum();
	cadSystem->runOndselDoublePendulum();
	//cadSystem->runOndselPiston();		//For debugging
	cadSystem->runPiston();
	runSpMat();
	MomentOfInertiaSolver::example1();
	sharedptrTest();
}
void sharedptrTest() {
	auto assm = std::make_shared<ASMTAssembly>();

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
void runSpMat() {
	auto spMat = std::make_shared<SparseMatrix<double>>(3, 3);
	spMat->atijput(0, 0, 1.0);
	spMat->atijput(0, 1, 1.0);
	spMat->atijput(1, 0, 1.0);
	spMat->atijput(1, 1, 1.0);
	spMat->atijput(1, 2, 1.0);
	spMat->atijput(2, 1, 1.0);
	spMat->atijput(2, 2, 1.0);
	auto fullCol = std::make_shared<FullColumn<double>>(3);
	fullCol->atiput(0, 1.0);
	fullCol->atiput(1, 2.0);
	fullCol->atiput(2, 3.0);
	auto matSolver = GESpMatParPvPrecise::With();
	auto answer = matSolver->solvewithsaveOriginal(spMat, fullCol, true);
	auto aAx = spMat->timesFullColumn(answer);
}
