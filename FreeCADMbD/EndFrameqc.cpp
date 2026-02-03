/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include "EndFrameqc.h"
#include "EulerParameters.h"

#include <memory>

#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "Variable.h"
#include "MarkerFrameqc.h"
#include "EndFrameqct2.h"
#include "EndFrameqccq.h"
#include "EndFrameccq.h"

using namespace MbD;

std::shared_ptr<EndFrameqc> EndFrameqc::With()
{
    auto inst = std::make_shared<EndFrameqc>();
    inst->initialize();
    return inst;
}

std::shared_ptr<EndFrameqc> EndFrameqc::With(const std::string& str)
{
    auto inst = std::make_shared<EndFrameqc>(str);
    inst->initialize();
    return inst;
}

void EndFrameqc::initialize()
{
    prOeOpE = FullMatrix<double>::With(3, 4);
    pprOeOpEpE = std::make_shared<FullMatrix<FColDsptr>>(4, 4);
    pAOepE = std::make_shared<FullColumn<FMatDsptr>>(4);
    ppAOepEpE = std::make_shared<FullMatrix<FMatDsptr>>(4, 4);
}

void EndFrameqc::initializeGlobally()
{
    //rOeO = rOmO + aAOm*rmem
    //aAOe = aAOm*aAme;
    auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            auto pprOmOpEipEj = mkrFrmqc->pprOmOpEpE->at(i)->at(j);
            auto ppAOmpEipEj = mkrFrmqc->ppAOmpEpE->at(i)->at(j);
            pprOeOpEpE->atijput(i, j, pprOmOpEipEj->plusFullColumn(ppAOmpEipEj->timesFullColumn(rmem)));
            ppAOepEpE->atijput(i, j, ppAOmpEipEj->timesFullMatrix(aAme));
        }
    }
}

void EndFrameqc::initEndFrameqct()
{
    endFrameqct = EndFrameqct::With(name.data());
    endFrameqct->prOeOpE = prOeOpE;
    endFrameqct->pprOeOpEpE = pprOeOpEpE;
    endFrameqct->pAOepE = pAOepE;
    endFrameqct->ppAOepEpE = ppAOepEpE;
    endFrameqct->setMarkerFrame(markerFrame);
}

void EndFrameqc::initEndFrameqct2()
{
    endFrameqct = EndFrameqct2::With(name.data());
    endFrameqct->prOeOpE = prOeOpE;
    endFrameqct->pprOeOpEpE = pprOeOpEpE;
    endFrameqct->pAOepE = pAOepE;
    endFrameqct->ppAOepEpE = ppAOepEpE;
    endFrameqct->setMarkerFrame(markerFrame);
}

FMatFColDsptr EndFrameqc::ppAjOepEpE(size_t jj) const
{
    auto answer = std::make_shared<FullMatrix<FColDsptr>>(4, 4);
    for (size_t i = 0; i < 4; i++) {
        auto answeri = answer->at(i);
        auto ppAOepEipE = ppAOepEpE->at(i);
        for (size_t j = i; j < 4; j++) {
            answeri->at(j) = ppAOepEipE->at(j)->column(jj);
        }
    }
    answer->symLowerWithUpper();
    return answer;
}

void EndFrameqc::simUpdateAll()
{
    //rOeO = rOmO + aAOm*rmem
    //aAOe = aAOm*aAme;
    EndFramec::simUpdateAll();
    auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
    for (size_t i = 0; i < 4; i++) {
        auto prOmOpEi = mkrFrmqc->prOmOpE->column(i);
        auto pAOmpEi = mkrFrmqc->pAOmpE->at(i);
        prOeOpE->atijputFullColumn(0, i, prOmOpEi->plusFullColumn(pAOmpEi->timesFullColumn(rmem)));
        pAOepE->atiput(i, pAOmpEi->timesFullMatrix(aAme));
    }
}

FMatDsptr EndFrameqc::pAjOepE(size_t jj) const
{
    auto answer = FullMatrix<double>::With(3, 4);
    for (size_t i = 0; i < 3; i++)
    {
        auto answeri = answer->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto pAOepEj = pAOepE->at(j);
            auto answerij = pAOepEj->at(i)->at(jj);
            answeri->atiput(j, answerij);
        }
    }
    return answer;
}

FMatDsptr EndFrameqc::pAjOepET(size_t axis) const
{
    auto answer = FullMatrix<double>::With(4, 3);
    for (size_t i = 0; i < 4; i++) {
        auto answeri = answer->at(i);
        auto pAOepEi = pAOepE->at(i);
        for (size_t j = 0; j < 3; j++) {
            auto answerij = pAOepEi->at(j)->at(axis);
            answeri->at(j) = answerij;
        }
    }
    return answer;
}

FMatDsptr EndFrameqc::ppriOeOpEpE(size_t ii) const
{
    auto answer = FullMatrix<double>::With(4, 4);
    for (size_t i = 0; i < 4; i++) {
        auto answeri = answer->at(i);
        auto pprOeOpEipE = pprOeOpEpE->at(i);
        for (size_t j = 0; j < 4; j++) {
            auto answerij = pprOeOpEipE->at(j)->at(ii);
            answeri->at(j) = answerij;
        }
    }
    return answer;
}

size_t EndFrameqc::iqX() const
{
    return static_cast<MarkerFrameqc*>(markerFrame)->iqX();
}

size_t EndFrameqc::iqE() const
{
    return static_cast<MarkerFrameqc*>(markerFrame)->iqE();
}

FRowDsptr EndFrameqc::priOeOpE(size_t i) const
{
    return prOeOpE->at(i);
}

FColDsptr EndFrameqc::qXdot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->qXdot();
}

std::shared_ptr<EulerParametersDot<double>> EndFrameqc::qEdot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->qEdot();
}

FColDsptr EndFrameqc::qXddot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->qXddot();
}

FColDsptr EndFrameqc::qEddot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->qEddot();
}

FColDsptr EndFrameqc::rpep()
{
    auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
    auto rpmp = mkrFrmqc->rpmp;
    auto aApm = mkrFrmqc->aApm;
    auto rpep = rpmp->plusFullColumn(aApm->timesFullColumn(rmem));
    return rpep;
}

FColFMatDsptr EndFrameqc::pAOppE()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->pAOppE();
}

FMatDsptr EndFrameqc::aBOp() const
{
    return static_cast<MarkerFrameqc*>(markerFrame)->aBOp();
}

bool EndFrameqc::isEndFrameqc()
{
    return true;
}

FMatDsptr EndFrameqc::pvOeOpE()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->pvOmOpE();
}

FColDsptr EndFrameqc::omeOeO()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->omeOmO();
}

FMatDsptr EndFrameqc::pomeOeOpE()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->pomeOmOpE();
}

FMatDsptr EndFrameqc::pomeOeOpEdot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->pomeOmOpEdot();
}

std::shared_ptr<EndFramec> EndFrameqc::followEndFrame(EndFrmsptr frmi)
{
    std::shared_ptr<EndFramec> endFrm;
    if (std::dynamic_pointer_cast<EndFrameqc>(frmi)) {

        endFrm = EndFrameqccq::With();
    }
    else if (std::dynamic_pointer_cast<EndFramec>(frmi)) {
        endFrm = EndFrameccq::With();
    }
    endFrm->name = name;
    markerFrame->addEndFrame(endFrm);
    endFrm->setTargetFrame(frmi);
    return endFrm;
}

bool EndFrameqc::has_qX() const
{
    return true;
}

FMatDsptr MbD::EndFrameqc::getprOeOpE() const
{
    return prOeOpE;
}

FMatFColDsptr MbD::EndFrameqc::getpprOeOpEpE() const
{
    return pprOeOpEpE;
}

MbD::FMatDsptr MbD::EndFrameqc::pAOepEtimesFullColumn(FColDsptr col) const
{
    auto answer = FullMatrix<double>::With(3, 4);
    for (size_t j = 0; j < 4; j++)
    {
        auto pAOepEj = pAOepE->at(j);
        auto answerCol = pAOepEj->timesFullColumn(col);
        answer->atijputFullColumn(0, j, answerCol);
    }
    return answer;
}

