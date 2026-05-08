/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include "EndFrameq.h"
#include "EulerParameters.h"

#include <memory>

#include "EndFrameq.h"
#include "EndFrameqt.h"
#include "Variable.h"
#include "MarkerFrameq.h"
#include "EndFrameqt2.h"
#include "EndFrameqccq.h"
#include "EndFrameccq.h"

using namespace MbD;

std::shared_ptr<EndFrameq> EndFrameq::With()
{
    auto inst = std::make_shared<EndFrameq>();
    inst->initialize();
    return inst;
}

std::shared_ptr<EndFrameq> EndFrameq::With(const std::string &str)
{
    auto inst = std::make_shared<EndFrameq>(str);
    inst->initialize();
    return inst;
}

void EndFrameq::initialize()
{
    prOeOpE = FullMatrix<double>::With(3, 4);
    pprOeOpEpE = std::make_shared<FullMatrix<FColDsptr>>(4, 4);
    pAOepE = std::make_shared<FullColumn<FMatDsptr>>(4);
    ppAOepEpE = std::make_shared<FullMatrix<FMatDsptr>>(4, 4);
}

void EndFrameq::initializeGlobally()
{
    // rOeO = rOmO + aAOm*rmem
    // aAOe = aAOm*aAme;
    auto mkrFrmqc = static_cast<MarkerFrameq *>(markerFrame);
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            auto pprOmOpEipEj = mkrFrmqc->pprOmOpEpE->at(i)->at(j);
            auto ppAOmpEipEj = mkrFrmqc->ppAOmpEpE->at(i)->at(j);
            pprOeOpEpE->atijput(i, j, pprOmOpEipEj->plusFullColumn(ppAOmpEipEj->timesFullColumn(rmem)));
            ppAOepEpE->atijput(i, j, ppAOmpEipEj->timesFullMatrix(aAme));
        }
    }
}

void EndFrameq::initEndFrameqt()
{
    endFrameqt = EndFrameqt::With(name.data());
    endFrameqt->prOeOpE = prOeOpE;
    endFrameqt->pprOeOpEpE = pprOeOpEpE;
    endFrameqt->pAOepE = pAOepE;
    endFrameqt->ppAOepEpE = ppAOepEpE;
    endFrameqt->setMarkerFrame(markerFrame);
}

void EndFrameq::initEndFrameqt2()
{
    endFrameqt = EndFrameqt2::With(name.data());
    endFrameqt->prOeOpE = prOeOpE;
    endFrameqt->pprOeOpEpE = pprOeOpEpE;
    endFrameqt->pAOepE = pAOepE;
    endFrameqt->ppAOepEpE = ppAOepEpE;
    endFrameqt->setMarkerFrame(markerFrame);
}

FMatFColDsptr EndFrameq::ppAjOepEpE(size_t jj) const
{
    auto answer = std::make_shared<FullMatrix<FColDsptr>>(4, 4);
    for (size_t i = 0; i < 4; i++)
    {
        auto answeri = answer->at(i);
        auto ppAOepEipE = ppAOepEpE->at(i);
        for (size_t j = i; j < 4; j++)
        {
            answeri->at(j) = ppAOepEipE->at(j)->column(jj);
        }
    }
    answer->symLowerWithUpper();
    return answer;
}

void EndFrameq::simUpdateAll()
{
    // rOeO = rOmO + aAOm*rmem
    // aAOe = aAOm*aAme;
    EndFrame::simUpdateAll();
    auto mkrFrmqc = static_cast<MarkerFrameq *>(markerFrame);
    for (size_t i = 0; i < 4; i++)
    {
        auto prOmOpEi = mkrFrmqc->prOmOpE->column(i);
        auto pAOmpEi = mkrFrmqc->pAOmpE->at(i);
        prOeOpE->atijputFullColumn(0, i, prOmOpEi->plusFullColumn(pAOmpEi->timesFullColumn(rmem)));
        pAOepE->atiput(i, pAOmpEi->timesFullMatrix(aAme));
    }
}

FMatDsptr EndFrameq::pAjOepE(size_t jj) const
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

FMatDsptr EndFrameq::pAjOepET(size_t axis) const
{
    auto answer = FullMatrix<double>::With(4, 3);
    for (size_t i = 0; i < 4; i++)
    {
        auto answeri = answer->at(i);
        auto pAOepEi = pAOepE->at(i);
        for (size_t j = 0; j < 3; j++)
        {
            auto answerij = pAOepEi->at(j)->at(axis);
            answeri->at(j) = answerij;
        }
    }
    return answer;
}

FMatDsptr EndFrameq::ppriOeOpEpE(size_t ii) const
{
    auto answer = FullMatrix<double>::With(4, 4);
    for (size_t i = 0; i < 4; i++)
    {
        auto answeri = answer->at(i);
        auto pprOeOpEipE = pprOeOpEpE->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto answerij = pprOeOpEipE->at(j)->at(ii);
            answeri->at(j) = answerij;
        }
    }
    return answer;
}

size_t EndFrameq::iqX() const
{
    return static_cast<MarkerFrameq *>(markerFrame)->iqX();
}

size_t EndFrameq::iqE() const
{
    return static_cast<MarkerFrameq *>(markerFrame)->iqE();
}

FRowDsptr EndFrameq::priOeOpE(size_t i) const
{
    return prOeOpE->at(i);
}

FColDsptr EndFrameq::qXdot()
{
    return static_cast<MarkerFrameq *>(markerFrame)->qXdot();
}

std::shared_ptr<EulerParametersDot<double>> EndFrameq::qEdot()
{
    return static_cast<MarkerFrameq *>(markerFrame)->qEdot();
}

FColDsptr EndFrameq::qXddot()
{
    return static_cast<MarkerFrameq *>(markerFrame)->qXddot();
}

FColDsptr EndFrameq::qEddot()
{
    return static_cast<MarkerFrameq *>(markerFrame)->qEddot();
}

FColDsptr EndFrameq::rpep()
{
    auto mkrFrmqc = static_cast<MarkerFrameq *>(markerFrame);
    auto rpmp = mkrFrmqc->rpmp;
    auto aApm = mkrFrmqc->aApm;
    auto rpep = rpmp->plusFullColumn(aApm->timesFullColumn(rmem));
    return rpep;
}

FColFMatDsptr EndFrameq::pAOppE()
{
    return static_cast<MarkerFrameq *>(markerFrame)->pAOppE();
}

FMatDsptr EndFrameq::aBOp() const
{
    return static_cast<MarkerFrameq *>(markerFrame)->aBOp();
}

bool EndFrameq::isEndFrameq()
{
    return true;
}

FMatDsptr EndFrameq::pvOeOpE()
{
    return static_cast<MarkerFrameq *>(markerFrame)->pvOmOpE();
}

FColDsptr EndFrameq::omeOeO()
{
    return static_cast<MarkerFrameq *>(markerFrame)->omeOmO();
}

FMatDsptr EndFrameq::pomeOeOpE()
{
    return static_cast<MarkerFrameq *>(markerFrame)->pomeOmOpE();
}

FMatDsptr EndFrameq::pomeOeOpEdot()
{
    return static_cast<MarkerFrameq *>(markerFrame)->pomeOmOpEdot();
}

std::shared_ptr<EndFrame> EndFrameq::followEndFrame(EndFrmsptr frmi)
{
    std::shared_ptr<EndFrame> endFrm;
    if (std::dynamic_pointer_cast<EndFrameq>(frmi))
    {

        endFrm = EndFrameqccq::With();
    }
    else if (std::dynamic_pointer_cast<EndFrame>(frmi))
    {
        endFrm = EndFrameccq::With();
    }
    endFrm->name = name;
    markerFrame->addEndFrame(endFrm);
    endFrm->setTargetFrame(frmi);
    return endFrm;
}

bool EndFrameq::has_qX() const
{
    return true;
}

FMatDsptr EndFrameq::getprOeOpE() const
{
    return prOeOpE;
}

FMatFColDsptr EndFrameq::getpprOeOpEpE() const
{
    return pprOeOpEpE;
}

FMatDsptr EndFrameq::pAOepEtimesFullColumn(FColDsptr col) const
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

FMatDsptr EndFrameq::pAOeTpEtimesFullColumn(FColDsptr col) const
{
    auto answer = FullMatrix<double>::With(3, 4);
    for (size_t j = 0; j < 4; j++)
    {
        auto pAOepEj = pAOepE->at(j);
        auto answerCol = pAOepEj->transposeTimesFullColumn(col);
        answer->atijputFullColumn(0, j, answerCol);
    }
    return answer;
}

FMatFColDsptr EndFrameq::ppAOeTpEpEtimesFullColumn(FColDsptr col) const
{
    // pprIeJeKepEKpEK = ppAOKeTpEKpEK * rIeJeO
    auto answer = FullMatrix<FColDsptr>::With(4, 4);
    for (size_t i = 0; i < 4; i++)
    {
        auto ppAOepEipE = ppAOepEpE->at(i);
        auto rowi = answer->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto ppAOepEipEj = ppAOepEipE->at(j);
            auto answerCol = ppAOepEipEj->transposeTimesFullColumn(col);
            rowi->atiput(j, answerCol);
        }
    }
    return answer;
}

FMatFColDsptr EndFrameq::pAOeTpEtimesFullMatrix(FMatDsptr prIeJeOpq) const
{
    // pprIeJeKepXIpEK = pAOKeTpEK * prIeJeOpXI
    // pprIeJeKepEIpEK = pAOKeTpEK * prIeJeOpEI
    // pprIeJeKepXJpEK = pAOKeTpEK * prIeJeOpXJ
    // pprIeJeKepEJpEK = pAOKeTpEK * prIeJeOpEJ
    auto pAOKepEK = getpAOepE();
    auto m = prIeJeOpq->ncol();
    auto pprIeJeKepqpEK = FullMatrix<FColDsptr>::With(m, 4);
    for (size_t i = 0; i < m; i++)
    {
        auto coli = prIeJeOpq->column(i);
        auto rowi = pprIeJeKepqpEK->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto pAOKepEKj = pAOKepEK->at(j);
            auto answerCol = pAOKepEKj->transposeTimesFullColumn(coli);
            rowi->atiput(j, answerCol);
        }
    }
    return pprIeJeKepqpEK;
}
