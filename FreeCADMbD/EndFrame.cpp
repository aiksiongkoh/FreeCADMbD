/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <assert.h>
#include <memory>

#include "EndFrame.h"
#include "SpatialContainerFrame.h"
#include "MarkerFrame.h"
#include "EndFrameq.h"
#include "EndFramet.h"
#include "SimulationStoppingError.h"

using namespace MbD;

EndFrmsptr EndFrame::With()
{
    auto inst = std::make_shared<EndFrame>();
    inst->initialize();
    return inst;
}

EndFrmsptr EndFrame::With(const std::string &str)
{
    auto inst = std::make_shared<EndFrame>(str);
    inst->initialize();
    return inst;
}

void EndFrame::initialize()
{
    // Do nothing.
}

FMatDsptr EndFrame::aAeO() const
{
    return aAOe->transpose();
}

System *EndFrame::root()
{
    return markerFrame->root();
}

void EndFrame::setMarkerFrame(MarkerFrame *markerFrm)
{
    markerFrame = markerFrm;
}

MarkerFrame *EndFrame::getMarkerFrame() const
{
    return markerFrame;
}

void EndFrame::initEndFrameqt()
{
    endFramet = EndFramet::With(name.data());
    endFramet->setMarkerFrame(markerFrame);
}

void EndFrame::initEndFrameqt2()
{
    initEndFrameqt();
}

void EndFrame::simUpdateAll()
{
    // rOeO = rOmO + aAOm*rmem
    // aAOe = aAOm*aAme;
    rOeO = markerFrame->rOmO->plusFullColumn(markerFrame->aAOm->timesFullColumn(rmem));
    aAOe = markerFrame->aAOm->timesFullMatrix(aAme);
}

void EndFrame::fillContactEndFrames(std::set<EndFrame *> efrms)
{
}

FColDsptr EndFrame::ieO() const
{
    return aAOe->column(0);
}

FColDsptr EndFrame::jeO() const
{
    return aAOe->column(1);
}

FColDsptr EndFrame::keO() const
{
    return aAOe->column(2);
}

FColDsptr EndFrame::aAjOe(size_t j) const
{
    return aAOe->column(j);
}

void EndFrame::aApm(FMatDsptr mat)
{
    markerFrame->aApm = mat;
}

double EndFrame::riOeO(size_t i) const
{
    return rOeO->at(i);
}

FColDsptr EndFrame::rpmp()
{
    return markerFrame->rpmp;
}

FColDsptr EndFrame::rmeO()
{
    return markerFrame->aAOm->timesFullColumn(rmem);
}

FColDsptr EndFrame::rpep()
{
    return FColDsptr();
}

FColFMatDsptr EndFrame::pAOppE()
{
    return FColFMatDsptr();
}

FMatDsptr EndFrame::aBOp() const
{
    double aE0 = 0.0;
    double aE1 = 0.0;
    double aE2 = 0.0;
    double aE3 = 1.0;
    double mE0 = -aE0;
    double mE1 = -aE1;
    double mE2 = -aE2;
    auto aB = FullMatrix<double>::With(3, 4);
    FRowDsptr aBi;
    aBi = aB->at(0);
    aBi->at(0) = aE3;
    aBi->at(1) = mE2;
    aBi->at(2) = aE1;
    aBi->at(3) = mE0;
    aBi = aB->at(1);
    aBi->at(0) = aE2;
    aBi->at(1) = aE3;
    aBi->at(2) = mE0;
    aBi->at(3) = mE1;
    aBi = aB->at(2);
    aBi->at(0) = mE1;
    aBi->at(1) = aE0;
    aBi->at(2) = aE3;
    aBi->at(3) = mE2;

    return aB;
}

FMatDsptr EndFrame::getaBOp() const
{
    return aBOp();
}

std::shared_ptr<EndFrameq> EndFrame::newCopyEndFrameq()
{
    auto eFrm = EndFrameq::With();
    markerFrame->addEndFrame(eFrm);
    return eFrm;
}

EndFrmsptr EndFrame::followEndFrame(EndFrmsptr frmi)
{
    throw SimulationStoppingError("Fixed eFrm cannot move to follow.");
}

bool EndFrame::isEndFrameq()
{
    return false;
}

SpatialContainerFrame *EndFrame::getPartFrame() const
{
    return markerFrame->getPartFrame();
}

std::shared_ptr<EulerParameters<double>> EndFrame::qEOe() const
{
    return aAOe->asEulerParameters();
}

FColDsptr EndFrame::vOeO() const
{
    return markerFrame->vOmO();
}

FMatDsptr EndFrame::getprOeOpE() const
{
    return FMatDsptr();
}

FMatFColDsptr EndFrame::getpprOeOpEpE() const
{
    return FMatFColDsptr();
}

FColDsptr EndFrame::getprOeOpt() const
{
    return FColDsptr();
}

FMatDsptr EndFrame::getpprOeOpEpt() const
{
    return FMatDsptr();
}

FColDsptr EndFrame::getpprOeOptpt() const
{
    return FColDsptr();
}

FMatDsptr EndFrame::getpAOept() const
{
    return FMatDsptr();
}

FColFMatDsptr EndFrame::getppAOepEpt() const
{
    return FColFMatDsptr();
}

FMatDsptr EndFrame::getppAOeptpt() const
{
    return FMatDsptr();
}

FMatDsptr EndFrame::pAOepEtimesFullColumn(FColDsptr col) const
{
    return FMatDsptr();
}

FMatDsptr EndFrame::pAOeTpEtimesFullColumn(FColDsptr col) const
{
    return FMatDsptr();
}

FMatFColDsptr EndFrame::ppAOeTpEpEtimesFullColumn(FColDsptr col) const
{
    return FMatFColDsptr();
}

FMatDsptr EndFrame::ppAOeTpEpttimesFullColumn(FColDsptr col) const
{
    return FMatDsptr();
}

FMatFColDsptr EndFrame::pAOeTpEtimesFullMatrix(FMatDsptr mat) const
{
    return FMatFColDsptr();
}

FColDsptr EndFrame::aOeO() const
{
    return markerFrame->aOmO();
}

FMatDsptr EndFrame::pAjOepE(size_t j) const
{
    throw SimulationStoppingError("To be implemented.");
}

FMatDsptr EndFrame::pAjOepET(size_t axis)
{
    auto answer = FullMatrix<double>::With(4, 3);
    for (size_t i = 0; i < 4; i++)
    {
        auto answeri = answer->at(i);
        auto pAOepEi = getpAOepE()->at(i);
        for (size_t j = 0; j < 3; j++)
        {
            auto answerij = pAOepEi->at(j)->at(axis);
            answeri->at(j) = answerij;
        }
    }
    return answer;
}

FColFMatDsptr EndFrame::getpAOepE() const
{
    // rOeO = rOmO + aAOm*rmem
    // aAOe = aAOm*aAme;
    auto pAOepE = std::make_shared<FullColumn<FMatDsptr>>(4);
    auto mrkFrmc = static_cast<MarkerFrame *>(markerFrame);
    for (size_t i = 0; i < 4; i++)
    {
        auto prOmOpEi = mrkFrmc->prOmOpE()->column(i);
        auto pAOmpEi = mrkFrmc->pAOmpE()->at(i); // Make a copy
        pAOepE->atiput(i, pAOmpEi->timesFullMatrix(aAme));
    }
    return pAOepE;
}

FColDsptr EndFrame::omeOeO()
{
    return static_cast<MarkerFrame *>(markerFrame)->omeOmO();
}
