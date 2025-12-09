#include "pch.h"
#include <cmath>
#include <CADSystem.h>
#include <ASMTAssembly.h>
#include <GESpMatParPvPrecise.h>
#include <MomentOfInertiaSolver.h>

using namespace MbD;

TEST(FreeCADMbD, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runOndselSinglePendulum) {
	//testing::internal::CaptureStdout();
	auto cadSystem = CADSystem::With();
	cadSystem->runOndselSinglePendulum();
	//std::string output = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runPreDragBackhoe1) {
	auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/runPreDragBackhoe1.asmt");
	assembly->runDraggingLog(std::string(TEST_DATA_PATH) + "/ASMT/draggingBackhoe1.log");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runPreDragBackhoe2) {
	auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/runPreDragBackhoe2.asmt");
	assembly->runDraggingLog(std::string(TEST_DATA_PATH) + "/ASMT/draggingBackhoe2.log");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runPreDragBackhoe3) {
	auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/runPreDragBackhoe3.asmt");
	assembly->runDraggingLog(std::string(TEST_DATA_PATH) + "/ASMT/draggingBackhoe3.log");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, pistonAllowZRotation) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/pistonAllowZRotation.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, RevRevJt) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/RevRevJt.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, RevCylJt) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/RevCylJt.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, CylSphJt) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/CylSphJt.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, SphSphJt) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/SphSphJt.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, Gears) {
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/Gears.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, anglejoint) {
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/anglejoint.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, constvel) {
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/constvel.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, rackscrew) {
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/rackscrew.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, planarbug) {
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/planarbug.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, cirpendu2) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/cirpendu2.asmt");	//Under constrained. Testing ICKine.
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, quasikine) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/quasikine.asmt");	//Under constrained. Testing ICKine.
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, piston) {
	ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, Springs) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/springs.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, Torsion) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/torsion.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runSinglePendulumSuperSimplified) {
	ASMTAssembly::runSinglePendulumSuperSimplified();	//Mass is missing
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runSinglePendulumSuperSimplified2) {
	ASMTAssembly::runSinglePendulumSuperSimplified2();	//DOF has infinite acceleration due to zero mass and inertias
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runSinglePendulumSimplified) {
	ASMTAssembly::runSinglePendulumSimplified();
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runSinglePendulum) {
	ASMTAssembly::runSinglePendulum();
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, piston2) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, 00backhoe) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/00backhoe.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, circular) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/circular.asmt");	//Needs checking
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, engine1) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/engine1.asmt");	//Needs checking
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, fourbar) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/fourbar.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, fourbot) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/fourbot.asmt");	//Very large but works
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, wobpump) {
	ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/wobpump.asmt");
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runOndselDoublePendulum) {
	auto cadSystem = CADSystem::With();
	cadSystem->runOndselDoublePendulum();
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runOndselPiston) {
	auto cadSystem = CADSystem::With();
	cadSystem->runOndselPiston();		//For debugging
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runPiston) {
	auto cadSystem = CADSystem::With();
	cadSystem->runPiston();
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, GESpMatParPvPrecise) {
	GESpMatParPvPrecise::runSpMat();
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, MomentOfInertiaSolver) {
	MomentOfInertiaSolver::example1();
	EXPECT_TRUE(true);
}
TEST(FreeCADMbD, sharedptrTest) {
	auto assm = ASMTAssembly::With();

	std::shared_ptr<ASMTAssembly> assm1 = assm;	//New shared_ptr to old object. Reference count incremented.
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
	EXPECT_TRUE(true);
}

