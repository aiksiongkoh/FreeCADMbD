#include "pch.h"
#include <array>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <sstream>
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
#include <Constant.h>
#include <EulerAngles.h>
#include <ExactPendulum.h>
#include <BasicDAEIntegrator.h>

using namespace MbD;

namespace
{
    class CoutRedirect
    {
    public:
        explicit CoutRedirect(std::ostream &target)
            : oldBuffer(std::cout.rdbuf(target.rdbuf()))
        {
        }

        ~CoutRedirect()
        {
            std::cout.rdbuf(oldBuffer);
        }

        CoutRedirect(const CoutRedirect &) = delete;
        CoutRedirect &operator=(const CoutRedirect &) = delete;

    private:
        std::streambuf *oldBuffer;
    };

    struct PendulumRevJtDiffs
    {
        double tol = 0.0;
        double maxRightDiff = 0.0;
        double maxUpDiff = 0.0;
        double maxBryDiff = 0.0;
        double maxOmeDiff = 0.0;
        double maxAlpDiff = 0.0;
    };

    template <typename LengthFunction, typename OmegaNaturalFunction>
    PendulumRevJtDiffs pendulumRevJt_XYRegressionDiffs(const std::string &filename,
                                                       int idigit,
                                                       LengthFunction lengthFunction,
                                                       OmegaNaturalFunction omegaNaturalFunction)
    {
        // The ASMT files model pendulums swinging in the x-y plane about +z.
        // theta is measured counter-clockwise from the downward vertical.
        SCOPED_TRACE(::testing::Message() << filename << ", idigit=" << idigit);
        PendulumRevJtDiffs diffs;
        diffs.tol = std::pow(10.0, -idigit);
        auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/" + filename);
        auto simPara = assembly->simulationParameters;
        simPara->setAllTolForNDigit(idigit);
        auto pendulum = assembly->partNamed("/Assembly1/Part1");

        auto length = lengthFunction(pendulum);
        auto gravity = -assembly->constantGravity->g->at(1);
        auto theta0 = pendulum->rotationMatrix->bryantAngles()->at(2) + std::numbers::pi / 2.0;
        auto omega0 = pendulum->omega3D->at(2);
        auto exactPendulum = ExactPendulum(theta0, omega0, omegaNaturalFunction(gravity, length));
        size_t n = (simPara->tend - simPara->tstart) / simPara->hout;
        n = n + 2; // add count for input and initial time
        assembly->runDYNAMIC();

        EXPECT_EQ(n, assembly->times->size());
        EXPECT_EQ(n, pendulum->xs->size());
        EXPECT_EQ(n, pendulum->ys->size());
        EXPECT_EQ(n, pendulum->bryzs->size());
        EXPECT_EQ(n, pendulum->omezs->size());
        EXPECT_EQ(n, pendulum->alpzs->size());
        if (n != assembly->times->size() || n != pendulum->xs->size() || n != pendulum->ys->size() || n != pendulum->bryzs->size() || n != pendulum->omezs->size() || n != pendulum->alpzs->size())
        {
            diffs.maxRightDiff = std::numeric_limits<double>::max();
            diffs.maxUpDiff = std::numeric_limits<double>::max();
            diffs.maxBryDiff = std::numeric_limits<double>::max();
            diffs.maxOmeDiff = std::numeric_limits<double>::max();
            diffs.maxAlpDiff = std::numeric_limits<double>::max();
            return diffs;
        }

        for (size_t i = 1; i < n; i++)
        {
            auto exactResult = exactPendulum.result(assembly->times->at(i));
            auto bryz = exactResult.theta - std::numbers::pi / 2.0;
            auto x = (length * std::sin(exactResult.theta)) - (length * std::cos(bryz));
            auto y = (-length * std::cos(exactResult.theta)) - (length * std::sin(bryz));
            diffs.maxRightDiff = std::max(diffs.maxRightDiff, std::abs(x - pendulum->xs->at(i)));
            diffs.maxUpDiff = std::max(diffs.maxUpDiff, std::abs(y - pendulum->ys->at(i)));
            diffs.maxBryDiff = std::max(diffs.maxBryDiff, std::abs(bryz - pendulum->bryzs->at(i)));
            auto omez = exactResult.omega;
            diffs.maxOmeDiff = std::max(diffs.maxOmeDiff, std::abs(omez - pendulum->omezs->at(i)));
            auto alpz = exactResult.alpha;
            diffs.maxAlpDiff = std::max(diffs.maxAlpDiff, std::abs(alpz - pendulum->alpzs->at(i)));
        }
        return diffs;
    }

    // Map each plane to XY coordinates, including the signed rotation axis.
    // Bryant-angle conventions need separate offsets and signs.
    void pointPendulumPlaneEquivalence(const std::string& plane,
                                       size_t rightAxis, size_t upAxis,
                                       size_t rotationAxis, size_t bryantAxis,
                                       double rotationSign, double angleSign, double angleOffset)
    {
        for (int idigit = 4; idigit <= 6; ++idigit)
        {
            SCOPED_TRACE(::testing::Message() << plane << ", idigit=" << idigit);
            const auto tol = std::pow(10.0, -idigit);
            auto xy = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/pointPendulumRevJt_XY.asmt");
            auto other = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/pointPendulumRevJt_" + plane + ".asmt");
            xy->simulationParameters->setAllTolForNDigit(idigit);
            other->simulationParameters->setAllTolForNDigit(idigit);
            auto pxy = xy->partNamed("/Assembly1/Part1");
            auto part = other->partNamed("/Assembly1/Part1");
            const auto theta = [=](double bryant)
            {
                return std::remainder(angleSign * bryant + angleOffset, 2.0 * std::numbers::pi);
            };
            const auto theta0 = pxy->rotationMatrix->bryantAngles()->at(2) + std::numbers::pi / 2.0;
            EXPECT_NEAR(theta0, theta(part->rotationMatrix->bryantAngles()->at(bryantAxis)), 1e-14);
            EXPECT_DOUBLE_EQ(pxy->omega3D->at(2), rotationSign * part->omega3D->at(rotationAxis));
            const auto length = pxy->principalMassMarker->position3D->at(0);
            EXPECT_DOUBLE_EQ(length, part->principalMassMarker->position3D->at(0));
            EXPECT_DOUBLE_EQ(xy->constantGravity->g->at(1), other->constantGravity->g->at(upAxis));
            EXPECT_DOUBLE_EQ(xy->simulationParameters->tend, other->simulationParameters->tend);
            EXPECT_DOUBLE_EQ(xy->simulationParameters->tstart, other->simulationParameters->tstart);
            EXPECT_DOUBLE_EQ(xy->simulationParameters->hout, other->simulationParameters->hout);
            ExactPendulum exact(theta0, pxy->omega3D->at(2), std::sqrt(-xy->constantGravity->g->at(1) / length));
            xy->runDYNAMIC();
            other->runDYNAMIC();
            const size_t n = static_cast<size_t>((xy->simulationParameters->tend - xy->simulationParameters->tstart) / xy->simulationParameters->hout) + 2;
            ASSERT_EQ(n, xy->times->size());
            ASSERT_EQ(n, other->times->size());
            const auto positions = std::array{part->xs, part->ys, part->zs};
            const auto angles = std::array{part->bryxs, part->bryys, part->bryzs};
            const auto omegas = std::array{part->omexs, part->omeys, part->omezs};
            const auto alphas = std::array{part->alpxs, part->alpys, part->alpzs};
            const auto bryants = angles.at(bryantAxis);
            const auto omega = omegas.at(rotationAxis);
            const auto alpha = alphas.at(rotationAxis);
            for (const auto& history : {pxy->xs, pxy->ys, pxy->zs, pxy->bryzs, pxy->omezs, pxy->alpzs,
                                       part->xs, part->ys, part->zs, bryants, omega, alpha})
            {
                ASSERT_EQ(n, history->size());
                for (size_t i = 1; i < n; ++i)
                    ASSERT_TRUE(std::isfinite(history->at(i))) << "sample=" << i;
            }
            PendulumRevJtDiffs between, analytic;
            for (size_t i = 1; i < n; ++i) // Exclude the unevaluated input state.
            {
                SCOPED_TRACE(::testing::Message() << "sample=" << i);
                EXPECT_NEAR(xy->times->at(i), other->times->at(i), 1e-14);
                for (const auto& position : positions)
                    EXPECT_NEAR(position->at(i), 0.0, 5.0 * tol);
                between.maxRightDiff = std::max(between.maxRightDiff, std::abs(pxy->xs->at(i) - positions.at(rightAxis)->at(i)));
                between.maxUpDiff = std::max(between.maxUpDiff, std::abs(pxy->ys->at(i) - positions.at(upAxis)->at(i)));
                EXPECT_NEAR(pxy->zs->at(i), rotationSign * positions.at(rotationAxis)->at(i), 10.0 * tol);
                const auto thetaXY = pxy->bryzs->at(i) + std::numbers::pi / 2.0;
                const auto thetaOther = theta(bryants->at(i));
                const auto omegaOther = rotationSign * omega->at(i);
                const auto alphaOther = rotationSign * alpha->at(i);
                between.maxBryDiff = std::max(between.maxBryDiff, std::abs(thetaXY - thetaOther));
                between.maxOmeDiff = std::max(between.maxOmeDiff, std::abs(pxy->omezs->at(i) - omegaOther));
                between.maxAlpDiff = std::max(between.maxAlpDiff, std::abs(pxy->alpzs->at(i) - alphaOther));
                const auto reference = exact.result(other->times->at(i));
                analytic.maxBryDiff = std::max(analytic.maxBryDiff, std::abs(thetaOther - reference.theta));
                analytic.maxOmeDiff = std::max(analytic.maxOmeDiff, std::abs(omegaOther - reference.omega));
                analytic.maxAlpDiff = std::max(analytic.maxAlpDiff, std::abs(alphaOther - reference.alpha));
            }
            const auto report = [&](const std::string& label, const PendulumRevJtDiffs& d)
            {
                std::ostringstream message;
                message << std::setprecision(12) << "Pendulum comparison idigit=" << idigit << " " << label
                        << " theta=" << d.maxBryDiff << " omega=" << d.maxOmeDiff << " alpha=" << d.maxAlpDiff << '\n';
                std::cout << message.str();
            };
            report("XY-" + plane, between);
            report(plane + "-exact", analytic);
            // Preserve standalone analytic bounds; XY has its own regression.
            EXPECT_LE(analytic.maxBryDiff, 5.0 * tol);
            EXPECT_LE(analytic.maxOmeDiff, 50.0 * tol);
            EXPECT_LE(analytic.maxAlpDiff, 500.0 * tol);
            // Independent adaptive runs may use the sum of their error budgets.
            EXPECT_LE(between.maxRightDiff, 10.0 * tol);
            EXPECT_LE(between.maxUpDiff, 10.0 * tol);
            EXPECT_LE(between.maxBryDiff, 10.0 * tol);
            EXPECT_LE(between.maxOmeDiff, 100.0 * tol);
            EXPECT_LE(between.maxAlpDiff, 1000.0 * tol);
        }
    }
}

TEST(FreeCADMbD, TestName)
{
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(FreeCADMbD, symbolicStr)
{
    auto constant = Constant::With(3.25);
    EXPECT_EQ("3.25", constant->str());
}

TEST(FreeCADMbD, simplePendulumXY)
{
    ASMTAssembly::runDynFile(std::string(TEST_DATA_PATH) + "/ASMT/simplePendulumXYa.asmt");
    EXPECT_TRUE(true);
}

TEST(FreeCADMbD, comparePistonKineDynXY)
{
    for (int idigit = 4; idigit <= 8; idigit++)
    {
        auto pistonKineXY = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/pistonKineXY.asmt");
        auto pistonDynXY = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/pistonDynXY.asmt");
        auto report = pistonKineXY->reportComparisonWith(pistonDynXY);
        EXPECT_TRUE(report.empty());

        pistonKineXY->simulationParameters->setAllTolForNDigit(idigit);
        pistonKineXY->runKINEMATIC();
        auto conrodKine = pistonKineXY->partNamed("/Assembly1/Part2");

        pistonDynXY->simulationParameters->setAllTolForNDigit(idigit);
        pistonDynXY->runDYNAMIC();
        auto conrodDyn = pistonDynXY->partNamed("/Assembly1/Part2");

        double tol = std::pow(10.0, -idigit);
        auto compareRows = [](const std::string &label, FRowDsptr row, FRowDsptr otherRow, double tol)
        {
            SCOPED_TRACE(label);
            ASSERT_NE(row, nullptr);
            ASSERT_NE(otherRow, nullptr);
            ASSERT_EQ(row->size(), otherRow->size());
            auto diffRow = row->minusFullRow(otherRow);
            auto maxDiff = diffRow->maxMagnitude();
            if (maxDiff > tol)
            {
                __debugbreak();
            }
            EXPECT_LE(maxDiff, tol);
        };

        switch (idigit)
        {
        case 4:
            compareRows("xs", conrodKine->xs, conrodDyn->xs, 1 * tol);
            compareRows("ys", conrodKine->ys, conrodDyn->ys, 1 * tol);
            compareRows("zs", conrodKine->zs, conrodDyn->zs, 1 * tol);
            compareRows("bryxs", conrodKine->bryxs, conrodDyn->bryxs, 1 * tol);
            compareRows("bryys", conrodKine->bryys, conrodDyn->bryys, 1 * tol);
            compareRows("bryzs", conrodKine->bryzs, conrodDyn->bryzs, 1 * tol);
            compareRows("vxs", conrodKine->vxs, conrodDyn->vxs, 10 * tol);
            compareRows("vys", conrodKine->vys, conrodDyn->vys, 10 * tol);
            compareRows("vzs", conrodKine->vzs, conrodDyn->vzs, 10 * tol);
            compareRows("omexs", conrodKine->omexs, conrodDyn->omexs, 10 * tol);
            compareRows("omeys", conrodKine->omeys, conrodDyn->omeys, 10 * tol);
            compareRows("omezs", conrodKine->omezs, conrodDyn->omezs, 10 * tol);
            compareRows("axs", conrodKine->axs, conrodDyn->axs, 100 * tol);
            compareRows("ays", conrodKine->ays, conrodDyn->ays, 100 * tol);
            compareRows("azs", conrodKine->azs, conrodDyn->azs, 100 * tol);
            compareRows("alpxs", conrodKine->alpxs, conrodDyn->alpxs, 100 * tol);
            compareRows("alpys", conrodKine->alpys, conrodDyn->alpys, 100 * tol);
            compareRows("alpzs", conrodKine->alpzs, conrodDyn->alpzs, 100 * tol);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            EXPECT_EQ(27, conrodKine->xs->size());
            EXPECT_EQ(2, conrodDyn->xs->size()); // error tolerance is too demanding.
            break;
        default:
            break;
        }
    }
}

TEST(FreeCADMbD, comparePointPendulumRevJt_XY)
{
    auto assemblyXY = ASMTAssembly::pointPendulumRevJt_XY();
    assemblyXY->runDYNAMIC();
    auto assemblyXYfile = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/pointPendulumRevJt_XY.asmt");
    assemblyXYfile->runDYNAMIC();
    std::string report;
    report = assemblyXY->reportComparisonWith(assemblyXYfile);
    EXPECT_TRUE(report.empty());
    auto pendulumXY = assemblyXY->partNamed("/Assembly1/Part1");
    auto pendulumXYfile = assemblyXYfile->partNamed("/Assembly1/Part1");

    auto compareRows = [](const std::string &label, FRowDsptr row, FRowDsptr otherRow)
    {
        SCOPED_TRACE(label);
        ASSERT_NE(row, nullptr);
        ASSERT_NE(otherRow, nullptr);
        ASSERT_EQ(row->size(), otherRow->size());
        auto diffRow = row->minusFullRow(otherRow);
        EXPECT_LE(diffRow->maxMagnitude(), 1.0e-12);
    };
    compareRows("xs", pendulumXY->xs, pendulumXYfile->xs);
    compareRows("ys", pendulumXY->ys, pendulumXYfile->ys);
    compareRows("zs", pendulumXY->zs, pendulumXYfile->zs);
    compareRows("bryxs", pendulumXY->bryxs, pendulumXYfile->bryxs);
    compareRows("bryys", pendulumXY->bryys, pendulumXYfile->bryys);
    compareRows("bryzs", pendulumXY->bryzs, pendulumXYfile->bryzs);
    compareRows("vxs", pendulumXY->vxs, pendulumXYfile->vxs);
    compareRows("vys", pendulumXY->vys, pendulumXYfile->vys);
    compareRows("vzs", pendulumXY->vzs, pendulumXYfile->vzs);
    compareRows("omexs", pendulumXY->omexs, pendulumXYfile->omexs);
    compareRows("omeys", pendulumXY->omeys, pendulumXYfile->omeys);
    compareRows("omezs", pendulumXY->omezs, pendulumXYfile->omezs);
    compareRows("axs", pendulumXY->axs, pendulumXYfile->axs);
    compareRows("ays", pendulumXY->ays, pendulumXYfile->ays);
    compareRows("azs", pendulumXY->azs, pendulumXYfile->azs);
    compareRows("alpxs", pendulumXY->alpxs, pendulumXYfile->alpxs);
    compareRows("alpys", pendulumXY->alpys, pendulumXYfile->alpys);
    compareRows("alpzs", pendulumXY->alpzs, pendulumXYfile->alpzs);
}

TEST(FreeCADMbD, comparePointPendulumRevJt_XY_XZ)
{
    // Compare equivalent orientations with errorTol = 1.0e-12.
    auto idigit = 6;
    auto tol = std::pow(10.0, -idigit);
    auto lambda = [&](std::shared_ptr<ASMTSimulationParameters> simPara)
    {
        simPara->errorTol = tol * tol;
        simPara->errorTolPosKine = tol * tol;
        simPara->errorTolAccKine = tol * tol;
        simPara->corAbsTol = tol * tol;
        simPara->corRelTol = tol * tol;
        simPara->intAbsTol = tol * tol;
        simPara->intRelTol = tol * tol;
        simPara->hmin = tol * tol;
    };
    std::ofstream file("pointPendulumRevJt_XY.txt");
    CoutRedirect redirect(file);
    auto assemblyXY = ASMTAssembly::pointPendulumRevJt_XY();
    lambda(assemblyXY->simulationParameters);
    assemblyXY->runDYNAMIC();

    std::ofstream file2("pointPendulumRevJt_XZ.txt");
    CoutRedirect redirect2(file2);
    auto assemblyXZ = ASMTAssembly::pointPendulumRevJt_XZ();
    lambda(assemblyXZ->simulationParameters);
    assemblyXZ->runDYNAMIC();

    std::ofstream file3("pointPendulumRevJt_XZfile.txt");
    CoutRedirect redirect3(file3);
    auto assemblyXZfile = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/" + "pointPendulumRevJt_XZ.asmt");
    lambda(assemblyXZfile->simulationParameters);
    assemblyXZfile->runDYNAMIC();
}

TEST(FreeCADMbD, pointPendulumRevJt_XY)
{
    auto assemblyXY = ASMTAssembly::pointPendulumRevJt_XY();
    assemblyXY->runDYNAMIC();
    auto pendulumXY = assemblyXY->partNamed("/Assembly1/Part1");
    auto length = pendulumXY->principalMassMarker->position3D->at(0);
    auto gravity = -assemblyXY->constantGravity->g->at(1);
    auto theta0 = pendulumXY->bryzs->at(1) + std::numbers::pi / 2.0;
    auto omega0 = pendulumXY->omezs->at(1);
    auto omega_n = std::sqrt(gravity / length);
    auto exactPendulum = ExactPendulum(theta0, omega0, omega_n);
    auto simParaXY = assemblyXY->simulationParameters;
    size_t n = (simParaXY->tend - simParaXY->tstart) / simParaXY->hout;
    n = n + 2; // add count for input and initial time
    auto tol = std::sqrt(simParaXY->errorTol);
    auto theDiffs = FullRow<double>::With();
    auto omeDiffs = FullRow<double>::With();
    auto alpDiffs = FullRow<double>::With();
    double time, bryz, theXY, omeXY, alpXY;
    for (size_t i = 1; i < n; i++)
    {
        time = assemblyXY->times->at(i);
        auto exactResult = exactPendulum.result(time);
        bryz = pendulumXY->bryzs->at(i); // -pi < bryz <= pi
        if (bryz <= 0.0)
        {
            theXY = bryz + (std::numbers::pi / 2.0);
        }
        else
        {
            theXY = bryz - (3.0 * std::numbers::pi / 2.0);
        }
        theDiffs->push_back(theXY - exactResult.theta);
        omeXY = pendulumXY->omezs->at(i);
        omeDiffs->push_back(omeXY - exactResult.omega);
        alpXY = pendulumXY->alpzs->at(i);
        alpDiffs->push_back(alpXY - exactResult.alpha);
    }
    auto maxTheDiff = theDiffs->maxMagnitude();
    auto maxOmeDiff = omeDiffs->maxMagnitude();
    auto maxAlpDiff = alpDiffs->maxMagnitude();
    EXPECT_LE(maxTheDiff, 5.0 * tol);
    EXPECT_LE(maxOmeDiff, 50.0 * tol);
    EXPECT_LE(maxAlpDiff, 500.0 * tol);
}

TEST(FreeCADMbD, pointPendulumRevJt_YZ)
{
    auto assemblyYZ = ASMTAssembly::pointPendulumRevJt_YZ();
    assemblyYZ->runDYNAMIC();
    auto pendulumYZ = assemblyYZ->partNamed("/Assembly1/Part1");
    auto length = pendulumYZ->principalMassMarker->position3D->at(0);
    auto gravity = -assemblyYZ->constantGravity->g->at(2);
    auto theta0 = pendulumYZ->bryxs->at(1);
    auto omega0 = pendulumYZ->omexs->at(1);
    auto omega_n = std::sqrt(gravity / length);
    auto exactPendulum = ExactPendulum(theta0, omega0, omega_n);
    auto simParaYZ = assemblyYZ->simulationParameters;
    size_t n = (simParaYZ->tend - simParaYZ->tstart) / simParaYZ->hout;
    n = n + 2; // add count for input and initial time
    auto tol = std::sqrt(simParaYZ->errorTol);
    auto theDiffs = FullRow<double>::With();
    auto omeDiffs = FullRow<double>::With();
    auto alpDiffs = FullRow<double>::With();
    double time, bryx, theYZ, omeYZ, alpYZ;
    for (size_t i = 1; i < n; i++)
    {
        time = assemblyYZ->times->at(i);
        auto exactResult = exactPendulum.result(time);
        bryx = pendulumYZ->bryxs->at(i); // -pi < bryx <= pi
        if (bryx <= 0.0)
        {
            theYZ = bryx;
        }
        else
        {
            theYZ = bryx;
        }
        theDiffs->push_back(theYZ - exactResult.theta);
        omeYZ = pendulumYZ->omexs->at(i);
        omeDiffs->push_back(omeYZ - exactResult.omega);
        alpYZ = pendulumYZ->alpxs->at(i);
        alpDiffs->push_back(alpYZ - exactResult.alpha);
    }
    auto maxTheDiff = theDiffs->maxMagnitude();
    auto maxOmeDiff = omeDiffs->maxMagnitude();
    auto maxAlpDiff = alpDiffs->maxMagnitude();
    EXPECT_LE(maxTheDiff, 5.0 * tol);
    EXPECT_LE(maxOmeDiff, 50.0 * tol);
    EXPECT_LE(maxAlpDiff, 500.0 * tol);
}

TEST(FreeCADMbD, pointPendulumRevJt_ZX)
{
    auto assemblyZX = ASMTAssembly::pointPendulumRevJt_ZX();
    assemblyZX->runDYNAMIC();
    auto pendulumZX = assemblyZX->partNamed("/Assembly1/Part1");
    auto length = pendulumZX->principalMassMarker->position3D->at(0);
    auto gravity = -assemblyZX->constantGravity->g->at(0);
    auto theta0 = pendulumZX->bryzs->at(1) + std::numbers::pi;
    auto omega0 = pendulumZX->omeys->at(1);
    auto omega_n = std::sqrt(gravity / length);
    auto exactPendulum = ExactPendulum(theta0, omega0, omega_n);
    auto simParaZX = assemblyZX->simulationParameters;
    size_t n = (simParaZX->tend - simParaZX->tstart) / simParaZX->hout;
    n = n + 2; // add count for input and initial time
    auto tol = std::sqrt(simParaZX->errorTol);
    auto theDiffs = FullRow<double>::With();
    auto omeDiffs = FullRow<double>::With();
    auto alpDiffs = FullRow<double>::With();
    double time, bryz, theZX, omeZX, alpZX;
    for (size_t i = 1; i < n; i++)
    {
        time = assemblyZX->times->at(i);
        auto exactResult = exactPendulum.result(time);
        bryz = pendulumZX->bryzs->at(i); // -pi < bryz <= pi
        if (bryz <= 0.0)
        {
            theZX = bryz + std::numbers::pi;
        }
        else
        {
            theZX = bryz - std::numbers::pi;
        }
        theDiffs->push_back(theZX - exactResult.theta);
        omeZX = pendulumZX->omeys->at(i);
        omeDiffs->push_back(omeZX - exactResult.omega);
        alpZX = pendulumZX->alpys->at(i);
        alpDiffs->push_back(alpZX - exactResult.alpha);
    }
    auto maxTheDiff = theDiffs->maxMagnitude();
    auto maxOmeDiff = omeDiffs->maxMagnitude();
    auto maxAlpDiff = alpDiffs->maxMagnitude();
    EXPECT_LE(maxTheDiff, 5.0 * tol);
    EXPECT_LE(maxOmeDiff, 50.0 * tol);
    EXPECT_LE(maxAlpDiff, 500.0 * tol);
}

TEST(FreeCADMbD, bryantAnglesReconstructRotation)
{
    const double halfPi = std::numbers::pi / 2.0;
    for (double x : {-2.4, 0.0, 0.7}) {
        for (double y : {-2.0, -halfPi, -halfPi + 5e-13, -halfPi + 1e-8,
                         0.0, halfPi - 1e-8, halfPi - 5e-13, halfPi, 2.0}) {
            for (double z : {-0.8, 0.0, 1.3}) {
                SCOPED_TRACE(::testing::Message() << x << ", " << y << ", " << z);
                auto matrix = FullMatrix<double>::rotatex(x)->timesFullMatrix(
                    FullMatrix<double>::rotatey(y)->timesFullMatrix(FullMatrix<double>::rotatez(z)));
                auto angles = matrix->bryantAngles();
                angles->calc();
                for (size_t row = 0; row < 3; ++row)
                    for (size_t col = 0; col < 3; ++col)
                        EXPECT_NEAR(matrix->at(row)->at(col), angles->aA->at(row)->at(col), 2e-12);
                if (std::abs(std::cos(y)) <= 1e-12)
                    EXPECT_EQ(0.0, angles->at(2));
            }
        }
    }
}

TEST(FreeCADMbD, bryantAnglesYZSingularityWithMatrixDrift)
{
    // Matrix captured from the YZ pendulum at t=0.86. R02 drift must
    // not cause atan2(-R12, R22) to interpret roundoff as a rotation.
    auto matrix = FullMatrix<double>::With(ListListD{
        {-2.0816681711721685e-17, 0.0, 0.99999998492675446},
        {0.58869519393157632, 0.80835508193823646, 0.0},
        {-0.80835508193823657, 0.58869519393157632, -2.0816681711721685e-17}});
    auto angles = matrix->bryantAngles();
    EXPECT_NEAR(std::atan2(matrix->at(1)->at(0), -matrix->at(2)->at(0)), angles->at(0), 1e-12);
    EXPECT_DOUBLE_EQ(std::numbers::pi / 2.0, angles->at(1));
    EXPECT_EQ(0.0, angles->at(2));
    angles->calc();
    for (size_t row = 0; row < 3; ++row)
        for (size_t col = 0; col < 3; ++col)
            EXPECT_NEAR(matrix->at(row)->at(col), angles->aA->at(row)->at(col), 3e-8);
}

TEST(FreeCADMbD, simplePendulumExactMotion)
{
    constexpr auto length = 1.0;
    constexpr auto gravity = 9.81;
    constexpr auto theta0 = std::numbers::pi / 2.0;
    const auto omegaNatural = std::sqrt(gravity / length);
    const auto modulus = std::sin(theta0 / 2.0);
    const auto period = 4.0 * std::comp_ellint_1(modulus) / omegaNatural;

    auto exactPendulum = ExactPendulum(theta0, 0.0, omegaNatural);

    auto exactResult = exactPendulum.result(0.0);
    EXPECT_NEAR(theta0, exactResult.theta, 1.0e-12);
    EXPECT_NEAR(1.0, length * std::sin(exactResult.theta), 1.0e-12);
    EXPECT_NEAR(0.0, -length * std::cos(exactResult.theta), 1.0e-12);
    EXPECT_NEAR(0.0, exactResult.time, 1.0e-12);
    EXPECT_NEAR(theta0, exactResult.theta0, 1.0e-12);
    EXPECT_NEAR(0.0, exactResult.omega0, 1.0e-12);
    EXPECT_NEAR(omegaNatural, exactResult.omega_n, 1.0e-12);
    EXPECT_NEAR(0.0, exactResult.omega, 1.0e-12);
    EXPECT_NEAR(-omegaNatural * omegaNatural * std::sin(theta0), exactResult.alpha, 1.0e-12);

    exactResult = exactPendulum.result(period / 4.0);
    EXPECT_NEAR(period / 4.0, exactResult.time, 1.0e-12);
    EXPECT_NEAR(0.0, exactResult.theta, 1.0e-12);
    EXPECT_NEAR(-2.0 * omegaNatural * modulus, exactResult.omega, 1.0e-12);
    EXPECT_NEAR(0.0, exactResult.alpha, 1.0e-12);
    EXPECT_NEAR(0.0, length * std::sin(exactResult.theta), 1.0e-12);
    EXPECT_NEAR(-1.0, -length * std::cos(exactResult.theta), 1.0e-12);

    exactResult = exactPendulum.result(period);
    EXPECT_NEAR(theta0, exactResult.theta, 1.0e-12);
    EXPECT_NEAR(1.0, length * std::sin(exactResult.theta), 1.0e-12);
    EXPECT_NEAR(0.0, -length * std::cos(exactResult.theta), 1.0e-12);
}

TEST(FreeCADMbD, exactPendulumClass)
{
    constexpr auto theta0 = std::numbers::pi / 2.0;
    constexpr auto omega0 = 0.0;
    constexpr auto omega_n = 1.0;

    auto exactPendulum = ExactPendulum(theta0, omega0, omega_n);

    auto exactResult = exactPendulum.result(0.0);
    EXPECT_EQ(ExactPendulum::Mode::Oscillation, exactResult.mode);
    EXPECT_NEAR(0.0, exactResult.time, 1.0e-12);
    EXPECT_NEAR(theta0, exactResult.theta0, 1.0e-12);
    EXPECT_NEAR(omega0, exactResult.omega0, 1.0e-12);
    EXPECT_NEAR(omega_n, exactResult.omega_n, 1.0e-12);
    EXPECT_NEAR(theta0, exactResult.theta, 1.0e-12);
    EXPECT_NEAR(omega0, exactResult.omega, 1.0e-12);
    EXPECT_NEAR(-omega_n * omega_n * std::sin(theta0), exactResult.alpha, 1.0e-12);
}

TEST(FreeCADMbD, exactPendulumInitialAngularVelocity)
{
    constexpr auto theta0 = std::numbers::pi / 6.0;
    constexpr auto omega0 = -0.25;
    constexpr auto omega_n = 1.0;

    auto exactPendulum = ExactPendulum(theta0, omega0, omega_n);

    auto exactResult = exactPendulum.result(0.0);
    EXPECT_EQ(ExactPendulum::Mode::Oscillation, exactResult.mode);
    EXPECT_NEAR(0.0, exactResult.time, 1.0e-12);
    EXPECT_NEAR(theta0, exactResult.theta0, 1.0e-12);
    EXPECT_NEAR(omega0, exactResult.omega0, 1.0e-12);
    EXPECT_NEAR(omega_n, exactResult.omega_n, 1.0e-12);
    EXPECT_NEAR(theta0, exactResult.theta, 1.0e-12);
    EXPECT_NEAR(omega0, exactResult.omega, 1.0e-12);
    EXPECT_NEAR(-omega_n * omega_n * std::sin(theta0), exactResult.alpha, 1.0e-12);
}

TEST(FreeCADMbD, exactPendulumJacobiReference)
{
    // Independent 10-decimal reference: https://dlmf.nist.gov/22.20#ii
    constexpr double k = 0.65, u = 0.8;
    constexpr double sn = 0.6950642165, cn = 0.7189476580, dn = 0.8921234349;
    const auto oscillation = ExactPendulum(0.0, 2.0 * k, 1.0).result(u);
    EXPECT_NEAR(2.0 * std::asin(k * sn), oscillation.theta, 2e-10);
    EXPECT_NEAR(2.0 * k * cn, oscillation.omega, 2e-10);
    const auto rotation = ExactPendulum(0.0, 2.0 / k, 1.0).result(k * u);
    EXPECT_EQ(ExactPendulum::Mode::Rotation, rotation.mode);
    EXPECT_NEAR(2.0 * std::atan2(sn, cn), rotation.theta, 2e-10);
    EXPECT_NEAR(2.0 * dn / k, rotation.omega, 2e-10);
}

TEST(FreeCADMbD, exactPendulumAgainstNumericalIntegration)
{
    // RK4 integrates the physical ODE independently of elliptic functions.
    // Cover both directions, negative times, rotation, and both sides of h=1.
    const double initialStates[][2] = {
        {0.7, 0.4}, {0.7, -0.4}, {0.3, 3.0}, {0.3, -3.0},
        {0.0, 2.0 * std::sqrt(1.0 - 1e-8)},
        {0.0, 2.0 * std::sqrt(1.0 + 1e-8)}, {0.0, 2.0}
    };
    for (const auto &initial : initialStates) {
        for (double endTime : {-2.0, 2.0}) {
            SCOPED_TRACE(::testing::Message() << initial[0] << ", " << initial[1] << ", t=" << endTime);
            double theta = initial[0], omega = initial[1];
            const double dt = endTime / 2000.0;
            for (int i = 0; i < 2000; ++i) {
                const double t1 = omega, w1 = -std::sin(theta);
                const double t2 = omega + dt * w1 / 2.0, w2 = -std::sin(theta + dt * t1 / 2.0);
                const double t3 = omega + dt * w2 / 2.0, w3 = -std::sin(theta + dt * t2 / 2.0);
                const double t4 = omega + dt * w3, w4 = -std::sin(theta + dt * t3);
                theta += dt * (t1 + 2.0 * t2 + 2.0 * t3 + t4) / 6.0;
                omega += dt * (w1 + 2.0 * w2 + 2.0 * w3 + w4) / 6.0;
            }
            const ExactPendulum pendulum(initial[0], initial[1], 1.0);
            const auto result = pendulum.result(endTime);
            EXPECT_NEAR(0.0, std::remainder(result.theta - theta, 2.0 * std::numbers::pi), 1e-9);
            EXPECT_NEAR(omega, result.omega, 1e-9);
            const double energy = std::pow(std::sin(result.theta / 2.0), 2) + std::pow(result.omega / 2.0, 2);
            EXPECT_NEAR(pendulum.energy(), energy, 1e-12);
        }
    }
}

TEST(FreeCADMbD, exactPendulumMultiplePeriods)
{
    for (double k : {1e-5, 0.65, 0.999999}) {
        const ExactPendulum pendulum(0.0, 2.0 * k, 1.0);
        const double period = 4.0 * std::comp_ellint_1(k);
        for (double cycles : {-100.0, -1.0, 0.0, 1.0, 100.0}) {
            const auto result = pendulum.result(cycles * period);
            EXPECT_NEAR(0.0, result.theta, 1e-10);
            EXPECT_NEAR(2.0 * k, result.omega, 1e-12);
            const auto turningPoint = pendulum.result((cycles + 0.25) * period);
            EXPECT_NEAR(2.0 * std::asin(k), turningPoint.theta, 1e-10);
            EXPECT_NEAR(0.0, turningPoint.omega, 1e-10);
        }
    }
}

TEST(FreeCADMbD, daeCorrectorRoundoffConvergence)
{
    // A stiff BDF row amplifies position roundoff into momentum corrections.
    // Supply its Jacobian directly so each convergence guard is exercised.
    class FixedJacobianCorrector : public DAECorrector {
    public:
        void fillPyPx() override {}
    } corrector;
    auto integrator = BasicDAEIntegrator::With();
    integrator->corAbsTol = FullColumn<double>::With(2, 1e-12);
    corrector.setSystem(integrator.get());
    corrector.x = FullColumn<double>::With(2, 1.0);
    corrector.y = FullColumn<double>::With(2, 0.0);
    corrector.pypx = std::make_shared<SparseMatrix<double>>(2, 2);
    corrector.pypx->atijput(0, 0, 1.0);
    corrector.pypx->atijput(0, 1, -1e6);
    corrector.pypx->atijput(1, 1, 1.0);
    corrector.dxNorms = std::make_shared<std::vector<double>>(2, 10.0);
    corrector.dxNorm = 10.0;
    corrector.iterNo = 1;
    corrector.y->at(0) = 1e-10;
    corrector.y->at(1) = 1e-16;
    EXPECT_TRUE(corrector.isConverged());

    // A small residual in one equation cannot hide another unsatisfied row.
    corrector.y->at(1) = 1e-10;
    EXPECT_FALSE(corrector.isConverged());
    corrector.y->at(1) = 1e-16;
    corrector.y->at(0) = 1e-7;
    EXPECT_FALSE(corrector.isConverged());
    corrector.y->at(0) = 1e-10;

    corrector.iterNo = 0;
    EXPECT_FALSE(corrector.isConverged());
    corrector.iterNo = 1;
    corrector.dxNorms->at(0) = 100.0; // Still converging: keep iterating.
    EXPECT_FALSE(corrector.isConverged());
    corrector.dxNorms->at(0) = 10.0;
    corrector.y->at(0) = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(corrector.isConverged());
    corrector.y->at(0) = 1e-10;
    corrector.pypx->atijput(0, 1, std::numeric_limits<double>::infinity());
    EXPECT_FALSE(corrector.isConverged());
}

TEST(FreeCADMbD, pointPendulumRevJtXYRegression)
{
    for (int idigit = 4; idigit <= 6; idigit++)
    {
        auto diffs = pendulumRevJt_XYRegressionDiffs(
            "pointPendulumRevJt_XY.asmt",
            idigit,
            [](const auto &pendulum)
            { return pendulum->principalMassMarker->position3D->at(0); },
            [](double gravity, double length)
            { return std::sqrt(gravity / length); });
        EXPECT_LE(diffs.maxRightDiff, 5.0 * diffs.tol);
        EXPECT_LE(diffs.maxUpDiff, 5.0 * diffs.tol);
        EXPECT_LE(diffs.maxBryDiff, 5.0 * diffs.tol);
        EXPECT_LE(diffs.maxOmeDiff, 50.0 * diffs.tol);
        EXPECT_LE(diffs.maxAlpDiff, 500.0 * diffs.tol);
    }
}

TEST(FreeCADMbD, pointPendulumRevJtXYYZEquivalence)
{
    // XY x->y, y->z, z->x; theta = bryx.
    pointPendulumPlaneEquivalence("YZ", 1, 2, 0, 0, 1.0, 1.0, 0.0);
}

TEST(FreeCADMbD, pointPendulumRevJtXYZXEquivalence)
{
    // XY x->z, y->x, z->y; theta = wrapped(bryz + pi).
    pointPendulumPlaneEquivalence("ZX", 2, 0, 1, 2, 1.0, 1.0, std::numbers::pi);
}

TEST(FreeCADMbD, pointPendulumRevJtXYZYEquivalence)
{
    // XY x->z, y->y, z->-x; theta = pi/2 - bryx.
    pointPendulumPlaneEquivalence("ZY", 2, 1, 0, 0, -1.0, -1.0, std::numbers::pi / 2.0);
}

TEST(FreeCADMbD, pointPendulumRevJtXYYXEquivalence)
{
    // XY x->y, y->x, z->-z; theta = wrapped(bryz + pi).
    pointPendulumPlaneEquivalence("YX", 1, 0, 2, 2, -1.0, 1.0, std::numbers::pi);
}

TEST(FreeCADMbD, pointPendulumRevJtXYXZEquivalence)
{
    // XY x->x, y->z, z->-y; theta = bryz + pi/2.
    pointPendulumPlaneEquivalence("XZ", 0, 2, 1, 2, -1.0, 1.0, std::numbers::pi / 2.0);
}

TEST(FreeCADMbD, line2PendulumRevJtXYRegression)
{
    for (int idigit = 4; idigit <= 6; idigit++)
    {
        auto diffs = pendulumRevJt_XYRegressionDiffs(
            "linePendulumRevJt_XY.asmt",
            idigit,
            [](const auto &pendulum)
            { return 2.0 * pendulum->principalMassMarker->position3D->at(0); },
            [](double gravity, double length)
            { return std::sqrt(3.0 * gravity / (2.0 * length)); });
        EXPECT_LE(diffs.maxRightDiff, 5.0 * diffs.tol);
        EXPECT_LE(diffs.maxUpDiff, 5.0 * diffs.tol);
        EXPECT_LE(diffs.maxBryDiff, 5.0 * diffs.tol);
        EXPECT_LE(diffs.maxOmeDiff, 20.0 * diffs.tol);
        EXPECT_LE(diffs.maxAlpDiff, 300.0 * diffs.tol);
    }
}

TEST(FreeCADMbD, blockPendulumRevJtXYRegression)
{
    constexpr auto width = 0.02;
    for (int idigit = 4; idigit <= 6; idigit++)
    {
        auto diffs = pendulumRevJt_XYRegressionDiffs(
            "blockPendulumRevJt_XY.asmt",
            idigit,
            [](const auto &pendulum)
            { return 2.0 * pendulum->principalMassMarker->position3D->at(0); },
            [width](double gravity, double length)
            {
                return std::sqrt((6.0 * gravity * length) / ((4.0 * length * length) + (width * width)));
            });
        EXPECT_LE(diffs.maxRightDiff, 5.0 * diffs.tol);
        EXPECT_LE(diffs.maxUpDiff, 5.0 * diffs.tol);
        EXPECT_LE(diffs.maxBryDiff, 5.0 * diffs.tol);
        EXPECT_LE(diffs.maxOmeDiff, 20.0 * diffs.tol);
        EXPECT_LE(diffs.maxAlpDiff, 200.0 * diffs.tol);
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
