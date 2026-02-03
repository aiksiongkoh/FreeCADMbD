/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <assert.h>
#include <memory>

#include "EndFramec.h"
#include "SpatialContainerFrame.h"
#include "MarkerFramec.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<EndFramec> EndFramec::With()
{
    auto inst = std::make_shared<EndFramec>();
    inst->initialize();
    return inst;
}

std::shared_ptr<EndFramec> EndFramec::With(const std::string& str)
{
    auto inst = std::make_shared<EndFramec>(str);
    inst->initialize();
    return inst;
}

void EndFramec::initialize()
{
    //Do nothing.
}

FMatDsptr EndFramec::aAeO() const
{
    return aAOe->transpose();
}

System* EndFramec::root()
{
    return markerFrame->root();
}

void EndFramec::setMarkerFrame(MarkerFramec* markerFrm)
{
    markerFrame = markerFrm;
}

MarkerFramec* EndFramec::getMarkerFrame() const
{
    return markerFrame;
}

void EndFramec::initEndFrameqct()
{
    endFramect = EndFramect::With(name.data());
    endFramect->setMarkerFrame(markerFrame);
}

void EndFramec::initEndFrameqct2()
{
    throw SimulationStoppingError("To be implemented.");
}

void EndFramec::simUpdateAll()
{
    //rOeO = rOmO + aAOm*rmem
    //aAOe = aAOm*aAme;
    rOeO = markerFrame->rOmO->plusFullColumn(markerFrame->aAOm->timesFullColumn(rmem));
    aAOe = markerFrame->aAOm->timesFullMatrix(aAme);
}

void EndFramec::fillContactEndFrames(std::set<EndFramec*> efrms)
{
}

FColDsptr EndFramec::ieO() const
{
    return aAOe->column(0);
}

FColDsptr EndFramec::jeO() const
{
    return aAOe->column(1);
}

FColDsptr EndFramec::keO() const
{
    return aAOe->column(2);
}

FColDsptr EndFramec::aAjOe(size_t j) const
{
    return aAOe->column(j);
}

void EndFramec::aApm(FMatDsptr mat)
{
    markerFrame->aApm = mat;
}

double EndFramec::riOeO(size_t i) const
{
    return rOeO->at(i);
}

FColDsptr EndFramec::rpmp()
{
    return markerFrame->rpmp;
}

FColDsptr EndFramec::rmeO()
{
    return markerFrame->aAOm->timesFullColumn(rmem);
}

FColDsptr EndFramec::rpep()
{
    return FColDsptr();
}

FColFMatDsptr EndFramec::pAOppE()
{
    return FColFMatDsptr();
}

FMatDsptr EndFramec::aBOp() const
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

FMatDsptr MbD::EndFramec::getaBOp() const
{
    return aBOp();
}

std::shared_ptr<EndFrameqc> EndFramec::newCopyEndFrameqc()
{
    auto frmIeqc = EndFrameqc::With();
    markerFrame->addEndFrame(frmIeqc);
    return frmIeqc;
}

std::shared_ptr<EndFramec> EndFramec::followEndFrame(EndFrmsptr frmi)
{
    throw SimulationStoppingError("Fixed eFrm cannot move to follow.");
    return std::shared_ptr<EndFramec>();
}

bool EndFramec::isEndFrameqc()
{
    return false;
}

SpatialContainerFrame* EndFramec::getPartFrame() const
{
    return markerFrame->getPartFrame();
}

std::shared_ptr<EulerParameters<double>> EndFramec::qEOe() const
{
    return aAOe->asEulerParameters();
}

FColDsptr EndFramec::vOeO() const
{
    return markerFrame->vOmO();
}

FMatDsptr MbD::EndFramec::getprOeOpE() const
{
    return FMatDsptr();
}

FMatFColDsptr MbD::EndFramec::getpprOeOpEpE() const
{
    return FMatFColDsptr();
}

FMatDsptr MbD::EndFramec::pAOepEtimesFullColumn(FColDsptr col) const
{
    return FMatDsptr();
}

FColDsptr EndFramec::aOeO() const
{
    return markerFrame->aOmO();
}

FMatDsptr EndFramec::pAjOepE(size_t j) const
{
    throw SimulationStoppingError("To be implemented.");
    return FMatDsptr();
}

FMatDsptr EndFramec::pAjOepET(size_t axis)
{
    auto answer = FullMatrix<double>::With(4, 3);
    for (size_t i = 0; i < 4; i++) {
        auto answeri = answer->at(i);
        auto pAOepEi = pAOepE()->at(i);
        for (size_t j = 0; j < 3; j++) {
            auto answerij = pAOepEi->at(j)->at(axis);
            answeri->at(j) = answerij;
        }
    }
    return answer;
}

FColFMatDsptr EndFramec::pAOepE() const
{
    //rOeO = rOmO + aAOm*rmem
    //aAOe = aAOm*aAme;
    auto pAOepE = std::make_shared<FullColumn<FMatDsptr>>(4);
    auto mrkFrmc = static_cast<MarkerFramec*>(markerFrame);
    for (size_t i = 0; i < 4; i++) {
        auto prOmOpEi = mrkFrmc->prOmOpE()->column(i);
        auto pAOmpEi = mrkFrmc->pAOmpE()->at(i);    //Make a copy
        pAOepE->atiput(i, pAOmpEi->timesFullMatrix(aAme));
    }
    return pAOepE;
}

FColDsptr EndFramec::omeOeO()
{
    return static_cast<MarkerFramec*>(markerFrame)->omeOmO();
}
