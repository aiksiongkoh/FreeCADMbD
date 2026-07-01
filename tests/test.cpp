#include "pch.h"
#include <cmath>
#include <numbers>
#include <CADSystem.h>
#include <ASMTAssembly.h>
#include <ASMTPart.h>
#include <ASMTMarker.h>
#include <ASMTMarkerTemp.h>
#include <ASMTConstantGravity.h>
#include <ASMTTime.h>
#include <GESpMatParPvPrecise.h>
#include <MomentOfInertiaSolver.h>
#include <BasicUserFunction.h>
#include <EulerAngles.h>
#include <ExactPendulum.h>

using namespace MbD;

TEST(FreeCADMbD, TestName)
{
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, simplePendulumXY)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/simplePendulumXYa.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, simplePendulumExactMotion)
{
    constexpr auto length = 1.0;
    constexpr auto gravity = 9.81;
    constexpr auto theta0 = std::numbers::pi / 2.0;
    const auto omegaNatural = std::sqrt(gravity / length);
    const auto modulus = std::sin(theta0 / 2.0);
    const auto period = 4.0 * std::comp_ellint_1(modulus) / omegaNatural;

    ExactPendulum pendulum(theta0, 0.0, omegaNatural);

    auto theta = pendulum.theta(0.0).theta;
    EXPECT_NEAR(theta0, theta, 1.0e-12);
    EXPECT_NEAR(1.0, length * std::sin(theta), 1.0e-12);
    EXPECT_NEAR(0.0, -length * std::cos(theta), 1.0e-12);
    auto result = pendulum.theta(0.0);
    EXPECT_NEAR(0.0, result.time, 1.0e-12);
    EXPECT_NEAR(theta0, result.theta0, 1.0e-12);
    EXPECT_NEAR(0.0, result.omega0, 1.0e-12);
    EXPECT_NEAR(omegaNatural, result.omega_n, 1.0e-12);
    EXPECT_NEAR(0.0, result.omega, 1.0e-12);
    EXPECT_NEAR(-omegaNatural * omegaNatural * std::sin(theta0), result.alpha, 1.0e-12);

    result = pendulum.theta(period / 4.0);
    theta = result.theta;
    EXPECT_NEAR(period / 4.0, result.time, 1.0e-12);
    EXPECT_NEAR(0.0, theta, 1.0e-12);
    EXPECT_NEAR(-2.0 * omegaNatural * modulus, result.omega, 1.0e-12);
    EXPECT_NEAR(0.0, result.alpha, 1.0e-12);
    EXPECT_NEAR(0.0, length * std::sin(theta), 1.0e-12);
    EXPECT_NEAR(-1.0, -length * std::cos(theta), 1.0e-12);

    theta = pendulum.theta(period).theta;
    EXPECT_NEAR(theta0, theta, 1.0e-12);
    EXPECT_NEAR(1.0, length * std::sin(theta), 1.0e-12);
    EXPECT_NEAR(0.0, -length * std::cos(theta), 1.0e-12);
}
TEST(FreeCADMbD, exactPendulumClass)
{
    constexpr auto theta0 = std::numbers::pi / 2.0;
    constexpr auto omega0 = 0.0;
    constexpr auto omega_n = 1.0;

    ExactPendulum pendulum(theta0, omega0, omega_n);

    auto result = pendulum.theta(0.0);
    EXPECT_EQ(ExactPendulum::Mode::Oscillation, result.mode);
    EXPECT_NEAR(0.0, result.time, 1.0e-12);
    EXPECT_NEAR(theta0, result.theta0, 1.0e-12);
    EXPECT_NEAR(omega0, result.omega0, 1.0e-12);
    EXPECT_NEAR(omega_n, result.omega_n, 1.0e-12);
    EXPECT_NEAR(theta0, result.theta, 1.0e-12);
    EXPECT_NEAR(omega0, result.omega, 1.0e-12);
    EXPECT_NEAR(-omega_n * omega_n * std::sin(theta0), result.alpha, 1.0e-12);
}
TEST(FreeCADMbD, exactPendulumInitialAngularVelocity)
{
    constexpr auto theta0 = std::numbers::pi / 6.0;
    constexpr auto omega0 = -0.25;
    constexpr auto omega_n = 1.0;

    ExactPendulum pendulum(theta0, omega0, omega_n);

    auto result = pendulum.theta(0.0);
    EXPECT_EQ(ExactPendulum::Mode::Oscillation, result.mode);
    EXPECT_NEAR(0.0, result.time, 1.0e-12);
    EXPECT_NEAR(theta0, result.theta0, 1.0e-12);
    EXPECT_NEAR(omega0, result.omega0, 1.0e-12);
    EXPECT_NEAR(omega_n, result.omega_n, 1.0e-12);
    EXPECT_NEAR(theta0, result.theta, 1.0e-12);
    EXPECT_NEAR(omega0, result.omega, 1.0e-12);
    EXPECT_NEAR(-omega_n * omega_n * std::sin(theta0), result.alpha, 1.0e-12);
}
TEST(FreeCADMbD, pointPendulumRevJtRegression)
{
    // asmt has point mass swinging in x-y plane.
    // Origin is at pivot.
    // x is to the right.
    // y is up.
    // gravity is in -y direction.
    // bryz is right hand rule rotation about z-axis. x-axis is reference.
    for (int idigit = 4; idigit <= 4; idigit++)
    {
        double tol = std::pow(10.0, -idigit);
        auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/pointPendulumRevJt.asmt");
        auto simPara = assembly->simulationParameters;
        simPara->setAllTolForNDigit(idigit);
        auto pendulum = assembly->partNamed("/Assembly/Part1");

        auto length = pendulum->principalMassMarker->position3D->at(0);
        auto gravity = -assembly->constantGravity->g->at(1);
        auto theta0 = pendulum->rotationMatrix->bryantAngles()->at(2) + std::numbers::pi / 2.0;
        auto omega0 = pendulum->omega3D->at(2);
        auto omega_n = std::sqrt(gravity / length);
        auto exactPendulum = ExactPendulum(theta0, omega0, omega_n);
        size_t n = (simPara->tend - simPara->tstart) / simPara->hout;
        n = n + 2; // add count for input and initial time

        assembly->runDYNAMIC();

        ASSERT_EQ(n, assembly->times->size());
        ASSERT_EQ(n, pendulum->xs->size());
        ASSERT_EQ(n, pendulum->ys->size());
        ASSERT_EQ(n, pendulum->bryzs->size());
        double maxXDiff = 0.0;
        double maxYDiff = 0.0;
        double maxBryzDiff = 0.0;
        for (size_t i = 1; i < n; i++)
        {
            auto time = assembly->times->at(i);
            auto theta = exactPendulum.theta(time).theta;
            auto bryz = theta - std::numbers::pi / 2.0;
            auto x = (length * std::sin(theta)) - (length * std::cos(bryz));
            auto y = (-length * std::cos(theta)) - (length * std::sin(bryz));
            maxXDiff = std::max(maxXDiff, std::abs(x - pendulum->xs->at(i)));
            maxYDiff = std::max(maxYDiff, std::abs(y - pendulum->ys->at(i)));
            maxBryzDiff = std::max(maxBryzDiff, std::abs(bryz - pendulum->bryzs->at(i)));
        }
        EXPECT_TRUE(maxXDiff <= 5.0 * tol);
        EXPECT_TRUE(maxYDiff <= 5.0 * tol);
        EXPECT_TRUE(maxBryzDiff <= 5.0 * tol);
    }
}
TEST(FreeCADMbD, line2PendulumRevJtRegression)
{
    // asmt has slender rod (L) swinging in x-y plane.
    // Origin is at pivot.
    // x is to the right.
    // y is up.
    // gravity is in -y direction.
    // bryz is right hand rule rotation about z-axis. x-axis is reference.
    for (int idigit = 4; idigit <= 4; idigit++)
    {
        double tol = std::pow(10.0, -idigit);
        auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/linePendulumRevJt.asmt");
        auto simPara = assembly->simulationParameters;
        simPara->setAllTolForNDigit(idigit);
        auto pendulum = assembly->partNamed("/Assembly/Part1");

        auto length = 2 * pendulum->principalMassMarker->position3D->at(0);
        auto gravity = -assembly->constantGravity->g->at(1);
        auto theta0 = pendulum->rotationMatrix->bryantAngles()->at(2) + std::numbers::pi / 2.0;
        auto omega0 = pendulum->omega3D->at(2);
        auto omega_n = std::sqrt(3 * gravity / (2 * length));
        auto exactPendulum = ExactPendulum(theta0, omega0, omega_n);
        size_t n = (simPara->tend - simPara->tstart) / simPara->hout;
        n = n + 2; // add count for input and initial time

        assembly->runDYNAMIC();

        ASSERT_EQ(n, assembly->times->size());
        ASSERT_EQ(n, pendulum->xs->size());
        ASSERT_EQ(n, pendulum->ys->size());
        ASSERT_EQ(n, pendulum->bryzs->size());
        double maxXDiff = 0.0;
        double maxYDiff = 0.0;
        double maxBryzDiff = 0.0;
        for (size_t i = 1; i < n; i++)
        {
            auto time = assembly->times->at(i);
            auto theta = exactPendulum.theta(time).theta;
            auto bryz = theta - std::numbers::pi / 2.0;
            auto x = (length * std::sin(theta)) - (length * std::cos(bryz));
            auto y = (-length * std::cos(theta)) - (length * std::sin(bryz));
            maxXDiff = std::max(maxXDiff, std::abs(x - pendulum->xs->at(i)));
            maxYDiff = std::max(maxYDiff, std::abs(y - pendulum->ys->at(i)));
            maxBryzDiff = std::max(maxBryzDiff, std::abs(bryz - pendulum->bryzs->at(i)));
        }
        EXPECT_TRUE(maxXDiff <= 5.0 * tol);
        EXPECT_TRUE(maxYDiff <= 5.0 * tol);
        EXPECT_TRUE(maxBryzDiff <= 5.0 * tol);
    }
}
TEST(FreeCADMbD, blockPendulumRevJtRegression)
{
    // AI Prompt
    // Compound pendulum is a cuboid of dimensions L,W,H.
    // Pivot is about an axis in the middle of an end face and is parallel to the short edge of the face.
    // What is the equation of motion?

    // \ddot{\theta} + \frac{6gL}{4L^2+W^2}\theta=0

    // asmt has cuboid mass swinging in x-y plane.
    // Origin is at pivot.
    // x is to the right.
    // y is up.
    // gravity is in -y direction.
    // bryz is right hand rule rotation about z-axis. x-axis is reference.
    for (int idigit = 4; idigit <= 4; idigit++)
    {
        double tol = std::pow(10.0, -idigit);
        auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/blockPendulumRevJt.asmt");
        auto simPara = assembly->simulationParameters;
        simPara->setAllTolForNDigit(idigit);
        auto pendulum = assembly->partNamed("/Assembly/Part1");

        auto length = 2 * pendulum->principalMassMarker->position3D->at(0);
        auto width = 0.02;
        auto gravity = -assembly->constantGravity->g->at(1);
        auto theta0 = pendulum->rotationMatrix->bryantAngles()->at(2) + std::numbers::pi / 2.0;
        auto omega0 = pendulum->omega3D->at(2);
        auto omega_n = std::sqrt((6 * gravity * length) / ((4 * length * length) + (width * width)));
        auto exactPendulum = ExactPendulum(theta0, omega0, omega_n);
        size_t n = (simPara->tend - simPara->tstart) / simPara->hout;
        n = n + 2; // add count for input and initial time

        assembly->runDYNAMIC();

        ASSERT_EQ(n, assembly->times->size());
        ASSERT_EQ(n, pendulum->xs->size());
        ASSERT_EQ(n, pendulum->ys->size());
        ASSERT_EQ(n, pendulum->bryzs->size());
        double maxXDiff = 0.0;
        double maxYDiff = 0.0;
        double maxBryzDiff = 0.0;
        for (size_t i = 1; i < n; i++)
        {
            auto time = assembly->times->at(i);
            auto theta = exactPendulum.theta(time).theta;
            auto bryz = theta - std::numbers::pi / 2.0;
            auto x = (length * std::sin(theta)) - (length * std::cos(bryz));
            auto y = (-length * std::cos(theta)) - (length * std::sin(bryz));
            maxXDiff = std::max(maxXDiff, std::abs(x - pendulum->xs->at(i)));
            maxYDiff = std::max(maxYDiff, std::abs(y - pendulum->ys->at(i)));
            maxBryzDiff = std::max(maxBryzDiff, std::abs(bryz - pendulum->bryzs->at(i)));
        }
        EXPECT_TRUE(maxXDiff <= 5.0 * tol);
        EXPECT_TRUE(maxYDiff <= 5.0 * tol);
        EXPECT_TRUE(maxBryzDiff <= 5.0 * tol);
    }
}
TEST(FreeCADMbD, 00compoundPendulum)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/CompoundPendulumX.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runCADSystemSinglePendulum)
{
    // testing::internal::CaptureStdout();
    auto cadSystem = CADSystem::With();
    cadSystem->runSinglePendulum();
    // std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runPreDragBackhoe1)
{
    auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/runPreDragBackhoe1.asmt");
    assembly->runDraggingLog(std::string(TEST_DATA_PATH) + "/ASMT/draggingBackhoe1.log");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runPreDragBackhoe2)
{
    auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/runPreDragBackhoe2.asmt");
    assembly->runDraggingLog(std::string(TEST_DATA_PATH) + "/ASMT/draggingBackhoe2.log");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runPreDragBackhoe3)
{
    auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/runPreDragBackhoe3.asmt");
    assembly->runDraggingLog(std::string(TEST_DATA_PATH) + "/ASMT/draggingBackhoe3.log");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, pistonAllowZRotation)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/pistonAllowZRotation.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, RevRevJt)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/RevRevJt.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, RevCylJt)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/RevCylJt.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, CylSphJt)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/CylSphJt.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, SphSphJt)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/SphSphJt.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, Gears)
{
    ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/Gears.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, anglejoint)
{
    ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/anglejoint.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, constvel)
{
    ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/constvel.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, rackscrew)
{
    ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/rackscrew.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, planarbug)
{
    ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/planarbug.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, cirpendu2)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/cirpendu2.asmt"); // Under constrained. Testing ICKine.
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, quasikine)
{
    ASMTAssembly::runKineFile(std::string(TEST_DATA_PATH) + "/ASMT/quasikine.asmt"); // Under constrained. Testing ICKine.
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, piston)
{
    ASMTAssembly::readWriteDynFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, pistonDynRegression)
{
    auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");

    assembly->runDYNAMIC();

    auto piston = assembly->partNamed("/Assembly1/Part3");
    ASSERT_EQ(27, assembly->times->size());
    ASSERT_EQ(27, piston->ys->size());

    const auto last = piston->ys->size() - 1;
    EXPECT_NEAR(1.0, assembly->times->at(last), 1.0e-12);
    EXPECT_NEAR(1.024695076596, piston->ys->at(last), 1.0e-7);
    EXPECT_NEAR(5.0265482457437, piston->vys->at(last), 1.0e-4);
    EXPECT_NEAR(24.65727399679, piston->ays->at(last), 2.0e-2);
    EXPECT_NEAR(-1.5707963267949, piston->bryxs->at(last), 1.0e-12);
}
TEST(FreeCADMbD, pistonKineRegression)
{
    auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");

    assembly->runKINEMATIC();

    auto piston = assembly->partNamed("/Assembly1/Part3");
    ASSERT_EQ(27, assembly->times->size());
    ASSERT_EQ(27, piston->ys->size());

    const auto last = piston->ys->size() - 1;
    EXPECT_NEAR(1.0, assembly->times->at(last), 1.0e-12);
    EXPECT_NEAR(1.024695076596, piston->ys->at(last), 1.0e-8);
    EXPECT_NEAR(5.0265482457437, piston->vys->at(last), 1.0e-5);
    EXPECT_NEAR(24.65727399679, piston->ays->at(last), 2.0e-3);
    EXPECT_NEAR(-1.5707963267949, piston->bryxs->at(last), 1.0e-12);
}
TEST(FreeCADMbD, Springs)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/springs.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, SpringsQuasiStatic)
{
    ASMTAssembly::runQuasiStaticFile(std::string(TEST_DATA_PATH) + "/ASMT/springsStatic.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, Torsion)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/torsion.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runSinglePendulumSuperSimplified)
{
    ASMTAssembly::runSinglePendulumSuperSimplified(); // Mass is missing
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runSinglePendulumSuperSimplified2)
{
    ASMTAssembly::runSinglePendulumSuperSimplified2(); // DOF has infinite acceleration due to zero mass and inertias
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runSinglePendulumSimplified)
{
    ASMTAssembly::runSinglePendulumSimplified();
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runSinglePendulum)
{
    ASMTAssembly::runSinglePendulum();
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, piston2)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/piston.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, 00backhoeDyn)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/00backhoe.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, 00backhoeKine)
{
    ASMTAssembly::runKineFile(std::string(TEST_DATA_PATH) + "/ASMT/00backhoe.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, circular)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/circular.asmt"); // Needs checking
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, engine1)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/engine1.asmt"); // Needs checking
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, fourbar)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/fourbar.asmt");
    EXPECT_TRUE(true);
}
// TEST(FreeCADMbD, fourbot) {
//     ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/fourbot.asmt");    //Very large but works
//     EXPECT_TRUE(true);
// }
TEST(FreeCADMbD, wobpump)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/wobpump.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, mcphersonX)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/mcphersonX.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, torsionSprDmpTol8)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/torsionSprDmpTol8.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, springdamper2)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/springdamper2.asmt");
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runOndselDoublePendulum)
{
    auto cadSystem = CADSystem::With();
    cadSystem->runOndselDoublePendulum();
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runOndselPiston)
{
    auto cadSystem = CADSystem::With();
    cadSystem->runOndselPiston(); // For debugging
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, runPiston)
{
    auto cadSystem = CADSystem::With();
    cadSystem->runPiston();
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, GESpMatParPvPrecise)
{
    GESpMatParPvPrecise::runSpMat();
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, MomentOfInertiaSolver)
{
    MomentOfInertiaSolver::example1();
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, sharedptrTest)
{
    auto assm = ASMTAssembly::With();

    std::shared_ptr<ASMTAssembly> assm1 = assm; // New shared_ptr to old object. Reference count incremented.
    assert(assm == assm1);
    assert(assm.get() == assm1.get());
    assert(&assm != &assm1);
    assert(assm->constantGravity == assm1->constantGravity);
    assert(&(assm->constantGravity) == &(assm1->constantGravity));

    auto assm2 = std::make_shared<ASMTAssembly>(*assm); // New shared_ptr to new object. Member variables copy old member variables
    assert(assm != assm2);
    assert(assm.get() != assm2.get());
    assert(&assm != &assm2);
    assert(assm->constantGravity == assm2->constantGravity);       // constantGravity is same object pointed to
    assert(&(assm->constantGravity) != &(assm2->constantGravity)); // Different shared_ptrs of same reference counter
    EXPECT_TRUE(true);
}
TEST(FreeCADMbD, SymbolicParserTest)
{
    auto assm = ASMTAssembly::With();
    auto parser = SymbolicParser::With();
    parser->owner = assm.get();
    auto geoTime = assm->geoTime();
    parser->variables->insert(std::make_pair("time", geoTime));
    std::shared_ptr<BasicUserFunction> userFunc;
    userFunc = std::make_shared<BasicUserFunction>("				-3500.0d + 1000.0d*sin(6.0d*pi*time) ", 1.0);
    parser->parseUserFunction(userFunc);
    auto sym = parser->stack->top();
    EXPECT_TRUE(true);
}
