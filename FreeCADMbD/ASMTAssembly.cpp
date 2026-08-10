/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <string>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <limits>
#include <numbers>
#include <utility>
#include <array>

#include "ASMTAssembly.h"
#include "ASMTRevoluteJoint.h"
#include "ASMTCylindricalJoint.h"
#include "ASMTRotationalMotion.h"
#include "ASMTTranslationalMotion.h"
#include "ASMTMarker.h"
#include "ASMTPart.h"
#include "ASMTTranslationalJoint.h"
#include "ASMTSphericalJoint.h"
#include "ASMTFixedJoint.h"
#include "ASMTGeneralMotion.h"
#include "ASMTAllowRotation.h"
#include "ASMTUniversalJoint.h"
#include "ASMTPointInPlaneJoint.h"
#include "ASMTMarkerTemp.h"
#include "ASMTForceTorque.h"
#include "ASMTConstantGravity.h"
#include "ASMTSimulationParameters.h"
#include "ASMTAnimationParameters.h"
#include "Numeric.h"
#include "Part.h"
#include "ASMTTime.h"
#include "ASMTItem.h"
#include "ASMTItemIJ.h"
#include "ASMTAngleJoint.h"
#include "ASMTConstantVelocityJoint.h"
#include "ASMTCylSphJoint.h"
#include "ASMTGearJoint.h"
#include "ASMTPointInLineJoint.h"
#include "ASMTRevCylJoint.h"
#include "ASMTSphSphJoint.h"
#include "ASMTLineInPlaneJoint.h"
#include "ASMTPlanarJoint.h"
#include "ASMTNoRotationJoint.h"
#include "ASMTParallelAxesJoint.h"
#include "ASMTPerpendicularJoint.h"
#include "ASMTRackPinionJoint.h"
#include "ASMTScrewJoint.h"
#include "SimulationStoppingError.h"
#include "ASMTKinematicIJ.h"
#include "ASMTRefPoint.h"
#include "ASMTRefCurve.h"
#include "ASMTRefSurface.h"
#include "ExternalSystem.h"
#include "SystemSolver.h"
#include "ASMTRevRevJoint.h"
#include "ASMTForceTorqueInLine.h"
#include "ASMTForceTorqueGeneral.h"
#include "ASMTLimit.h"
#include "ASMTRotationLimit.h"
#include "ASMTTranslationLimit.h"
#include "Units.h"
#include "PosVelAccData.h"
#include "EulerAngles.h"
#if __GNUC__ >= 8
#include <filesystem>
#endif
namespace
{
    constexpr auto FreeCADMotionHeader = "freeCAD: 3D CAD with Motion Simulation  by  askoh.com";
    constexpr auto OndselSolverHeader = "OndselSolver";
    constexpr auto FreeCADMbDHeader = "FreeCADMbD";
    constexpr auto SmallPendulumAmplitude = 1.0e-12;
    constexpr auto SmallPendulumVelocity = 1.0e-12;

    bool isASMTHeader(const std::string &line)
    {
        return line == FreeCADMotionHeader || line == OndselSolverHeader || line == FreeCADMbDHeader;
    }

    double signum(double value)
    {
        if (value < 0.0)
            return -1.0;
        if (value > 0.0)
            return 1.0;
        return 0.0;
    }

    double inverseJacobiSn(double sn, double modulus)
    {
        sn = std::clamp(sn, -1.0, 1.0);
        return std::ellint_1(modulus, std::asin(sn));
    }

    std::pair<double, double> jacobiSnCnFromU(double u, double modulus)
    {
        const auto kComplete = std::comp_ellint_1(modulus);
        const auto period = 4.0 * kComplete;
        auto reducedU = std::fmod(u, period);
        if (reducedU < 0.0)
            reducedU += period;

        auto signSn = 1.0;
        auto signCn = 1.0;
        if (reducedU > 2.0 * kComplete)
        {
            reducedU -= 2.0 * kComplete;
            signSn = -1.0;
            signCn = -1.0;
        }
        if (reducedU > kComplete)
        {
            reducedU = 2.0 * kComplete - reducedU;
            signCn = -signCn;
        }

        double phi = std::clamp(reducedU, 0.0, std::numbers::pi / 2.0);
        for (size_t i = 0; i < 12; ++i)
        {
            const auto sinPhi = std::sin(phi);
            const auto cosPhi = std::cos(phi);
            const auto root = std::sqrt(std::max(0.0, 1.0 - modulus * modulus * sinPhi * sinPhi));
            const auto residual = std::ellint_1(modulus, phi) - reducedU;
            const auto correction = residual * root;
            phi -= correction;
            if (std::abs(correction) <= 2.0 * std::numeric_limits<double>::epsilon() * std::max(1.0, std::abs(phi)))
                break;
            if (cosPhi == 0.0)
                break;
        }
        return {signSn * std::sin(phi), signCn * std::cos(phi)};
    }
}

using namespace MbD;

namespace
{
    using RotationMatrixValues = std::array<double, 9>;

    template <typename T>
    void setRotationMatrix(const std::shared_ptr<T> &item, const RotationMatrixValues &rotation)
    {
        item->setRotationMatrix(
            rotation[0], rotation[1], rotation[2],
            rotation[3], rotation[4], rotation[5],
            rotation[6], rotation[7], rotation[8]);
    }

    std::shared_ptr<ASMTAssembly> pointPendulumRevJt(
        const RotationMatrixValues &rotation,
        double gravityX,
        double gravityY,
        double gravityZ)
    {
        auto assembly = ASMTAssembly::With();

        assembly->setNotes("");
        assembly->setName("Assembly1");
        assembly->setPosition3D(0, 0, 0);
        assembly->setRotationMatrix(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1);
        assembly->setVelocity3D(0, 0, 0);
        assembly->setOmega3D(0, 0, 0);

        auto mkrAM1 = ASMTMarker::With();
        mkrAM1->setName("Marker1");
        mkrAM1->setPosition3D(0, 0, 0);
        setRotationMatrix(mkrAM1, rotation);
        assembly->addMarker(mkrAM1);

        auto part1 = ASMTPart::With();
        part1->setName("Part1");
        part1->setPosition3D(0, 0, 0);
        setRotationMatrix(part1, rotation);
        part1->setVelocity3D(0, 0, 0);
        part1->setOmega3D(0, 0, 0);
        assembly->addPart(part1);

        auto massMarker = ASMTMarkerTemp::With();
        massMarker->setMass(0.2);
        massMarker->setDensity(1000.0);
        massMarker->setMomentOfInertias(0, 0, 0);
        massMarker->setPosition3D(0.2, 0, 0);
        massMarker->setRotationMatrix(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1);
        part1->setPrincipalMassMarker(massMarker);

        auto mkrP1M1 = ASMTMarker::With();
        mkrP1M1->setName("Marker1");
        mkrP1M1->setPosition3D(0, 0, 0);
        mkrP1M1->setRotationMatrix(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1);
        part1->addMarker(mkrP1M1);

        auto joint = ASMTRevoluteJoint::With();
        joint->setName("Joint1");
        joint->setMarkerI(mkrAM1);
        joint->setMarkerJ(mkrP1M1);
        assembly->addJoint(joint);

        auto constantGravity = ASMTConstantGravity::With();
        constantGravity->setg(gravityX, gravityY, gravityZ);
        assembly->setConstantGravity(constantGravity);

        auto simulationParameters = ASMTSimulationParameters::With();
        simulationParameters->settstart(0.0);
        simulationParameters->settend(2.0);
        simulationParameters->sethmin(1.0e-9);
        simulationParameters->sethmax(1.0);
        simulationParameters->sethout(0.02);
        simulationParameters->seterrorTol(1.0e-8);
        assembly->setSimulationParameters(simulationParameters);
        return assembly;
    }

    std::string optionalAssemblyItemComparisonWith(
        const std::string &label,
        const std::shared_ptr<ASMTItem> &item,
        const std::shared_ptr<ASMTItem> &otherItem)
    {
        if (!item && !otherItem)
        {
            return std::string{};
        }
        if (!item)
        {
            return "Missing " + label + ".\n";
        }
        if (!otherItem)
        {
            return "Missing comparison " + label + ".\n";
        }
        return item->reportComparisonWith(otherItem);
    }
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::With()
{
    auto inst = std::make_shared<ASMTAssembly>();
    inst->initialize();
    return inst;
}

void ASMTAssembly::initialize()
{
    ASMTSpatialContainer::initialize();
    setConstantGravity(ASMTConstantGravity::With());
    setSimulationParameters(ASMTSimulationParameters::With());
    setAnimationParameters(ASMTAnimationParameters::With());
    addTime(ASMTTime::With());
    asmtUnits = Units::With();
    times = FullRow<double>::With();
}

void ASMTAssembly::runSinglePendulumSuperSimplified()
{
    // In this version we skip declaration of variables that don't need as they use default values.
    auto assembly = ASMTAssembly::With();

    assembly->setName("Assembly1");

    auto mkrI = ASMTMarker::With();
    mkrI->setName("Marker1");
    assembly->addMarker(mkrI);

    auto part1 = ASMTPart::With();
    part1->setName("Part1");
    part1->setPosition3D(-0.1, -0.1, -0.1);
    assembly->addPart(part1);

    auto mkrJ = ASMTMarker::With();
    mkrJ->setName("Marker1");
    mkrJ->setPosition3D(0.1, 0.1, 0.1);
    part1->addMarker(mkrJ);

    auto joint = ASMTFixedJoint::With();
    joint->setName("Joint1");
    joint->setMarkerI(mkrI);
    joint->setMarkerJ(mkrJ);
    assembly->addJoint(joint);

    auto simulationParameters = ASMTSimulationParameters::With();
    simulationParameters->settstart(0.0);
    simulationParameters->settend(0.0); // tstart == tend Initial Conditions only.
    simulationParameters->sethmin(1.0e-9);
    simulationParameters->sethmax(1.0);
    simulationParameters->sethout(0.04);
    simulationParameters->seterrorTol(1.0e-6);
    assembly->setSimulationParameters(simulationParameters);

    assembly->runKINEMATIC();
}

void ASMTAssembly::runSinglePendulumSuperSimplified2()
{
    // In this version we skip declaration of variables that don't need as they use default values.
    auto assembly = ASMTAssembly::With();
    assembly->setName("OndselAssembly");

    auto mkrAM1 = ASMTMarker::With();
    mkrAM1->setName("marker1");
    assembly->addMarker(mkrAM1);

    auto part1 = ASMTPart::With();
    part1->setName("part1");
    assembly->addPart(part1);

    auto mkrP1Fix = ASMTMarker::With();
    mkrP1Fix->setName("FixingMarker");
    part1->addMarker(mkrP1Fix);

    auto mkrP1M2 = ASMTMarker::With();
    mkrP1M2->setName("marker2");
    mkrP1M2->setPosition3D(20.0, 10.0, 0.0);
    part1->addMarker(mkrP1M2);

    auto part2 = ASMTPart::With();
    part2->setName("part2");
    part2->setPosition3D(20.0, 10.0, 0.0);
    assembly->addPart(part2);

    auto mkrP2M2 = ASMTMarker::With();
    mkrP2M2->setName("marker2");
    mkrP2M2->setPosition3D(50.0, 10.0, 0.0);
    part2->addMarker(mkrP2M2);

    /*Ground joint*/
    auto joint = ASMTFixedJoint::With();
    joint->setName("Joint1");
    joint->setMarkerI(mkrAM1);
    joint->setMarkerJ(mkrP1Fix);
    assembly->addJoint(joint);

    auto joint2 = ASMTRevoluteJoint::With();
    joint2->setName("Joint2");
    joint2->setMarkerI(mkrP1M2);
    joint2->setMarkerJ(mkrP2M2);
    assembly->addJoint(joint2);

    auto simulationParameters = ASMTSimulationParameters::With();
    simulationParameters->settstart(0.0);
    simulationParameters->settend(0.0); // tstart == tend Initial Conditions only.
    simulationParameters->sethmin(1.0e-9);
    simulationParameters->sethmax(1.0);
    simulationParameters->sethout(0.04);
    simulationParameters->seterrorTol(1.0e-6);
    assembly->setSimulationParameters(simulationParameters);

    assembly->runKINEMATIC();
}

void ASMTAssembly::runSinglePendulumSimplified()
{
    auto assembly = ASMTAssembly::With();

    assembly->setNotes("");
    assembly->setName("Assembly1");
    assembly->setPosition3D(0, 0, 0);
    assembly->setRotationMatrix(
        1, 0, 0,
        0, 1, 0,
        0, 0, 1);
    assembly->setVelocity3D(0, 0, 0);
    assembly->setOmega3D(0, 0, 0);

    auto mkrAM1 = ASMTMarker::With();
    mkrAM1->setName("Marker1");
    mkrAM1->setPosition3D(0, 0, 0);
    mkrAM1->setRotationMatrix(
        1, 0, 0,
        0, 1, 0,
        0, 0, 1);
    assembly->addMarker(mkrAM1);

    auto part1 = ASMTPart::With();
    part1->setName("Part1");
    part1->setPosition3D(-0.1, -0.1, -0.1);
    part1->setRotationMatrix(
        1, 0, 0,
        0, 1, 0,
        0, 0, 1);
    part1->setVelocity3D(0, 0, 0);
    part1->setOmega3D(0, 0, 0);
    assembly->addPart(part1);

    auto massMarker = ASMTMarkerTemp::With();
    massMarker->setMass(0.2);
    massMarker->setDensity(10.0);
    massMarker->setMomentOfInertias(8.3333333333333e-4, 0.016833333333333, 0.017333333333333);
    massMarker->setPosition3D(0.5, 0.1, 0.05);
    massMarker->setRotationMatrix(
        1, 0, 0,
        0, 1, 0,
        0, 0, 1);
    part1->setPrincipalMassMarker(massMarker);

    auto mkrP1M1 = ASMTMarker::With();
    mkrP1M1->setName("Marker1");
    mkrP1M1->setPosition3D(0.1, 0.1, 0.1);
    mkrP1M1->setRotationMatrix(
        1, 0, 0,
        0, 1, 0,
        0, 0, 1);
    part1->addMarker(mkrP1M1);

    auto joint = ASMTRevoluteJoint::With();
    joint->setName("Joint1");
    joint->setMarkerI(mkrAM1);
    joint->setMarkerJ(mkrP1M1);
    assembly->addJoint(joint);

    auto motion = ASMTRotationalMotion::With();
    motion->setName("Motion1");
    motion->setMotionJoint("/Assembly1/Joint1");
    motion->setRotationZ("0.0");
    assembly->addMotion(motion);

    auto constantGravity = ASMTConstantGravity::With();
    constantGravity->setg(0.0, 0.0, 0.0);
    assembly->setConstantGravity(constantGravity);

    auto simulationParameters = ASMTSimulationParameters::With();
    simulationParameters->settstart(0.0);
    simulationParameters->settend(0.0); // tstart == tend Initial Conditions only.
    simulationParameters->sethmin(1.0e-9);
    simulationParameters->sethmax(1.0);
    simulationParameters->sethout(0.04);
    simulationParameters->seterrorTol(1.0e-6);
    assembly->setSimulationParameters(simulationParameters);

    assembly->runKINEMATIC();
}

void ASMTAssembly::runSinglePendulum()
{
    auto assembly = ASMTAssembly::With();
    std::string str = "";
    assembly->setNotes(str);
    str = "Assembly1";
    assembly->setName(str);
    auto pos3D = std::make_shared<FullColumn<double>>(ListD{0, 0, 0});
    assembly->setPosition3D(pos3D);
    auto rotMat = FullMatrix<double>::With(ListListD{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}});
    assembly->setRotationMatrix(rotMat);
    auto vel3D = std::make_shared<FullColumn<double>>(ListD{0, 0, 0});
    assembly->setVelocity3D(vel3D);
    auto ome3D = std::make_shared<FullColumn<double>>(ListD{0, 0, 0});
    assembly->setOmega3D(ome3D);
    //
    auto mkrAM1 = ASMTMarker::With();
    str = "Marker1";
    mkrAM1->setName(str);
    pos3D = std::make_shared<FullColumn<double>>(ListD{0, 0, 0});
    mkrAM1->setPosition3D(pos3D);
    rotMat = FullMatrix<double>::With(ListListD{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}});
    mkrAM1->setRotationMatrix(rotMat);
    assembly->addMarker(mkrAM1);
    //
    auto part1 = ASMTPart::With();
    str = "Part1";
    part1->setName(str);
    pos3D = std::make_shared<FullColumn<double>>(ListD{-0.1, -0.1, -0.1});
    part1->setPosition3D(pos3D);
    rotMat = FullMatrix<double>::With(ListListD{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}});
    part1->setRotationMatrix(rotMat);
    vel3D = std::make_shared<FullColumn<double>>(ListD{0, 0, 0});
    part1->setVelocity3D(vel3D);
    ome3D = std::make_shared<FullColumn<double>>(ListD{0, 0, 0});
    part1->setOmega3D(ome3D);
    assembly->addPart(part1);
    //
    auto massMarker = ASMTMarkerTemp::With();
    massMarker->setMass(0.2);
    massMarker->setDensity(10.0);
    auto aJ = DiagonalMatrix<double>::With(ListD{8.3333333333333e-4, 0.016833333333333, 0.017333333333333});
    massMarker->setMomentOfInertias(aJ);
    pos3D = std::make_shared<FullColumn<double>>(ListD{0.5, 0.1, 0.05});
    massMarker->setPosition3D(pos3D);
    rotMat = FullMatrix<double>::With(ListListD{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}});
    massMarker->setRotationMatrix(rotMat);
    part1->setPrincipalMassMarker(massMarker);
    //
    auto mkrP1M1 = ASMTMarker::With();
    str = "Marker1";
    mkrP1M1->setName(str);
    pos3D = std::make_shared<FullColumn<double>>(ListD{0.1, 0.1, 0.1});
    mkrP1M1->setPosition3D(pos3D);
    rotMat = FullMatrix<double>::With(ListListD{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}});
    mkrP1M1->setRotationMatrix(rotMat);
    part1->addMarker(mkrP1M1);
    //
    auto joint = ASMTRevoluteJoint::With();
    str = "Joint1";
    joint->setName(str);
    joint->setMarkerI(mkrAM1);
    joint->setMarkerJ(mkrP1M1);
    assembly->addJoint(joint);
    //
    auto motion = ASMTRotationalMotion::With();
    str = "Motion1";
    motion->setName(str);
    str = "/Assembly1/Joint1";
    motion->setMotionJoint(str);
    str = "0.0";
    motion->setRotationZ(str);
    assembly->addMotion(motion);
    //
    auto constantGravity = ASMTConstantGravity::With();
    auto gAcceleration = FullColumn<double>::With(3, 0.0);
    constantGravity->setg(gAcceleration);
    assembly->setConstantGravity(constantGravity);
    //
    auto simulationParameters = ASMTSimulationParameters::With();
    simulationParameters->settstart(0.0);
    simulationParameters->settend(0.0); // tstart == tend Initial Conditions only.
    simulationParameters->sethmin(1.0e-9);
    simulationParameters->sethmax(1.0);
    simulationParameters->sethout(0.04);
    simulationParameters->seterrorTol(1.0e-6);
    assembly->setSimulationParameters(simulationParameters);
    //
    assembly->runKINEMATIC();
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::pointPendulumRevJt_XY()
{
    return pointPendulumRevJt(
        {1, 0, 0,
         0, 1, 0,
         0, 0, 1},
        0.0, -9.81, 0.0);
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::pointPendulumRevJt_YZ()
{
    return pointPendulumRevJt(
        {0, 0, 1,
         1, 0, 0,
         0, 1, 0},
        0.0, 0.0, -9.81);
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::pointPendulumRevJt_ZX()
{
    return pointPendulumRevJt(
        {1, 0, 0,
         0, 0, 1,
         1, 0, 0},
        -9.81, 0.0, 0.0);
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::pointPendulumRevJt_XZ()
{
    return pointPendulumRevJt(
        {1, 0, 0,
         0, 0, -1,
         0, 1, 0},
        0.0, 0.0, -9.81);
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::pointPendulumRevJt_YX()
{
    return pointPendulumRevJt(
        {0, 1, 0,
         1, 0, 0,
         0, 0, -1},
        -9.81, 0.0, 0.0);
}

ASMTAssembly::SimplePendulumMotion ASMTAssembly::exactSimplePendulumMotion(
    double time,
    double length,
    double gravity,
    double initialTheta,
    double initialOmega)
{
    // Origin is at pivot.
    // x is to the right.
    // y is up
    // Point mass hanging down.
    // Positive gravity is down.
    // theta is counter clockwise rotation from down direction (-y dir).
    if (length <= 0.0)
        throw SimulationStoppingError("Simple pendulum length must be positive.");
    if (gravity <= 0.0)
        throw SimulationStoppingError("Simple pendulum gravity must be positive.");

    const auto naturalFrequency = std::sqrt(gravity / length);
    const auto energy = (0.5 * initialOmega * initialOmega) - (naturalFrequency * naturalFrequency * std::cos(initialTheta));
    if (energy >= naturalFrequency * naturalFrequency)
    {
        throw SimulationStoppingError("Exact simple pendulum motion supports bounded oscillation only.");
    }

    const auto thetaMax = std::acos(-energy / (naturalFrequency * naturalFrequency));
    const auto modulus = std::sin(0.5 * thetaMax);
    double theta = 0.0;
    double omega = 0.0;

    if (std::abs(modulus) <= SmallPendulumAmplitude)
    {
        theta = initialTheta * std::cos(naturalFrequency * time) + (initialOmega / naturalFrequency) * std::sin(naturalFrequency * time);
        omega = -initialTheta * naturalFrequency * std::sin(naturalFrequency * time) + initialOmega * std::cos(naturalFrequency * time);
    }
    else
    {
        const auto initialSn = std::sin(0.5 * initialTheta) / modulus;
        const auto u0 = inverseJacobiSn(initialSn, modulus);
        auto direction = signum(initialOmega);
        if (direction == 0.0)
            direction = initialTheta >= 0.0 ? -1.0 : 1.0;
        const auto u = u0 + (direction * naturalFrequency * time);
        const auto [sn, cn] = jacobiSnCnFromU(u, modulus);
        theta = 2.0 * std::asin(std::clamp(modulus * sn, -1.0, 1.0));
        omega = 2.0 * modulus * cn * direction * naturalFrequency;
        if (std::abs(omega) <= SmallPendulumVelocity)
            omega = 0.0;
    }

    SimplePendulumMotion motion;
    motion.theta = theta;
    motion.omega = omega;
    // theta = 0 hangs straight down, so positive theta moves the bob toward +x.
    motion.x = length * std::sin(theta);
    motion.y = -length * std::cos(theta);
    motion.vx = length * std::cos(theta) * omega;
    motion.vy = length * std::sin(theta) * omega;
    return motion;
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::assemblyFromFile(const std::string &fileName)
{
    auto lines = linesFromFile(fileName);
    auto assembly = ASMTAssembly::With();
    assembly->readStringNoSpacesOffTopEqualOrThrow(lines, "Assembly");
    assembly->setinFileName(fileName);
    assembly->parseASMT(lines);
    return assembly;
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::runDynFile(const std::string &fileName)
{
    auto assembly = ASMTAssembly::assemblyFromFile(fileName);
    const std::string &str("\n\n\nStarting DYNAMIC simulation");
    assembly->logString(str);
    assembly->runDYNAMIC();
    return assembly;
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::runKineFile(const std::string &fileName)
{
    auto assembly = ASMTAssembly::assemblyFromFile(fileName);
    const std::string &str("\n\n\nStarting KINEMATIC simulation");
    assembly->logString(str);
    assembly->runKINEMATIC();
    return assembly;
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::runQuasiStaticFile(const std::string &fileName)
{
    auto assembly = ASMTAssembly::assemblyFromFile(fileName);
    const std::string &str("\n\n\nStarting QUASI STATIC simulation");
    assembly->logString(str);
    assembly->runQUASISTATIC();
    return assembly;
}

std::vector<std::string> ASMTAssembly::linesFromFile(const std::string &fileName)
{
    std::ifstream stream(fileName);
    if (stream.fail())
    {
        std::cout << "Failed to open: "
                  << std::filesystem::absolute(fileName) << "\n";
        std::cout << "Current working directory: "
                  << std::filesystem::current_path() << "\n";
        throw std::invalid_argument("File not found.");
    }
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(stream, line))
    {
        lines.push_back(line);
    }
    if (lines.empty() || !isASMTHeader(lines.front()))
    {
        throw std::invalid_argument("Invalid ASMT file header.");
    }
    lines.erase(lines.begin());
    return lines;
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::readWriteKineFile(const std::string &fileName)
{
    auto assembly = ASMTAssembly::runKineFile(fileName);
    assembly->outputFile("tempAssembly.asmt");
    assembly->combineInputInitialConditionsWithCalculationResults();
    return assembly;
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::readWriteDynFile(const std::string &fileName)
{
    auto assembly = ASMTAssembly::runDynFile(fileName);
    assembly->outputFile("tempAssembly.asmt");
    assembly->combineInputInitialConditionsWithCalculationResults();
    return assembly;
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::readWriteDynFile2(const std::string &infilename, const std::string &outfilename)
{
    auto assembly = ASMTAssembly::runDynFile(infilename);
    assembly->setoutFileName(outfilename);
    assembly->outputFile("tempAssembly.asmt");
    // Create tempAssembly2.asmt from input data from filename and TimeSeries from tempAssembly.asmt
    // Otherwise redundant constraints may not be the same even with very very small differences in input.
    assembly->combineInputInitialConditionsWithCalculationResults();

    namespace fs = std::filesystem;
    if (fs::exists("tempAssembly2.asmt"))
    {
        try
        {
            fs::copy_file("tempAssembly2.asmt", assembly->outFileName, fs::copy_options::overwrite_existing);
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "COPY TO DESTINATION FAILED: " << assembly->outFileName << '\n';
        }
    }
    else
    {
        std::cerr << "SOLVER ERROR: tempAssembly2.asmt not found." << std::endl;
    }
    return assembly;
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::readWriteReadDynFile(const std::string &fileName)
{
    auto assembly = ASMTAssembly::readWriteDynFile(fileName);
    auto assembly2 = ASMTAssembly::runDynFile("tempAssembly2.asmt");
    return assembly2;
}

std::shared_ptr<ASMTAssembly> ASMTAssembly::runDraggingTest()
{
    auto assembly = ASMTAssembly::assemblyFromFile("../testapp/dragCrankSlider.asmt");
    auto dragPart = assembly->parts->at(0);
    auto dragParts = std::make_shared<std::vector<std::shared_ptr<ASMTPart>>>();
    dragParts->push_back(dragPart);
    assembly->runPreDrag(); // Do this before first drag
    FColDsptr pos3D, delta;
    pos3D = dragPart->position3D;
    delta = std::make_shared<FullColumn<double>>(ListD{0.1, 0.2, 0.3});
    dragPart->updateMbDFromPosition3D(pos3D->plusFullColumn(delta));
    assembly->runDragStep(dragParts);
    pos3D = dragPart->position3D;
    delta = std::make_shared<FullColumn<double>>(ListD{0.3, 0.2, 0.1});
    dragPart->updateMbDFromPosition3D(pos3D->plusFullColumn(delta));
    assembly->runDragStep(dragParts);
    assembly->runPostDrag(); // Do this after last drag
    return assembly;
}

ASMTAssembly *ASMTAssembly::root()
{
    return this;
}

void ASMTAssembly::setNotes(const std::string &str)
{
    notes = str;
}

void ASMTAssembly::parseASMT(std::vector<std::string> &lines)
{
    readNotes(lines);
    readName(lines);
    readPosition3D(lines);
    readRotationMatrix(lines);
    readVelocity3D(lines);
    readOmega3D(lines);
    readRefPoints(lines);
    readRefCurves(lines);
    readRefSurfaces(lines);
    readParts(lines);
    readKinematicIJs(lines);
    readConstraintSets(lines);
    readForcesTorques(lines);
    readConstantGravity(lines);
    readSimulationParameters(lines);
    readAnimationParameters(lines);
    readSeries(lines);
}

void ASMTAssembly::readNotes(std::vector<std::string> &lines)
{
    assert(lines[0] == "\tNotes");
    lines.erase(lines.begin());
    notes = readStringTrimmedOffTop(lines);
}

void ASMTAssembly::readParts(std::vector<std::string> &lines)
{
    assert(lines[0] == "\tParts");
    lines.erase(lines.begin());
    parts->clear();
    auto it = std::find(lines.begin(), lines.end(), "\tKinematicIJs");
    std::vector<std::string> partsLines(lines.begin(), it);
    while (!partsLines.empty())
    {
        readPart(partsLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTAssembly::readPart(std::vector<std::string> &lines)
{
    assert(lines[0] == "\t\tPart");
    lines.erase(lines.begin());
    auto part = ASMTPart::With();
    part->owner = this;
    part->parseASMT(lines);
    parts->push_back(part);
}

void ASMTAssembly::readKinematicIJs(std::vector<std::string> &lines)
{
    assert(lines[0] == "\tKinematicIJs");
    lines.erase(lines.begin());
    kinematicIJs->clear();
    auto it = std::find(lines.begin(), lines.end(), "\tConstraintSets");
    std::vector<std::string> kinematicIJsLines(lines.begin(), it);
    while (!kinematicIJsLines.empty())
    {
        readKinematicIJ(kinematicIJsLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTAssembly::readKinematicIJ(std::vector<std::string> &)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTAssembly::readConstraintSets(std::vector<std::string> &lines)
{
    assert(lines[0] == "\tConstraintSets");
    lines.erase(lines.begin());
    readJoints(lines);
    readMotions(lines);
    readLimits(lines);
    readGeneralConstraintSets(lines);
}

void ASMTAssembly::readJoints(std::vector<std::string> &lines)
{
    assert(lines[0] == "\t\tJoints");
    lines.erase(lines.begin());
    joints->clear();
    auto it = std::find(lines.begin(), lines.end(), "\t\tMotions");
    std::vector<std::string> jointsLines(lines.begin(), it);
    std::shared_ptr<ASMTJoint> joint;
    while (!jointsLines.empty())
    {
        if (jointsLines[0] == "\t\t\tAngleJoint")
        {
            joint = ASMTAngleJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tGearJoint")
        {
            joint = ASMTGearJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tNoRotationJoint")
        {
            joint = ASMTNoRotationJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tParallelAxesJoint")
        {
            joint = ASMTParallelAxesJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tPerpendicularJoint")
        {
            joint = ASMTPerpendicularJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tRackPinionJoint")
        {
            joint = ASMTRackPinionJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tScrewJoint")
        {
            joint = ASMTScrewJoint::With();
        }
        // AtPointJoints
        else if (jointsLines[0] == "\t\t\tConstantVelocityJoint")
        {
            joint = ASMTConstantVelocityJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tFixedJoint")
        {
            joint = ASMTFixedJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tRevoluteJoint")
        {
            joint = ASMTRevoluteJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tSphericalJoint")
        {
            joint = ASMTSphericalJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tUniversalJoint")
        {
            joint = ASMTUniversalJoint::With();
        }
        // CompoundJoints
        else if (jointsLines[0] == "\t\t\tSphSphJoint")
        {
            joint = ASMTSphSphJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tCylSphJoint")
        {
            joint = ASMTCylSphJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tRevCylJoint")
        {
            joint = ASMTRevCylJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tRevRevJoint")
        {
            joint = ASMTRevRevJoint::With();
        }
        // InLineJoints
        else if (jointsLines[0] == "\t\t\tCylindricalJoint")
        {
            joint = ASMTCylindricalJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tPointInLineJoint")
        {
            joint = ASMTPointInLineJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tTranslationalJoint")
        {
            joint = ASMTTranslationalJoint::With();
        }
        // InPlaneJoints
        else if (jointsLines[0] == "\t\t\tLineInPlaneJoint")
        {
            joint = ASMTLineInPlaneJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tPlanarJoint")
        {
            joint = ASMTPlanarJoint::With();
        }
        else if (jointsLines[0] == "\t\t\tPointInPlaneJoint")
        {
            joint = ASMTPointInPlaneJoint::With();
        }
        else
        {
            throw SimulationStoppingError("To be implemented.");
        }
        jointsLines.erase(jointsLines.begin());
        joint->owner = this;
        joint->parseASMT(jointsLines);
        joints->push_back(joint);
    }
    lines.erase(lines.begin(), it);
}

void ASMTAssembly::readMotions(std::vector<std::string> &lines)
{
    assert(lines[0] == "\t\tMotions");
    lines.erase(lines.begin());
    motions->clear();
    auto it = std::find(lines.begin(), lines.end(), "\t\tLimits");
    if (it == lines.end())
    {
        it = std::find(lines.begin(), lines.end(), "\t\tGeneralConstraintSets");
    }
    std::vector<std::string> motionsLines(lines.begin(), it);
    std::shared_ptr<ASMTMotion> motion;
    while (!motionsLines.empty())
    {
        if (motionsLines[0] == "\t\t\tRotationalMotion")
        {
            motion = ASMTRotationalMotion::With();
        }
        else if (motionsLines[0] == "\t\t\tTranslationalMotion")
        {
            motion = ASMTTranslationalMotion::With();
        }
        else if (motionsLines[0] == "\t\t\tGeneralMotion")
        {
            motion = ASMTGeneralMotion::With();
        }
        else if (motionsLines[0] == "\t\t\tAllowRotation")
        {
            motion = ASMTAllowRotation::With();
        }
        else
        {
            throw SimulationStoppingError("To be implemented.");
        }
        motionsLines.erase(motionsLines.begin());
        motion->owner = this;
        motion->parseASMT(motionsLines);
        motions->push_back(motion);
        motion->initMarkers();
    }
    lines.erase(lines.begin(), it);
}

void ASMTAssembly::readLimits(std::vector<std::string> &lines)
{
    if (lines[0] != "\t\tLimits")
    {
        return;
    }
    lines.erase(lines.begin());
    limits->clear();
    auto it = std::find(lines.begin(), lines.end(), "\t\tGeneralConstraintSets");
    std::vector<std::string> limitsLines(lines.begin(), it);
    std::shared_ptr<ASMTLimit> limit;
    while (!limitsLines.empty())
    {
        if (limitsLines[0] == "\t\t\tRotationLimit")
        {
            limit = ASMTRotationLimit::With();
        }
        else if (limitsLines[0] == "\t\t\tTranslationLimit")
        {
            limit = ASMTTranslationLimit::With();
        }
        else
        {
            throw SimulationStoppingError("To be implemented.");
        }
        limitsLines.erase(limitsLines.begin());
        limit->parseASMT(limitsLines);
        limits->push_back(limit);
        limit->owner = this;
        limit->initMarkers();
    }
    lines.erase(lines.begin(), it);
}

void ASMTAssembly::readGeneralConstraintSets(std::vector<std::string> &lines) const
{
    assert(lines[0] == "\t\tGeneralConstraintSets");
    lines.erase(lines.begin());
    constraintSets->clear();
    auto it = std::find(lines.begin(), lines.end(), "\tForceTorques");
    std::vector<std::string> generalConstraintSetsLines(lines.begin(), it);
    while (!generalConstraintSetsLines.empty())
    {
        throw SimulationStoppingError("To be implemented.");
    }
    lines.erase(lines.begin(), it);
}

void ASMTAssembly::readForcesTorques(std::vector<std::string> &lines)
{
    assert(lines[0] == "\tForceTorques"); // Spelling is not consistent in asmt file.
    lines.erase(lines.begin());
    forcesTorques->clear();
    auto it = std::find(lines.begin(), lines.end(), "\tConstantGravity");
    std::vector<std::string> forcesTorquesLines(lines.begin(), it);
    std::shared_ptr<ASMTForceTorque> forceTorque;
    while (!forcesTorquesLines.empty())
    {
        if (forcesTorquesLines[0] == "\t\tInLineForceTorque")
        {
            forceTorque = ASMTForceTorqueInLine::With();
        }
        else if (forcesTorquesLines[0] == "\t\tGeneralForceTorque")
        {
            forceTorque = ASMTForceTorqueGeneral::With();
        }
        else
        {
            throw SimulationStoppingError("To be implemented.");
        }

        forcesTorquesLines.erase(forcesTorquesLines.begin());
        forceTorque->owner = this;
        forceTorque->parseASMT(forcesTorquesLines);
        forcesTorques->push_back(forceTorque);
    }
    lines.erase(lines.begin(), it);
}

void ASMTAssembly::readConstantGravity(std::vector<std::string> &lines)
{
    assert(lines[0] == "\tConstantGravity");
    lines.erase(lines.begin());
    constantGravity = ASMTConstantGravity::With();
    constantGravity->owner = this;
    constantGravity->parseASMT(lines);
}

void ASMTAssembly::readSimulationParameters(std::vector<std::string> &lines)
{
    assert(lines[0] == "\tSimulationParameters");
    lines.erase(lines.begin());
    simulationParameters = ASMTSimulationParameters::With();
    simulationParameters->owner = this;
    simulationParameters->parseASMT(lines);
}

void ASMTAssembly::readAnimationParameters(std::vector<std::string> &lines)
{
    assert(lines[0] == "\tAnimationParameters");
    lines.erase(lines.begin());
    animationParameters = ASMTAnimationParameters::With();
    animationParameters->owner = this;
    animationParameters->parseASMT(lines);
}

void ASMTAssembly::readSeries(std::vector<std::string> &lines)
{
    while (!lines.empty() && (lines[0].find("Series") != std::string::npos))
    {
        if (lines[0].find("TimeSeries") != std::string::npos)
        {
            readTimeSeries(lines);
        }
        else if (lines[0].find("AssemblySeries") != std::string::npos)
        {
            readAssemblySeries(lines);
        }
        else if (lines[0].find("PartSeries") != std::string::npos)
        {
            readPartSeries(lines);
        }
        else if (lines[0].find("JointSeries") != std::string::npos)
        {
            readJointSeries(lines);
        }
        else if (lines[0].find("MotionSeries") != std::string::npos)
        {
            readMotionSeries(lines);
        }
        else if (lines[0].find("ForceTorqueSeries") != std::string::npos)
        {
            readForceTorqueSeries(lines);
        }
        else if (lines[0].find("AllowRotationSeries") != std::string::npos)
        {
            readAllowRotationSeries(lines);
        }
        else
        {
            throw SimulationStoppingError("To be implemented.");
        }
    }
}

void ASMTAssembly::readTimeSeries(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    readStringNoSpacesOffTopEqualOrThrow(lines, "TimeSeries");
    assert(lines[0].find("Number\tInput") != std::string::npos);
    lines.erase(lines.begin());
    readTimes(lines);
}

void ASMTAssembly::readTimes(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    std::string str = lines[0];
    std::string substr = "Time\tInput";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    itimes = readRowOfDoubles(str);
    // Need to insert element for input state at front of itimes.
    if (itimes->empty())
    {
        itimes->push_back(0.0);
    }
    else
    {
        // Duplicate time0.
        itimes->insert(itimes->begin(), itimes->at(0));
    }
    lines.erase(lines.begin());
}

void ASMTAssembly::readPartSeriesMany(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    assert(lines[0].find("PartSeries") != std::string::npos);
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string &s)
                           { return s.find("JointSeries") != std::string::npos; });
    std::vector<std::string> partSeriesLines(lines.begin(), it);
    while (!partSeriesLines.empty())
    {
        readPartSeries(partSeriesLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTAssembly::readJointSeriesMany(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    assert(lines[0].find("JointSeries") != std::string::npos);
    auto it = std::find_if(lines.begin(), lines.end(), [](const std::string &s)
                           { return s.find("tionSeries") != std::string::npos; });
    std::vector<std::string> jointSeriesLines(lines.begin(), it);
    while (!jointSeriesLines.empty())
    {
        readJointSeries(jointSeriesLines);
    }
    lines.erase(lines.begin(), it);
}

void ASMTAssembly::readAssemblySeries(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    std::string str = lines[0];
    std::string substr = "AssemblySeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    assert(fullName("") == seriesName);
    lines.erase(lines.begin());

    auto inxs2 = readSeriesOf(lines, "X");
    auto inys2 = readSeriesOf(lines, "Y");
    auto inzs2 = readSeriesOf(lines, "Z");
    auto inbryxs2 = readSeriesOf(lines, "Bryantx");
    auto inbryys2 = readSeriesOf(lines, "Bryanty");
    auto inbryzs2 = readSeriesOf(lines, "Bryantz");
    auto invxs2 = readSeriesOf(lines, "VX");
    auto invys2 = readSeriesOf(lines, "VY");
    auto invzs2 = readSeriesOf(lines, "VZ");
    auto inomexs2 = readSeriesOf(lines, "OmegaX");
    auto inomeys2 = readSeriesOf(lines, "OmegaY");
    auto inomezs2 = readSeriesOf(lines, "OmegaZ");
    auto inaxs2 = readSeriesOf(lines, "AX");
    auto inays2 = readSeriesOf(lines, "AY");
    auto inazs2 = readSeriesOf(lines, "AZ");
    auto inalpxs2 = readSeriesOf(lines, "AlphaX");
    auto inalpys2 = readSeriesOf(lines, "AlphaY");
    auto inalpzs2 = readSeriesOf(lines, "AlphaZ");

    for (size_t i = 0; i < inxs2->size(); ++i)
    {
        auto data = PosVelAccData::With();
        auto lambda = [&](FRowDsptr rowx, FRowDsptr rowy, FRowDsptr rowz) -> FColDsptr
        {
            auto col = FullColumn<double>::With(3);
            col->at(0) = rowx->at(i);
            col->at(1) = rowy->at(i);
            col->at(2) = rowz->at(i);
            return col;
        };
        data->rFfF = lambda(inxs2, inys2, inzs2);
        data->bryAngFf = EulerAngles<double>::With(lambda(inbryxs2, inbryys2, inbryzs2));
        data->vFfF = lambda(invxs2, invys2, invzs2);
        data->omeFfF = lambda(inomexs2, inomeys2, inomezs2);
        data->aFfF = lambda(inaxs2, inays2, inazs2);
        data->alpFfF = lambda(inalpxs2, inalpys2, inalpzs2);
        dataSeriesIn->push_back(data);
    }

    // readXs(lines);
    // readYs(lines);
    // readZs(lines);
    // readBryantxs(lines);
    // readBryantys(lines);
    // readBryantzs(lines);
    // readVXs(lines);
    // readVYs(lines);
    // readVZs(lines);
    // readOmegaXs(lines);
    // readOmegaYs(lines);
    // readOmegaZs(lines);
    // readAXs(lines);
    // readAYs(lines);
    // readAZs(lines);
    // readAlphaXs(lines);
    // readAlphaYs(lines);
    // readAlphaZs(lines);
}

void ASMTAssembly::readPartSeries(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    std::string str = lines[0];
    std::string substr = "PartSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart> &prt)
                           { return prt->fullName("") == seriesName; });
    auto part = *it;
    part->readPartSeries(lines);
}

void ASMTAssembly::readJointSeries(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    std::string str = lines[0];
    std::string substr = "JointSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    auto it = std::find_if(joints->begin(), joints->end(), [&](const std::shared_ptr<ASMTJoint> &jt)
                           { return jt->fullName("") == seriesName; });
    auto joint = *it;
    joint->readJointSeries(lines);
}

void ASMTAssembly::readMotionSeriesMany(std::vector<std::string> &lines)
{
    while (!lines.empty())
    {
        assert(lines[0].find("tionSeries") != std::string::npos);
        readMotionSeries(lines);
    }
}

void ASMTAssembly::readMotionSeries(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    std::string str = lines[0];
    std::string substr = "tionSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    auto it = std::find_if(motions->begin(), motions->end(), [&](const std::shared_ptr<ASMTMotion> &jt)
                           { return jt->fullName("") == seriesName; });
    auto motion = *it;
    motion->readMotionSeries(lines);
}

void ASMTAssembly::readForceTorqueSeries(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    std::string str = lines[0];
    std::string substr = "ForceTorqueSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    auto it = std::find_if(forcesTorques->begin(), forcesTorques->end(), [&](const std::shared_ptr<ASMTForceTorque> &jt)
                           { return jt->fullName("") == seriesName; });
    auto forcesTorque = *it;
    forcesTorque->readForceTorqueSeries(lines);
}

void ASMTAssembly::readAllowRotationSeries(std::vector<std::string> &lines)
{
    if (lines.empty())
        return;
    std::string str = lines[0];
    std::string substr = "AllowRotationSeries";
    auto pos = str.find(substr);
    assert(pos != std::string::npos);
    str.erase(0, pos + substr.length());
    auto seriesName = readString(str);
    auto it = std::find_if(motions->begin(), motions->end(), [&](const std::shared_ptr<ASMTMotion> &jt)
                           { return jt->fullName("") == seriesName; });
    auto motion = *it;
    motion->readAllowRotationSeries(lines);
}

void ASMTAssembly::runDraggingLog(const std::string &fileName)
{
    std::ifstream stream(fileName);
    if (stream.fail())
    {
        throw std::invalid_argument("File not found.");
    }
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(stream, line))
    {
        lines.push_back(line);
    }
    readStringNoSpacesOffTopEqualOrThrow(lines, "runPreDrag");
    runPreDrag();
    while (lines[0].find("runDragStep") != std::string::npos)
    {
        readStringNoSpacesOffTopEqualOrThrow(lines, "runDragStep");
        auto dragParts = std::make_shared<std::vector<std::shared_ptr<ASMTPart>>>();
        while (lines[0].find("Name") != std::string::npos)
        {
            readStringNoSpacesOffTopEqualOrThrow(lines, "Name");
            auto dragPartName = readStringNoSpacesOffTop(lines);
            std::string longerName = "/" + name + "/" + dragPartName;
            auto dragPart = partAt(longerName);
            dragParts->push_back(dragPart);
            readStringNoSpacesOffTopEqualOrThrow(lines, "Position3D");
            auto dragPartPosition3D = readColumnOfDoublesOffTop(lines);
            dragPart->setPosition3D(dragPartPosition3D);
            readStringNoSpacesOffTopEqualOrThrow(lines, "RotationMatrix");
            auto dragPartRotationMatrix = std::make_shared<FullMatrix<double>>(3);
            for (size_t i = 0; i < 3; i++)
            {
                auto row = readRowOfDoublesOffTop(lines);
                dragPartRotationMatrix->atiput(i, row);
            }
            dragPart->setRotationMatrix(dragPartRotationMatrix);
        }
        runDragStep(dragParts);
    }
    readStringNoSpacesOffTopEqualOrThrow(lines, "runPostDrag");
    runPostDrag();
}

void ASMTAssembly::outputFor(AnalysisType type)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTAssembly::preMbDrun(std::shared_ptr<System> mbdSys)
{
    deleteMbD();
    createMbD();
}

void ASMTAssembly::postMbDrun()
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<std::vector<std::shared_ptr<ASMTItemIJ>>> ASMTAssembly::connectorList() const
{
    auto list = std::make_shared<std::vector<std::shared_ptr<ASMTItemIJ>>>();
    list->insert(list->end(), joints->begin(), joints->end());
    list->insert(list->end(), motions->begin(), motions->end());
    list->insert(list->end(), kinematicIJs->begin(), kinematicIJs->end());
    list->insert(list->end(), forcesTorques->begin(), forcesTorques->end());
    return list;
}

void ASMTAssembly::deleteMbD()
{
    ASMTSpatialContainer::deleteMbD();
    constantGravity->deleteMbD();
    asmtTime->deleteMbD();
    for (auto part : *parts)
    {
        part->deleteMbD();
    }
    for (auto joint : *joints)
    {
        joint->deleteMbD();
    }
    for (auto motion : *motions)
    {
        motion->deleteMbD();
    }
    for (auto limit : *limits)
    {
        limit->deleteMbD();
    }
    for (auto forceTorque : *forcesTorques)
    {
        forceTorque->deleteMbD();
    }
}

void ASMTAssembly::createMbD()
{
    mbdObject = mbdSystem;
    constantGravity->createMbD();
    asmtTime->createMbD();
    for (auto refPoint : *refPoints)
    {
        refPoint->createMbD();
    }
    for (auto refCurve : *refCurves)
    {
        refCurve->createMbD();
    }
    for (auto refSurface : *refSurfaces)
    {
        refSurface->createMbD();
    }
    std::sort(parts->begin(), parts->end(), [](std::shared_ptr<ASMTPart> a, std::shared_ptr<ASMTPart> b)
              { return a->name < b->name; });
    auto jointsMotions = std::make_shared<std::vector<std::shared_ptr<ASMTConstraintSet>>>();
    jointsMotions->insert(jointsMotions->end(), joints->begin(), joints->end());
    jointsMotions->insert(jointsMotions->end(), motions->begin(), motions->end());
    std::sort(jointsMotions->begin(), jointsMotions->end(), [](std::shared_ptr<ASMTConstraintSet> a, std::shared_ptr<ASMTConstraintSet> b)
              { return a->name < b->name; });
    std::sort(forcesTorques->begin(), forcesTorques->end(), [](std::shared_ptr<ASMTForceTorque> a, std::shared_ptr<ASMTForceTorque> b)
              { return a->name < b->name; });
    for (auto part : *parts)
    {
        part->createMbD();
    }
    for (auto joint : *jointsMotions)
    {
        joint->createMbD();
    }
    for (auto forceTorque : *forcesTorques)
    {
        forceTorque->createMbD();
    }

    // Create MbD in SI units
    auto asmtUnts = asmtUnits;
    auto mbdSysSolver = mbdSys()->systemSolver;
    mbdSysSolver->errorTolPosKine = simulationParameters->errorTolPosKine;
    mbdSysSolver->errorTolAccKine = simulationParameters->errorTolAccKine;
    mbdSysSolver->iterMaxPosKine = simulationParameters->iterMaxPosKine;
    mbdSysSolver->iterMaxAccKine = simulationParameters->iterMaxAccKine;
    mbdSysSolver->tstart = simulationParameters->tstart * asmtUnts->time;
    mbdSysSolver->tend = simulationParameters->tend * asmtUnts->time;
    mbdSysSolver->hmin = simulationParameters->hmin * asmtUnts->time;
    mbdSysSolver->hmax = simulationParameters->hmax * asmtUnts->time;
    mbdSysSolver->hout = simulationParameters->hout * asmtUnts->time;
    mbdSysSolver->corAbsTol = simulationParameters->corAbsTol;
    mbdSysSolver->corRelTol = simulationParameters->corRelTol;
    mbdSysSolver->intAbsTol = simulationParameters->intAbsTol;
    mbdSysSolver->intRelTol = simulationParameters->intRelTol;
    mbdSysSolver->iterMaxDyn = simulationParameters->iterMaxDyn;
    mbdSysSolver->orderMax = simulationParameters->orderMax;
    mbdSysSolver->translationLimit = simulationParameters->translationLimit * asmtUnts->length;
    mbdSysSolver->rotationLimit = simulationParameters->rotationLimit;
    // animationParameters = nullptr;
}

void ASMTAssembly::outputFile(std::string filename)
{
    std::ofstream os(filename);
    os << std::setprecision(std::numeric_limits<double>::max_digits10);
    //    try {
    os << "OndselSolver" << std::endl;
    storeOnLevel(os, 0);
}

void ASMTAssembly::storeOnLevel(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "Assembly");
    storeOnLevelNotes(os, level + 1);
    storeOnLevelName(os, level + 1);
    ASMTSpatialContainer::storeOnLevel(os, level);

    storeOnLevelParts(os, level + 1);
    storeOnLevelKinematicIJs(os, level + 1);
    storeOnLevelConstraintSets(os, level + 1);
    storeOnLevelForceTorques(os, level + 1);
    constantGravity->storeOnLevel(os, level + 1);
    simulationParameters->storeOnLevel(os, level + 1);
    animationParameters->storeOnLevel(os, level + 1);
    storeOnTimeSeries(os);
}

void ASMTAssembly::solve()
{
    auto simulationParameters = ASMTSimulationParameters::With();
    simulationParameters->settstart(0.0);
    simulationParameters->settend(0.0); // tstart == tend Initial Conditions only.
    simulationParameters->sethmin(1.0e-9);
    simulationParameters->sethmax(1.0);
    simulationParameters->sethout(0.04);
    simulationParameters->seterrorTol(1.0e-6);
    setSimulationParameters(simulationParameters);

    runKINEMATIC();
}

void ASMTAssembly::runPreDrag()
{
    mbdSystem = System::With();
    mbdSystem->externalSystem->asmtAssembly = this;
    try
    {
        mbdSystem->runPreDrag(mbdSystem);
    }
    catch (SimulationStoppingError ex)
    {
    }
}

void ASMTAssembly::runDragStep(std::shared_ptr<std::vector<std::shared_ptr<ASMTPart>>> dragParts) const
{
    auto dragMbDParts = std::make_shared<std::vector<std::shared_ptr<Part>>>();
    for (auto dragPart : *dragParts)
    {
        auto dragMbDPart = std::static_pointer_cast<Part>(dragPart->mbdObject);
        dragMbDParts->push_back(dragMbDPart);
    }
    mbdSystem->runDragStep(dragMbDParts);
}

void ASMTAssembly::runPostDrag()
{
    runPreDrag();
}

void ASMTAssembly::runKINEMATIC()
{
    mbdSystem = System::With();
    mbdSystem->externalSystem->asmtAssembly = this;
    try
    {
        mbdSystem->runKINEMATIC(mbdSystem);
    }
    catch (SimulationStoppingError ex)
    {
    }
}

void ASMTAssembly::runDYNAMIC()
{
    mbdSystem = System::With();
    mbdSystem->externalSystem->asmtAssembly = this;
    try
    {
        mbdSystem->runDYNAMIC(mbdSystem);
    }
    catch (SimulationStoppingError ex)
    {
    }
}

void ASMTAssembly::runQUASISTATIC()
{
    mbdSystem = System::With();
    mbdSystem->externalSystem->asmtAssembly = this;
    try
    {
        mbdSystem->runQUASISTATIC(mbdSystem);
    }
    catch (SimulationStoppingError ex)
    {
    }
}

std::shared_ptr<ASMTSpatialContainer> ASMTAssembly::spatialContainerAt(std::shared_ptr<ASMTAssembly> self, std::string &longname) const
{
    if ((self->fullName("")) == longname)
        return self;
    auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart> &prt)
                           { return prt->fullName("") == longname; });
    auto part = *it;
    return part;
}

std::shared_ptr<ASMTPart> ASMTAssembly::partAt(const std::string &longname) const
{
    for (auto part : *parts)
    {
        if (part->fullName("") == longname)
        {
            return part;
        }
    }
    return nullptr;
}

std::shared_ptr<ASMTMarker> ASMTAssembly::markerAt(std::string &longname) const
{
    for (auto refPoint : *refPoints)
    {
        for (auto marker : *refPoint->markers)
        {
            if (marker->fullName("") == longname)
                return marker;
        }
    }
    for (auto part : *parts)
    {
        for (auto refPoint : *part->refPoints)
        {
            for (auto marker : *refPoint->markers)
            {
                if (marker->fullName("") == longname)
                    return marker;
            }
        }
        if (part->principalMassMarker->fullName("") == longname)
            return part->principalMassMarker;
    }
    return nullptr;
}

std::shared_ptr<ASMTJoint> ASMTAssembly::jointAt(std::string &longname) const
{
    auto it = std::find_if(joints->begin(), joints->end(), [&](const std::shared_ptr<ASMTJoint> &jt)
                           { return jt->fullName("") == longname; });
    auto joint = *it;
    return joint;
}

std::shared_ptr<ASMTMotion> ASMTAssembly::motionAt(std::string &longname) const
{
    auto it = std::find_if(motions->begin(), motions->end(), [&](const std::shared_ptr<ASMTMotion> &mt)
                           { return mt->fullName("") == longname; });
    auto motion = *it;
    return motion;
}

std::shared_ptr<ASMTForceTorque> ASMTAssembly::forceTorqueAt(std::string &longname) const
{
    auto it = std::find_if(forcesTorques->begin(), forcesTorques->end(), [&](const std::shared_ptr<ASMTForceTorque> &mt)
                           { return mt->fullName("") == longname; });
    auto forceTorque = *it;
    return forceTorque;
}

FColDsptr ASMTAssembly::rOcmO()
{
    return FullColumn<double>::With(3, 0.0);
}

FColDsptr ASMTAssembly::vOcmO()
{
    return FullColumn<double>::With(3, 0.0);
}

FColDsptr ASMTAssembly::omeOpO()
{
    return FullColumn<double>::With(3, 0.0);
}

std::shared_ptr<ASMTTime> ASMTAssembly::geoTime() const
{
    return asmtTime;
}

void ASMTAssembly::updateFromMbD()
{
    auto data = dataFromMbD();
    dataSeries->push_back(data);

    xs->push_back(0.0);
    ys->push_back(0.0);
    zs->push_back(0.0);
    bryxs->push_back(0.0);
    bryys->push_back(0.0);
    bryzs->push_back(0.0);
    vxs->push_back(0.0);
    vys->push_back(0.0);
    vzs->push_back(0.0);
    omexs->push_back(0.0);
    omeys->push_back(0.0);
    omezs->push_back(0.0);
    axs->push_back(0.0);
    ays->push_back(0.0);
    azs->push_back(0.0);
    alpxs->push_back(0.0);
    alpys->push_back(0.0);
    alpzs->push_back(0.0);
    auto time = asmtTime->getValue();
    times->push_back(time);
    // std::cout << "Time = " << time << std::endl;
    for (auto part : *parts)
        part->updateFromMbD();
    for (auto joint : *joints)
        joint->updateFromMbD();
    for (auto motion : *motions)
        motion->updateFromMbD();
    for (auto forceTorque : *forcesTorques)
        forceTorque->updateFromMbD();
}

std::shared_ptr<StateData> ASMTAssembly::dataFromMbD()
{
    auto data = PosVelAccData::With();
    auto zeroCol = FullColumn<double>::With(3, 0.0);
    data->rFfF = zeroCol;
    data->aAFf = FullMatrix<double>::identitysptr(3);
    data->bryAngFf = EulerAngles<double>::With(3, 0.0);
    data->vFfF = zeroCol;
    data->omeFfF = zeroCol;
    data->aFfF = zeroCol;
    data->alpFfF = zeroCol;
    return data;
}

void ASMTAssembly::compareResults2(AnalysisType type)
{
    ASMTSpatialContainer::compareResults2(type);
    for (auto part : *parts)
        part->compareResults2(type);
    for (auto joint : *joints)
        joint->compareResults2(type);
    for (auto motion : *motions)
        motion->compareResults2(type);
    for (auto forceTorque : *forcesTorques)
        forceTorque->compareResults2(type);
}

std::string ASMTAssembly::reportComparisonWith(std::shared_ptr<ASMTItem> otherItem)
{
    auto report = ASMTSpatialContainer::reportComparisonWith(otherItem);
    if (!report.empty())
    {
        return report;
    }
    auto other = std::dynamic_pointer_cast<ASMTAssembly>(otherItem);
    if (!other)
    {
        return "Missing comparison assembly.\n";
    }
    report = ASMTItem::itemCollectionComparisonWith("part", parts, other->parts);
    if (!report.empty())
    {
        return report;
    }
    report = ASMTItem::itemCollectionComparisonWith("kinematicIJ", kinematicIJs, other->kinematicIJs);
    if (!report.empty())
    {
        return report;
    }
    report = ASMTItem::itemCollectionComparisonWith("constraintSet", constraintSets, other->constraintSets);
    if (!report.empty())
    {
        return report;
    }
    report = ASMTItem::itemCollectionComparisonWith("joint", joints, other->joints);
    if (!report.empty())
    {
        return report;
    }
    report = ASMTItem::itemCollectionComparisonWith("motion", motions, other->motions);
    if (!report.empty())
    {
        return report;
    }
    report = ASMTItem::itemCollectionComparisonWith("limit", limits, other->limits);
    if (!report.empty())
    {
        return report;
    }
    report = ASMTItem::itemCollectionComparisonWith("forceTorque", forcesTorques, other->forcesTorques);
    if (!report.empty())
    {
        return report;
    }
    report = optionalAssemblyItemComparisonWith("constantGravity", constantGravity, other->constantGravity);
    if (!report.empty())
    {
        return report;
    }
    report = optionalAssemblyItemComparisonWith("simulationParameters", simulationParameters, other->simulationParameters);
    if (!report.empty())
    {
        return report;
    }
    // report = optionalAssemblyItemComparisonWith("animationParameters", animationParameters, other->animationParameters);
    // if (!report.empty()) {
    //     return report;
    // }
    if (!asmtTime && other->asmtTime)
    {
        return "Missing time.\n";
    }
    if (asmtTime && !other->asmtTime)
    {
        return "Missing comparison time.\n";
    }
    if (asmtTime && other->asmtTime)
    {
        if (asmtTime->getName() != other->asmtTime->getName())
        {
            return asmtTime->getName() + " != " + other->asmtTime->getName() + "\n";
        }
        // if (!Numeric::equaltol(asmtTime->getValue(), other->asmtTime->getValue(), 1.0e-9)) {
        //     return asmtTime->getName() + " value differs.\n";
        // }
    }
    return std::string{};
}

void ASMTAssembly::outputResults(AnalysisType type)
{
    // ASMTSpatialContainer::outputResults(type);
    // for (auto part : *parts) part->outputResults(type);
    // for (auto joint : *joints) joint->outputResults(type);
    // for (auto motion : *motions) motion->outputResults(type);
    // for (auto forceTorque : *forcesTorques) forceTorque->outputResults(type);
}

void ASMTAssembly::addTime(std::shared_ptr<ASMTTime> time)
{
    asmtTime = time;
    time->owner = this;
}

void ASMTAssembly::addPart(std::shared_ptr<ASMTPart> part)
{
    parts->push_back(part);
    part->owner = this;
}

void ASMTAssembly::addJoint(std::shared_ptr<ASMTJoint> joint)
{
    joints->push_back(joint);
    joint->owner = this;
}

void ASMTAssembly::addMotion(std::shared_ptr<ASMTMotion> motion)
{
    motions->push_back(motion);
    motion->owner = this;
    motion->initMarkers();
}

void ASMTAssembly::addForceTorque(std::shared_ptr<ASMTForceTorque> forTor)
{
    forcesTorques->push_back(forTor);
    forTor->owner = this;
}

void ASMTAssembly::setConstantGravity(std::shared_ptr<ASMTConstantGravity> gravity)
{
    constantGravity = gravity;
    gravity->owner = this;
}

void ASMTAssembly::setSimulationParameters(std::shared_ptr<ASMTSimulationParameters> parameters)
{
    simulationParameters = parameters;
    parameters->owner = this;
}

void ASMTAssembly::setAnimationParameters(std::shared_ptr<ASMTAnimationParameters> parameters)
{
    animationParameters = parameters;
    parameters->owner = this;
}

std::shared_ptr<ASMTPart> ASMTAssembly::partNamed(std::string partName) const
{
    auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart> &prt)
                           { return prt->fullName("") == partName; });
    auto part = *it;
    return part;
}

std::shared_ptr<ASMTPart> ASMTAssembly::partPartialNamed(std::string partialName) const
{
    auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart> &prt)
                           {
        auto fullName = prt->fullName("");
        return fullName.find(partialName) != std::string::npos; });
    auto part = *it;
    return part;
}

void ASMTAssembly::storeOnLevelNotes(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "Notes");
    storeOnLevelString(os, level + 1, notes);
}

void ASMTAssembly::storeOnLevelParts(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "Parts");
    for (auto part : *parts)
    {
        part->storeOnLevel(os, level + 1);
    }
}

void ASMTAssembly::storeOnLevelKinematicIJs(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "KinematicIJs");
    for (auto KinematicIeJe : *kinematicIJs)
    {
        KinematicIeJe->storeOnLevel(os, level);
    }
}

void ASMTAssembly::storeOnLevelConstraintSets(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "ConstraintSets");
    storeOnLevelJoints(os, level + 1);
    storeOnLevelMotions(os, level + 1);
    storeOnLevelGeneralConstraintSets(os, level + 1);
}

void ASMTAssembly::storeOnLevelForceTorques(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "ForceTorques");
    for (auto forceTorque : *forcesTorques)
    {
        forceTorque->storeOnLevel(os, level + 1);
    }
}

void ASMTAssembly::storeOnLevelJoints(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "Joints");
    for (auto joint : *joints)
    {
        joint->storeOnLevel(os, level + 1);
    }
}

void ASMTAssembly::storeOnLevelMotions(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "Motions");
    for (auto motion : *motions)
    {
        motion->storeOnLevel(os, level + 1);
    }
}

void ASMTAssembly::storeOnLevelGeneralConstraintSets(std::ofstream &os, size_t level)
{
    storeOnLevelString(os, level, "GeneralConstraintSets");
    // for (auto generalConstraintSet : *generalConstraintSets) {
    //     generalConstraintSet->storeOnLevel(os, level);
    // }
}

void ASMTAssembly::storeOnTimeSeries(std::ofstream &os)
{
    if (times->empty())
        return;
    os << "TimeSeries" << std::endl;
    os << "Number\tInput\t";
    auto n = times->size();
    for (size_t i = 1; i < n - 1; i++)
    {
        os << i << '\t';
    }
    os << n - 1;
    os << std::endl;
    os << "Time\tInput\t";
    for (size_t i = 1; i < n - 1; i++)
    {
        os << times->at(i) << '\t';
    }
    os << times->back();
    os << std::endl;
    os << "AssemblySeries\t" << fullName("") << std::endl;
    ASMTSpatialContainer::storeOnTimeSeries(os);
    for (auto part : *parts)
        part->storeOnTimeSeries(os);
    for (auto joint : *joints)
        joint->storeOnTimeSeries(os);
    for (auto motion : *motions)
        motion->storeOnTimeSeries(os);
    for (auto forTor : *forcesTorques)
        forTor->storeOnTimeSeries(os);
}

void ASMTAssembly::setinFileName(const std::string &str)
{
    std::stringstream ss;
    ss << "FileName = " << str;
    auto str2 = ss.str();
    logString(str2);
    inFileName = str;
}

void ASMTAssembly::setoutFileName(const std::string &str)
{
    std::stringstream ss;
    ss << "FileName = " << str;
    auto str2 = ss.str();
    logString(str2);
    outFileName = str;
}

void ASMTAssembly::updateFromInputState()
{
    ASMTSpatialContainer::updateFromInputState();
    for (auto part : *parts)
        part->updateFromInputState();
    for (auto joint : *joints)
        joint->updateFromInputState();
    for (auto motion : *motions)
        motion->updateFromInputState();
}

void MbD::ASMTAssembly::combineInputInitialConditionsWithCalculationResults()
{
    // tempAssembly.asmt has data from calculations
    // Its initial conditions is not exactly the same as inFileName
    // Therefore, the redundant constraints removed can be different between the two files
    // To prevent that, tempAssembly2.asmt has the initial conditions of inFileName and results from tempAssembly.asmt
    std::ifstream in(inFileName);
    if (!in)
        throw std::runtime_error("Cannot open input file");
    std::ifstream in2("tempAssembly.asmt");
    if (!in2)
        throw std::runtime_error("Cannot open input file");
    std::ofstream out("tempAssembly2.asmt");
    if (!out)
        throw std::runtime_error("Cannot open output file");
    std::string data((std::istreambuf_iterator<char>(in)),
                     std::istreambuf_iterator<char>());
    std::string data2((std::istreambuf_iterator<char>(in2)),
                      std::istreambuf_iterator<char>());
    std::size_t pos = data.find("TimeSeries");
    if (pos == std::string::npos)
        pos = data.size();
    std::size_t pos2 = data2.find("TimeSeries");
    out.write(data.data(), static_cast<std::streamsize>(pos));
    out.write(data2.data() + pos2,
              static_cast<std::streamsize>(data2.size() - pos2));
    out.close();
}
