/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "EndFrameccq.h"
#include "EndFrameqct.h"
#include "Variable.h"
#include "MarkerFrameqc.h"
#include "EndFrameqct2.h"
#include "EndFrameqccq.h"

using namespace MbD;

std::shared_ptr<EndFrameccq> EndFrameccq::With()
{
    auto inst = std::make_shared<EndFrameccq>();
    inst->initialize();
    return inst;
}

std::shared_ptr<EndFrameccq> EndFrameccq::With(const std::string& str)
{
    auto inst = std::make_shared<EndFrameccq>(str);
    inst->initialize();
    return inst;
}

void EndFrameccq::initialize()
{
    prOeOpE = FullMatrix<double>::With(3, 4);
    pprOeOpEpE = std::make_shared<FullMatrix<FColDsptr>>(4, 4);
    pAOepE = std::make_shared<FullColumn<FMatDsptr>>(4);
    ppAOepEpE = std::make_shared<FullMatrix<FMatDsptr>>(4, 4);
}

void EndFrameccq::initializeGlobally()
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

void EndFrameccq::initEndFrameqct()
{
    endFrameqct = EndFrameqct::With(name.data());
    endFrameqct->prOeOpE = prOeOpE;
    endFrameqct->pprOeOpEpE = pprOeOpEpE;
    endFrameqct->pAOepE = pAOepE;
    endFrameqct->ppAOepEpE = ppAOepEpE;
    endFrameqct->setMarkerFrame(markerFrame);
}

void EndFrameccq::initEndFrameqct2()
{
    endFrameqct = EndFrameqct2::With(name.data());
    endFrameqct->prOeOpE = prOeOpE;
    endFrameqct->pprOeOpEpE = pprOeOpEpE;
    endFrameqct->pAOepE = pAOepE;
    endFrameqct->ppAOepEpE = ppAOepEpE;
    endFrameqct->setMarkerFrame(markerFrame);
}

FMatFColDsptr EndFrameccq::ppAjOepEpE(size_t jj) const
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

void EndFrameccq::simUpdateAll()
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

FMatDsptr EndFrameccq::pAjOepE(size_t jj) const
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

FMatDsptr EndFrameccq::pAjOepET(size_t axis) const
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

FMatDsptr EndFrameccq::ppriOeOpEpE(size_t ii) const
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

size_t EndFrameccq::iqX() const
{
    return static_cast<MarkerFrameqc*>(markerFrame)->iqX();
}

size_t EndFrameccq::iqE() const
{
    return static_cast<MarkerFrameqc*>(markerFrame)->iqE();
}

FRowDsptr EndFrameccq::priOeOpE(size_t i) const
{
    return prOeOpE->at(i);
}

FColDsptr EndFrameccq::qXdot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->qXdot();
}

std::shared_ptr<EulerParametersDot<double>> EndFrameccq::qEdot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->qEdot();
}

FColDsptr EndFrameccq::qXddot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->qXddot();
}

FColDsptr EndFrameccq::qEddot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->qEddot();
}

FColDsptr EndFrameccq::rpep()
{
    auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
    auto rpmp = mkrFrmqc->rpmp;
    auto aApm = mkrFrmqc->aApm;
    auto rpep = rpmp->plusFullColumn(aApm->timesFullColumn(rmem));
    return rpep;
}

FColFMatDsptr EndFrameccq::pAOppE()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->pAOppE();
}

FMatDsptr EndFrameccq::aBOp() const
{
    return static_cast<MarkerFrameqc*>(markerFrame)->aBOp();
}

bool EndFrameccq::isEndFrameqc()
{
    return true;
}

FMatDsptr EndFrameccq::pvOeOpE()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->pvOmOpE();
}

FColDsptr EndFrameccq::omeOeO()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->omeOmO();
}

FMatDsptr EndFrameccq::pomeOeOpE()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->pomeOmOpE();
}

FMatDsptr EndFrameccq::pomeOeOpEdot()
{
    return static_cast<MarkerFrameqc*>(markerFrame)->pomeOmOpEdot();
}

std::shared_ptr<EndFramec> EndFrameccq::followEndFrame(EndFrmsptr frmi)
{
    auto endFrm = EndFrameqccq::With();
    endFrm->name = name;
    markerFrame->addEndFrame(endFrm);
    endFrm->targetFrame = frmi;
    return endFrm;
}

bool EndFrameccq::has_qX() const
{
    return true;
}

void EndFrameccq::setTargetFrame(std::shared_ptr<EndFramec> targetFrm)
{
    targetFrame = targetFrm;
}

