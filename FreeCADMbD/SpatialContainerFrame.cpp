/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "SpatialContainerFrame.h"
#include "Part.h"
#include "EulerConstraint.h"
#include "AbsConstraint.h"
#include "MarkerFramec.h"
#include "EulerParameters.h"
#include "EulerParametersDot.h"
#include "RedundantConstraint.h"
#include "System.h"

using namespace MbD;

void SpatialContainerFrame::initialize()
{
    markerFrames = std::make_shared<std::vector<std::shared_ptr<MarkerFramec>>>();
}

void SpatialContainerFrame::initializeLocally()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->initializeLocally(); });
}

void SpatialContainerFrame::initializeGlobally()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->initializeGlobally(); });
}

void SpatialContainerFrame::addMarkerFrame(std::shared_ptr<MarkerFramec> markerFrame)
{
    markerFrame->setPartFrame(this);
    markerFrames->push_back(markerFrame);
}

EndFrmsptr SpatialContainerFrame::endFrame(std::string name) const
{
    auto match = std::find_if(markerFrames->begin(), markerFrames->end(), [&](auto mkr) {return mkr->name == name; });
    return (*match)->endFrames->at(0);
}

void SpatialContainerFrame::markerFramesDo(const std::function<void(std::shared_ptr<MarkerFramec>)>& f) const
{
    for (const auto markerFrame : *markerFrames) f(markerFrame);
}

void SpatialContainerFrame::prePosIC()
{
    CartesianFrame::prePosIC();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrm) { markerFrm->prePosIC(); });
}

void SpatialContainerFrame::prePosKine()
{
    CartesianFrame::prePosKine();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrm) { markerFrm->prePosKine(); });
}

void SpatialContainerFrame::fillqsuWeights(DiagMatDsptr diagMat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsuWeights(diagMat); });
}

void SpatialContainerFrame::fillqsuddotlam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsuddotlam(col); });
}

void SpatialContainerFrame::fillqsulam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsulam(col); });
}

void SpatialContainerFrame::fillpqsumu(FColDsptr col)
{
    //"Fill q, s and lam into col."
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillpqsumu(col); });
}

void SpatialContainerFrame::fillpqsumudot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillpqsumudot(col); });
}

void SpatialContainerFrame::fillqsudot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsudot(col); });
}

void SpatialContainerFrame::fillqsudotWeights(DiagMatDsptr diagMat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillqsudotWeights(diagMat); });
}

void SpatialContainerFrame::useEquationNumbers()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->useEquationNumbers(); });
}

void SpatialContainerFrame::setqsu(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsu(col); });
}

void SpatialContainerFrame::setqsulam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsulam(col); });
}

void SpatialContainerFrame::setqsudotlam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsudotlam(col); });
}

void SpatialContainerFrame::setqsudot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsudot(col); });
}

void SpatialContainerFrame::postPosICIteration()
{
    CartesianFrame::postPosICIteration();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postPosICIteration(); });
}

void SpatialContainerFrame::fillPosICError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillPosICError(col); });
}

void SpatialContainerFrame::fillPosICJacob(SpMatDsptr mat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillPosICJacob(mat); });
}

void SpatialContainerFrame::postPosIC()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postPosIC(); });
}

void SpatialContainerFrame::preDyn()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->preDyn(); });
}

void SpatialContainerFrame::storeDynState()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->storeDynState(); });
}

void SpatialContainerFrame::fillPosKineError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillPosKineError(col); });
}

void SpatialContainerFrame::preVelIC()
{
    CartesianFrame::preVelIC();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->preVelIC(); });
}

void SpatialContainerFrame::postVelIC()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postVelIC(); });
}

void SpatialContainerFrame::fillVelICError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillVelICError(col); });
}

void SpatialContainerFrame::fillVelICJacob(SpMatDsptr mat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillVelICJacob(mat); });
}

void SpatialContainerFrame::preAccIC()
{
    CartesianFrame::preAccIC();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->preAccIC(); });
}

void SpatialContainerFrame::fillAccICIterError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillAccICIterError(col); });
}

void SpatialContainerFrame::fillAccICIterJacob(SpMatDsptr mat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillAccICIterJacob(mat); });
}

void SpatialContainerFrame::setqsuddotlam(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setqsuddotlam(col); });
}

void SpatialContainerFrame::fillPosKineJacob(SpMatDsptr mat)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillPosKineJacob(mat); });
}

void SpatialContainerFrame::postDynStep()
{
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postDynStep(); });
}

void SpatialContainerFrame::setpqsumu(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setpqsumu(col); });
}

void SpatialContainerFrame::setpqsumudot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setpqsumudot(col); });
}

void SpatialContainerFrame::setpqsumuddot(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->setpqsumuddot(col); });
}

void SpatialContainerFrame::postDynPredictor()
{
    CartesianFrame::postDynPredictor();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postDynPredictor(); });
}

void SpatialContainerFrame::fillDynError(FColDsptr col)
{
    markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillDynError(col); });
}

void SpatialContainerFrame::fillpFpy(SpMatDsptr mat)
{
    //markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillpFpy(mat); });
}

void SpatialContainerFrame::fillpFpydot(SpMatDsptr mat)
{
    //markerFramesDo([&](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->fillpFpydot(mat); });
}

void SpatialContainerFrame::postDynCorrectorIteration()
{
    CartesianFrame::postDynCorrectorIteration();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postDynCorrectorIteration(); });
}

void SpatialContainerFrame::preDynOutput()
{
    CartesianFrame::preDynOutput();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->preDynOutput(); });
}

void SpatialContainerFrame::postDynOutput()
{
    CartesianFrame::postDynOutput();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postDynOutput(); });
}

size_t SpatialContainerFrame::iqX() const
{
    throw SimulationStoppingError("To be implemented.");
    return size_t();
}

size_t SpatialContainerFrame::iqE() const
{
    throw SimulationStoppingError("To be implemented.");
    return size_t();
}

FColDsptr SpatialContainerFrame::qX()
{
    return FColDsptr();
}

std::shared_ptr<EulerParameters<double>> SpatialContainerFrame::qE()
{
    return std::shared_ptr<EulerParameters<double>>();
}

FColDsptr SpatialContainerFrame::qXdot()
{
    return FColDsptr();
}

std::shared_ptr<EulerParametersDot<double>> SpatialContainerFrame::qEdot()
{
    return std::shared_ptr<EulerParametersDot<double>>();
}

FColDsptr SpatialContainerFrame::qXddot()
{
    return FColDsptr();
}

FColDsptr SpatialContainerFrame::qEddot()
{
    return FColDsptr();
}

FMatDsptr SpatialContainerFrame::aAOp()
{
    return FMatDsptr();
}

FMatDsptr SpatialContainerFrame::aC()
{
    return FMatDsptr();
}

FMatDsptr SpatialContainerFrame::aCdot()
{
    return FMatDsptr();
}

FColDsptr SpatialContainerFrame::alpOpO()
{
    return FColDsptr();
}

FColFMatDsptr SpatialContainerFrame::pAOppE()
{
    return FColFMatDsptr();
}

FColFMatDsptr SpatialContainerFrame::pAdotOppE()
{
    return FColFMatDsptr();
}

FMatDsptr SpatialContainerFrame::pomeOpOpE()
{
    return FMatDsptr();
}

FMatDsptr SpatialContainerFrame::pomeOpOpEdot()
{
    return FMatDsptr();
}

FColDsptr SpatialContainerFrame::vOpO()
{
    return FColDsptr();
}

FMatDsptr SpatialContainerFrame::aAdotOp()
{
    return FMatDsptr();
}

FColDsptr SpatialContainerFrame::aOpO()
{
    return FColDsptr();
}

FMatDsptr SpatialContainerFrame::aAddotOp()
{
    return FMatDsptr();
}

FColDsptr SpatialContainerFrame::omeOpO()
{
    return FColDsptr();
}

FMatDsptr SpatialContainerFrame::aBOp() const
{
    return FMatDsptr();
}

FColDsptr SpatialContainerFrame::aOmO() const
{
    return FColDsptr();
}

void SpatialContainerFrame::postInput()
{
    CartesianFrame::postInput();
    markerFramesDo([](std::shared_ptr<MarkerFramec> markerFrame) { markerFrame->postInput(); });
}
