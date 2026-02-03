/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "AssemblyFrame.h"
#include "Part.h"
#include "EulerConstraint.h"
#include "AbsConstraint.h"
#include "MarkerFramec.h"
#include "EulerParameters.h"
#include "EulerParametersDot.h"
#include "RedundantConstraint.h"
#include "System.h"

using namespace MbD;

AssemblyFrame::AssemblyFrame(const std::string& str) : SpatialContainerFrame(str)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<AssemblyFrame> AssemblyFrame::With()
{
    auto inst = std::make_shared<AssemblyFrame>();
    inst->initialize();
    return inst;
}

std::shared_ptr<AssemblyFrame> AssemblyFrame::With(const std::string& str)
{
    auto inst = std::make_shared<AssemblyFrame>(str);
    inst->initialize();
    return inst;
}

std::shared_ptr<MarkerFramec> MbD::AssemblyFrame::createMarkerFrame(const std::string& str)
{
    return MarkerFramec::With(str);
}

System* AssemblyFrame::root()
{
    return assembly->root();
}

void AssemblyFrame::initializeLocally()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->initializeLocally(); });
}

void AssemblyFrame::initializeGlobally()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->initializeGlobally(); });
}

void AssemblyFrame::setAssembly(System* x) {
    assembly = x;
}

System* AssemblyFrame::getAssembly() const {
    return assembly;
}

void AssemblyFrame::setPart(Part* x)
{
    //Do nothing.
}

FColFMatDsptr AssemblyFrame::pAOppE()
{
    auto eulerParameters = EulerParameters<double>::With(ListD{ 0.0, 0.0, 0.0, 1.0 });
    eulerParameters->calcpApE();
    return eulerParameters->pApE;
}

void AssemblyFrame::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos)
{
    //Do nothing.
}

void AssemblyFrame::reactivateRedundantConstraints()
{
    //Do nothing.
}

void AssemblyFrame::constraintsReport()
{
    //Do nothing.
}

void AssemblyFrame::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
    //Do nothing.
}

void AssemblyFrame::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
    //Do nothing.
}

void AssemblyFrame::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints)
{
    //Do nothing.
}

void AssemblyFrame::fillqsu(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsu(col); });
}

void AssemblyFrame::fillqsuWeights(DiagMatDsptr diagMat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsuWeights(diagMat); });
}

void AssemblyFrame::fillqsuddotlam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsuddotlam(col); });
}

void AssemblyFrame::fillqsulam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsulam(col); });
}

void AssemblyFrame::fillpqsumu(FColDsptr col)
{
    //"Fill q, s and lam into col."
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillpqsumu(col); });
}

void AssemblyFrame::fillpqsumudot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillpqsumudot(col); });
}

void AssemblyFrame::fillqsudot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsudot(col); });
}

void AssemblyFrame::fillqsudotWeights(DiagMatDsptr diagMat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsudotWeights(diagMat); });
}

void AssemblyFrame::useEquationNumbers()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->useEquationNumbers(); });
}

void AssemblyFrame::setqsu(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsu(col); });
}

void AssemblyFrame::setqsulam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsulam(col); });
}

void AssemblyFrame::setqsudotlam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsudotlam(col); });
}

void AssemblyFrame::setqsudot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsudot(col); });
}

void AssemblyFrame::postPosICIteration()
{
    CartesianFrame::postPosICIteration();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postPosICIteration(); });
}

void AssemblyFrame::fillPosICError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillPosICError(col); });
}

void AssemblyFrame::fillPosICJacob(SpMatDsptr mat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillPosICJacob(mat); });
}

void AssemblyFrame::postPosIC()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postPosIC(); });
}

void AssemblyFrame::preDyn()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->preDyn(); });
}

void AssemblyFrame::storeDynState()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->storeDynState(); });
}

void AssemblyFrame::fillPosKineError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillPosKineError(col); });
}

void AssemblyFrame::preVelIC()
{
    CartesianFrame::preVelIC();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->preVelIC(); });
}

void AssemblyFrame::postVelIC()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postVelIC(); });
}

void AssemblyFrame::fillVelICError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillVelICError(col); });
}

void AssemblyFrame::fillVelICJacob(SpMatDsptr mat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillVelICJacob(mat); });
}

void AssemblyFrame::preAccIC()
{
    CartesianFrame::preAccIC();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->preAccIC(); });
}

void AssemblyFrame::fillAccICIterError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillAccICIterError(col); });
}

void AssemblyFrame::fillAccICIterJacob(SpMatDsptr mat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillAccICIterJacob(mat); });
}

void AssemblyFrame::setqsuddotlam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsuddotlam(col); });
}

void AssemblyFrame::fillPosKineJacob(SpMatDsptr mat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillPosKineJacob(mat); });
}

double AssemblyFrame::suggestSmallerOrAcceptDynStepSize(double hnew)
{
    //"Default is return hnew."
    return hnew;
}

void AssemblyFrame::postDynStep()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postDynStep(); });
}

void AssemblyFrame::setpqsumu(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setpqsumu(col); });
}

void AssemblyFrame::setpqsumudot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setpqsumudot(col); });
}

void AssemblyFrame::setpqsumuddot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setpqsumuddot(col); });
}

void AssemblyFrame::postDynPredictor()
{
    CartesianFrame::postDynPredictor();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postDynPredictor(); });
}

void AssemblyFrame::fillDynError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillDynError(col); });
}

void AssemblyFrame::fillpFpy(SpMatDsptr mat)
{
    //Do nothing.
}

void AssemblyFrame::fillpFpydot(SpMatDsptr mat)
{
    //Do nothing.
}

void AssemblyFrame::postDynCorrectorIteration()
{
    CartesianFrame::postDynCorrectorIteration();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postDynCorrectorIteration(); });
}

void AssemblyFrame::preDynOutput()
{
    CartesianFrame::preDynOutput();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->preDynOutput(); });
}

void AssemblyFrame::postDynOutput()
{
    CartesianFrame::postDynOutput();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postDynOutput(); });
}

void AssemblyFrame::postInput()
{
    CartesianFrame::postInput();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postInput(); });
}

void AssemblyFrame::simUpdateAll()
{
    //Do nothing.
}
