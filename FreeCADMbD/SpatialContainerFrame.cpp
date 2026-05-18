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
#include "MarkerFrame.h"
#include "EulerParameters.h"
#include "EulerParametersDot.h"
#include "RedundantConstraint.h"
#include "System.h"

using namespace MbD;

void SpatialContainerFrame::initialize()
{
    markerFrames = std::make_shared<std::vector<MkrFrmsptr>>();
}

void SpatialContainerFrame::initializeLocally()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->initializeLocally();
        });
}

void SpatialContainerFrame::initializeGlobally()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->initializeGlobally();
        });
}

void SpatialContainerFrame::addMarkerFrame(MkrFrmsptr markerFrame)
{
    markerFrame->setPartFrame(this);
    markerFrames->push_back(markerFrame);
}

EndFrmsptr SpatialContainerFrame::endFrame(std::string name) const
{
    auto match = std::find_if(markerFrames->begin(), markerFrames->end(), [&](auto mkr) {return mkr->name == name; });
    return (*match)->endFrames->at(0);
}

void SpatialContainerFrame::markerFramesDo(const std::function<void(MkrFrmsptr)>& f) const
{
    for (const auto markerFrame : *markerFrames) f(markerFrame);
}

void SpatialContainerFrame::prePosIC()
{
    CartesianFrame::prePosIC();
    markerFramesDo([&](MkrFrmsptr markerFrm) {
        markerFrm->prePosIC();
        });
}

void SpatialContainerFrame::prePosKine()
{
    CartesianFrame::prePosKine();
    markerFramesDo([&](MkrFrmsptr markerFrm) {
        markerFrm->prePosKine();
        });
}

void MbD::SpatialContainerFrame::preStatic()
{
    CartesianFrame::preStatic();
    markerFramesDo([&](MkrFrmsptr markerFrm) {
        markerFrm->preStatic();
        });
}

void SpatialContainerFrame::fillqsuWeights(DiagMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsuWeights(mat);
        });
}

void SpatialContainerFrame::fillqsuddotlam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsuddotlam(col);
        });
}

void SpatialContainerFrame::fillqsulam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsulam(col);
        });
}

void SpatialContainerFrame::fillpqsumu(FColDsptr col)
{
    //"Fill q, s and lam into col."
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillpqsumu(col);
        });
}

void SpatialContainerFrame::fillpqsumudot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillpqsumudot(col);
        });
}

void SpatialContainerFrame::fillqsudot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsudot(col);
        });
}

void SpatialContainerFrame::fillqsudotWeights(DiagMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillqsudotWeights(mat);
        });
}

void SpatialContainerFrame::useEquationNumbers()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->useEquationNumbers();
        });
}

void SpatialContainerFrame::setqsu(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsu(col);
        });
}

void SpatialContainerFrame::setqsulam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsulam(col);
        });
}

void SpatialContainerFrame::setqsudotlam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsudotlam(col);
        });
}

void SpatialContainerFrame::setqsudot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsudot(col);
        });
}

void SpatialContainerFrame::postPosICIteration()
{
    CartesianFrame::postPosICIteration();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postPosICIteration();
        });
}

void SpatialContainerFrame::fillPosICError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillPosICError(col);
        });
}

void SpatialContainerFrame::fillPosICJacob(SpMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillPosICJacob(mat);
        });
}

void SpatialContainerFrame::postPosIC()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postPosIC();
        });
}

void SpatialContainerFrame::preDyn()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->preDyn();
        });
}

void SpatialContainerFrame::storeDynState()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->storeDynState();
        });
}

void SpatialContainerFrame::fillPosKineError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillPosKineError(col);
        });
}

void SpatialContainerFrame::preVelIC()
{
    CartesianFrame::preVelIC();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->preVelIC();
        });
}

void SpatialContainerFrame::postVelIC()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postVelIC();
        });
}

void SpatialContainerFrame::fillVelICError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillVelICError(col);
        });
}

void SpatialContainerFrame::fillVelICJacob(SpMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillVelICJacob(mat);
        });
}

void SpatialContainerFrame::preAccIC()
{
    CartesianFrame::preAccIC();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->preAccIC();
        });
}

void SpatialContainerFrame::fillAccICIterError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillAccICIterError(col);
        });
}

void SpatialContainerFrame::fillAccICIterJacob(SpMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillAccICIterJacob(mat);
        });
}

void SpatialContainerFrame::setqsuddotlam(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setqsuddotlam(col);
        });
}

void SpatialContainerFrame::fillPosKineJacob(SpMatDsptr mat)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillPosKineJacob(mat);
        });
}

void SpatialContainerFrame::postDynStep()
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postDynStep();
        });
}

void SpatialContainerFrame::setpqsumu(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setpqsumu(col);
        });
}

void SpatialContainerFrame::setpqsumudot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setpqsumudot(col);
        });
}

void SpatialContainerFrame::setpqsumuddot(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->setpqsumuddot(col);
        });
}

void SpatialContainerFrame::postDynPredictor()
{
    CartesianFrame::postDynPredictor();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postDynPredictor();
        });
}

void SpatialContainerFrame::fillDynError(FColDsptr col)
{
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->fillDynError(col);
        });
}

void SpatialContainerFrame::fillpFpy(SpMatDsptr mat)
{
    //markerFramesDo([&](MkrFrmsptr markerFrame) {
    // markerFrame->fillpFpy(mat);
    // });
}

void SpatialContainerFrame::fillpFpydot(SpMatDsptr mat)
{
    //markerFramesDo([&](MkrFrmsptr markerFrame) {
    // markerFrame->fillpFpydot(mat);
    // });
}

void SpatialContainerFrame::postDynCorrectorIteration()
{
    CartesianFrame::postDynCorrectorIteration();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postDynCorrectorIteration();
        });
}

void SpatialContainerFrame::preDynOutput()
{
    CartesianFrame::preDynOutput();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->preDynOutput();
        });
}

void SpatialContainerFrame::postDynOutput()
{
    CartesianFrame::postDynOutput();
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postDynOutput();
        });
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
    markerFramesDo([&](MkrFrmsptr markerFrame) {
        markerFrame->postInput();
        });
}
