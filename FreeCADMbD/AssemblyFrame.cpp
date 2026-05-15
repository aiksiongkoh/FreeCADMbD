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
#include "MarkerFrame.h"
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

MkrFrmsptr AssemblyFrame::createMarkerFrame(const std::string& str)
{
    return MarkerFrame::With(str);
}

System* AssemblyFrame::root()
{
    return assembly->root();
}

void AssemblyFrame::initializeLocally()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->initializeLocally();
        });
}

void AssemblyFrame::initializeGlobally()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->initializeGlobally();
        });
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
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsu(col);
        });
}

void AssemblyFrame::fillqsuWeights(DiagMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsuWeights(mat);
        });
}

void AssemblyFrame::fillqsuddotlam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsuddotlam(col);
        });
}

void AssemblyFrame::fillqsulam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsulam(col);
        });
}

void AssemblyFrame::fillpqsumu(FColDsptr col)
{
    //"Fill q, s and lam into col."
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillpqsumu(col);
        });
}

void AssemblyFrame::fillpqsumudot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillpqsumudot(col);
        });
}

void AssemblyFrame::fillqsudot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsudot(col);
        });
}

void AssemblyFrame::fillqsudotWeights(DiagMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsudotWeights(mat);
        });
}

void AssemblyFrame::useEquationNumbers()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->useEquationNumbers();
        });
}

void AssemblyFrame::setqsu(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsu(col);
        });
}

void AssemblyFrame::setqsulam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsulam(col);
        });
}

void AssemblyFrame::setqsudotlam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsudotlam(col);
        });
}

void AssemblyFrame::setqsudot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsudot(col);
        });
}

void AssemblyFrame::postPosICIteration()
{
    CartesianFrame::postPosICIteration();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postPosICIteration();
        });
}

void AssemblyFrame::fillPosICError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillPosICError(col);
        });
}

void AssemblyFrame::fillPosICJacob(SpMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillPosICJacob(mat);
        });
}

void AssemblyFrame::postPosIC()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postPosIC();
        });
}

void AssemblyFrame::preDyn()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->preDyn();
        });
}

void AssemblyFrame::storeDynState()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->storeDynState();
        });
}

void AssemblyFrame::fillPosKineError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillPosKineError(col);
        });
}

void AssemblyFrame::preVelIC()
{
    CartesianFrame::preVelIC();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->preVelIC();
        });
}

void AssemblyFrame::postVelIC()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postVelIC();
        });
}

void AssemblyFrame::fillVelICError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillVelICError(col);
        });
}

void AssemblyFrame::fillVelICJacob(SpMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillVelICJacob(mat);
        });
}

void AssemblyFrame::preAccIC()
{
    CartesianFrame::preAccIC();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->preAccIC();
        });
}

void AssemblyFrame::fillAccICIterError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillAccICIterError(col);
        });
}

void AssemblyFrame::fillAccICIterJacob(SpMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillAccICIterJacob(mat);
        });
}

void AssemblyFrame::setqsuddotlam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsuddotlam(col);
        });
}

void AssemblyFrame::fillPosKineJacob(SpMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillPosKineJacob(mat);
        });
}

double AssemblyFrame::suggestSmallerOrAcceptDynStepSize(double hnew)
{
    //"Default is return hnew."
    return hnew;
}

void AssemblyFrame::postDynStep()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postDynStep();
        });
}

void AssemblyFrame::setpqsumu(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setpqsumu(col);
        });
}

void AssemblyFrame::setpqsumudot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setpqsumudot(col);
        });
}

void AssemblyFrame::setpqsumuddot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setpqsumuddot(col);
        });
}

void AssemblyFrame::postDynPredictor()
{
    CartesianFrame::postDynPredictor();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postDynPredictor();
        });
}

void AssemblyFrame::fillDynError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillDynError(col);
        });
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
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postDynCorrectorIteration();
        });
}

void AssemblyFrame::preDynOutput()
{
    CartesianFrame::preDynOutput();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->preDynOutput();
        });
}

void AssemblyFrame::postDynOutput()
{
    CartesianFrame::postDynOutput();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postDynOutput();
        });
}

void AssemblyFrame::postInput()
{
    CartesianFrame::postInput();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postInput();
        });
}

void AssemblyFrame::simUpdateAll()
{
    //Do nothing.
}
