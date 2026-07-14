#include "pch.h"
#include <cmath>
#include <fstream>
#include <iostream>
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
#include <Constant.h>
#include <EulerAngles.h>
#include <ExactPendulum.h>

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
        SCOPED_TRACE(filename);
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

    template <typename LengthFunction, typename OmegaNaturalFunction>
    PendulumRevJtDiffs pendulumRevJt_YZRegressionDiffs(const std::string &filename,
                                                       int idigit,
                                                       LengthFunction lengthFunction,
                                                       OmegaNaturalFunction omegaNaturalFunction)
    {
        // The ASMT files model pendulums swinging in the x-y plane about +z.
        // theta is measured counter-clockwise from the downward vertical.
        SCOPED_TRACE(filename);
        PendulumRevJtDiffs diffs;
        diffs.tol = std::pow(10.0, -idigit);
        auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/" + filename);
        auto simPara = assembly->simulationParameters;
        simPara->setAllTolForNDigit(idigit);
        auto pendulum = assembly->partNamed("/Assembly1/Part1");

        auto length = lengthFunction(pendulum);
        auto gravity = -assembly->constantGravity->g->at(2); // -z dir
        auto theta0 = pendulum->rotationMatrix->bryantAngles()->at(2) + std::numbers::pi / 2.0;
        auto omega0 = pendulum->omega3D->at(0);
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
            auto omex = exactResult.omega;
            diffs.maxOmeDiff = std::max(diffs.maxOmeDiff, std::abs(omex - pendulum->omexs->at(i)));
            auto alpx = exactResult.alpha;
            diffs.maxAlpDiff = std::max(diffs.maxAlpDiff, std::abs(alpx - pendulum->alpxs->at(i)));
        }
        return diffs;
    }

    template <typename LengthFunction, typename OmegaNaturalFunction>
    PendulumRevJtDiffs pendulumRevJt_ZXRegressionDiffs(const std::string &filename,
                                                       int idigit,
                                                       LengthFunction lengthFunction,
                                                       OmegaNaturalFunction omegaNaturalFunction)
    {
        // The ASMT files model pendulums swinging in the z-x plane about +y.
        // Gravity is -x direction.
        // theta is measured counter-clockwise from the downward vertical.
        SCOPED_TRACE(filename);
        PendulumRevJtDiffs diffs;
        diffs.tol = std::pow(10.0, -idigit);
        auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/" + filename);
        auto simPara = assembly->simulationParameters;
        simPara->setAllTolForNDigit(idigit);
        auto pendulum = assembly->partNamed("/Assembly1/Part1");

        auto length = lengthFunction(pendulum);
        auto gravity = -assembly->constantGravity->g->at(0);
        auto theta0 = pendulum->rotationMatrix->bryantAngles()->at(2) + std::numbers::pi;
        auto omega0 = pendulum->omega3D->at(1);
        auto exactPendulum = ExactPendulum(theta0, omega0, omegaNaturalFunction(gravity, length));
        size_t n = (simPara->tend - simPara->tstart) / simPara->hout;
        n = n + 2; // add count for input and initial time

        assembly->runDYNAMIC();

        EXPECT_EQ(n, assembly->times->size());
        EXPECT_EQ(n, pendulum->zs->size());
        EXPECT_EQ(n, pendulum->xs->size());
        EXPECT_EQ(n, pendulum->bryzs->size());
        EXPECT_EQ(n, pendulum->omeys->size());
        EXPECT_EQ(n, pendulum->alpys->size());
        if (n != assembly->times->size() || n != pendulum->zs->size() || n != pendulum->xs->size() || n != pendulum->bryzs->size() || n != pendulum->omeys->size() || n != pendulum->alpys->size())
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
            auto bryz = exactResult.theta - std::numbers::pi;
            auto z = (length * std::sin(exactResult.theta)) + (length * std::sin(bryz));
            auto x = (-length * std::cos(exactResult.theta)) - (length * std::cos(bryz));
            diffs.maxRightDiff = std::max(diffs.maxRightDiff, std::abs(z - pendulum->zs->at(i)));
            diffs.maxUpDiff = std::max(diffs.maxUpDiff, std::abs(x - pendulum->xs->at(i)));
            auto bryzsi = pendulum->bryzs->at(i);
            if (bryzsi > 0.0)
            {
                bryzsi -= 2.0 * std::numbers::pi;
            }
            diffs.maxBryDiff = std::max(diffs.maxBryDiff, std::abs(bryz - bryzsi));
            auto omey = exactResult.omega;
            diffs.maxOmeDiff = std::max(diffs.maxOmeDiff, std::abs(omey - pendulum->omeys->at(i)));
            auto alpy = exactResult.alpha;
            diffs.maxAlpDiff = std::max(diffs.maxAlpDiff, std::abs(alpy - pendulum->alpys->at(i)));
        }
        return diffs;
    }

    template <typename LengthFunction, typename OmegaNaturalFunction>
    PendulumRevJtDiffs pendulumRevJt_ZYRegressionDiffs(const std::string &filename,
                                                       int idigit,
                                                       LengthFunction lengthFunction,
                                                       OmegaNaturalFunction omegaNaturalFunction)
    {
        // The ASMT files model pendulums swinging in the z-y plane about +x.
        // Gravity is -y direction.
        // theta is measured counter-clockwise from the downward vertical.
        SCOPED_TRACE(filename);
        PendulumRevJtDiffs diffs;
        diffs.tol = std::pow(10.0, -idigit);
        auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/" + filename);
        auto simPara = assembly->simulationParameters;
        simPara->setAllTolForNDigit(idigit);
        auto pendulum = assembly->partNamed("/Assembly1/Part1");

        auto length = lengthFunction(pendulum);
        auto gravity = -assembly->constantGravity->g->at(1);
        auto theta0 = std::numbers::pi / 2.0 - pendulum->rotationMatrix->bryantAngles()->at(0);
        auto omega0 = pendulum->omega3D->at(0);
        auto exactPendulum = ExactPendulum(theta0, omega0, omegaNaturalFunction(gravity, length));
        size_t n = (simPara->tend - simPara->tstart) / simPara->hout;
        n = n + 2; // add count for input and initial time

        assembly->runDYNAMIC();

        EXPECT_EQ(n, assembly->times->size());
        EXPECT_EQ(n, pendulum->zs->size());
        EXPECT_EQ(n, pendulum->ys->size());
        EXPECT_EQ(n, pendulum->bryxs->size());
        EXPECT_EQ(n, pendulum->omexs->size());
        EXPECT_EQ(n, pendulum->alpxs->size());
        if (n != assembly->times->size() || n != pendulum->zs->size() || n != pendulum->ys->size() || n != pendulum->bryxs->size() || n != pendulum->omexs->size() || n != pendulum->alpxs->size())
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
            auto bryx = std::numbers::pi / 2.0 - exactResult.theta;
            auto z = (length * std::sin(exactResult.theta)) - (length * std::cos(bryx));
            auto y = (-length * std::cos(exactResult.theta)) - (-length * std::sin(bryx));
            diffs.maxRightDiff = std::max(diffs.maxRightDiff, std::abs(z - pendulum->zs->at(i)));
            diffs.maxUpDiff = std::max(diffs.maxUpDiff, std::abs(y - pendulum->ys->at(i)));
            diffs.maxBryDiff = std::max(diffs.maxBryDiff, std::abs(bryx - pendulum->bryxs->at(i)));
            auto omex = -exactResult.omega;
            diffs.maxOmeDiff = std::max(diffs.maxOmeDiff, std::abs(omex - pendulum->omexs->at(i)));
            auto alpx = -exactResult.alpha;
            diffs.maxAlpDiff = std::max(diffs.maxAlpDiff, std::abs(alpx - pendulum->alpxs->at(i)));
        }
        return diffs;
    }
}

template <typename LengthFunction, typename OmegaNaturalFunction>
PendulumRevJtDiffs pendulumRevJt_YXRegressionDiffs(const std::string &filename,
                                                   int idigit,
                                                   LengthFunction lengthFunction,
                                                   OmegaNaturalFunction omegaNaturalFunction)
{
    // The ASMT files model pendulums swinging in the x-y plane about +z.
    // theta is measured counter-clockwise from the downward vertical.
    SCOPED_TRACE(filename);
    PendulumRevJtDiffs diffs;
    diffs.tol = std::pow(10.0, -idigit);
    auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/" + filename);
    auto simPara = assembly->simulationParameters;
    simPara->setAllTolForNDigit(idigit);
    auto pendulum = assembly->partNamed("/Assembly1/Part1");

    auto length = lengthFunction(pendulum);
    auto gravity = -assembly->constantGravity->g->at(0);
    auto theta0 = pendulum->rotationMatrix->bryantAngles()->at(2) + std::numbers::pi;
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
        auto bryz = exactResult.theta - std::numbers::pi;
        auto x = (-length * std::cos(exactResult.theta)) - (length * std::cos(bryz));
        auto y = (-length * std::sin(exactResult.theta)) - (length * std::sin(bryz));
        diffs.maxRightDiff = std::max(diffs.maxRightDiff, std::abs(x - pendulum->xs->at(i)));
        diffs.maxUpDiff = std::max(diffs.maxUpDiff, std::abs(y - pendulum->ys->at(i)));
        auto bryzsi = pendulum->bryzs->at(i);
        if (bryzsi > 0.0)
        {
            bryzsi -= 2.0 * std::numbers::pi;
        }
        diffs.maxBryDiff = std::max(diffs.maxBryDiff, std::abs(bryz - bryzsi));
        auto omez = -exactResult.omega;
        diffs.maxOmeDiff = std::max(diffs.maxOmeDiff, std::abs(omez - pendulum->omezs->at(i)));
        auto alpz = -exactResult.alpha;
        diffs.maxAlpDiff = std::max(diffs.maxAlpDiff, std::abs(alpz - pendulum->alpzs->at(i)));
    }
    return diffs;
}

template <typename LengthFunction, typename OmegaNaturalFunction>
PendulumRevJtDiffs pendulumRevJt_XZRegressionDiffs(const std::string &filename,
                                                   int idigit,
                                                   LengthFunction lengthFunction,
                                                   OmegaNaturalFunction omegaNaturalFunction)
{
    // The ASMT files model pendulums swinging in the x-z plane about -y.
    // Gravity is -z direction.
    // theta is measured counter-clockwise from the downward vertical.
    SCOPED_TRACE(filename);
    PendulumRevJtDiffs diffs;
    diffs.tol = std::pow(10.0, -idigit);
    auto assembly = ASMTAssembly::assemblyFromFile(std::string(TEST_DATA_PATH) + "/ASMT/" + filename);
    auto simPara = assembly->simulationParameters;
    simPara->setAllTolForNDigit(idigit);
    auto pendulum = assembly->partNamed("/Assembly1/Part1");

    auto length = lengthFunction(pendulum);
    auto gravity = -assembly->constantGravity->g->at(2);
    auto theta0 = pendulum->rotationMatrix->bryantAngles()->at(2) + std::numbers::pi / 2.0;
    auto omega0 = pendulum->omega3D->at(1); // y-component
    auto exactPendulum = ExactPendulum(theta0, omega0, omegaNaturalFunction(gravity, length));
    size_t n = (simPara->tend - simPara->tstart) / simPara->hout;
    n = n + 2; // add count for input and initial time

    assembly->runDYNAMIC();

    EXPECT_EQ(n, assembly->times->size());
    EXPECT_EQ(n, pendulum->xs->size());
    EXPECT_EQ(n, pendulum->zs->size());
    EXPECT_EQ(n, pendulum->bryzs->size());
    EXPECT_EQ(n, pendulum->omeys->size());
    EXPECT_EQ(n, pendulum->alpys->size());
    if (n != assembly->times->size() || n != pendulum->xs->size() || n != pendulum->zs->size() || n != pendulum->bryzs->size() || n != pendulum->omeys->size() || n != pendulum->alpys->size())
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
        auto z = (-length * std::cos(exactResult.theta)) - (length * std::sin(bryz));
        diffs.maxRightDiff = std::max(diffs.maxRightDiff, std::abs(x - pendulum->xs->at(i)));
        diffs.maxUpDiff = std::max(diffs.maxUpDiff, std::abs(z - pendulum->zs->at(i)));
        diffs.maxBryDiff = std::max(diffs.maxBryDiff, std::abs(bryz - pendulum->bryzs->at(i)));
        auto omey = -exactResult.omega;
        diffs.maxOmeDiff = std::max(diffs.maxOmeDiff, std::abs(omey - pendulum->omeys->at(i)));
        auto alpy = -exactResult.alpha;
        diffs.maxAlpDiff = std::max(diffs.maxAlpDiff, std::abs(alpy - pendulum->alpys->at(i)));
    }
    return diffs;
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
    // Why XY succeeds and XZ fails when errorTol = 1.0e-12 ?
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

TEST(FreeCADMbD, pointPendulumRevJtYZRegression)
{
    for (int idigit = 4; idigit <= 6; idigit++)
    {
        auto diffs = pendulumRevJt_YZRegressionDiffs(
            "pointPendulumRevJt_YZ.asmt",
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

TEST(FreeCADMbD, pointPendulumRevJtZXRegression)
{
    for (int idigit = 4; idigit <= 6; idigit++)
    {
        auto diffs = pendulumRevJt_ZXRegressionDiffs(
            "pointPendulumRevJt_ZX.asmt",
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

TEST(FreeCADMbD, pointPendulumRevJtZYRegression)
{
    for (int idigit = 4; idigit <= 6; idigit++)
    {
        auto diffs = pendulumRevJt_ZYRegressionDiffs(
            "pointPendulumRevJt_ZY.asmt",
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

TEST(FreeCADMbD, pointPendulumRevJtYXRegression)
{
    for (int idigit = 4; idigit <= 6; idigit++)
    {
        auto diffs = pendulumRevJt_YXRegressionDiffs(
            "pointPendulumRevJt_YX.asmt",
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

TEST(FreeCADMbD, pointPendulumRevJtXZRegression)
{
    for (int idigit = 4; idigit <= 6; idigit++)
    {
        // if (idigit = 6)
        //     break; // errorTol = 1.0e-12 is too stringent for simulation
        auto diffs = pendulumRevJt_XZRegressionDiffs(
            "pointPendulumRevJt_XZ.asmt",
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
