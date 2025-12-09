/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "Variable.h"
#include "MarkerFrame.h"
#include "EndFrameqct2.h"
#include "EndFrameqccq.h"

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
    pprOeOpEpE = markerFrame->pprOmOpEpE;
    ppAOepEpE = markerFrame->ppAOmpEpE;
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

FMatFColDsptr EndFrameqc::ppAjOepEpE(size_t jj)
{
    auto answer = std::make_shared<FullMatrix<FColDsptr>>(4, 4);
    for (size_t i = 0; i < 4; i++) {
        auto& answeri = answer->at(i);
        auto& ppAOepEipE = ppAOepEpE->at(i);
        for (size_t j = i; j < 4; j++) {
            answeri->at(j) = ppAOepEipE->at(j)->column(jj);
        }
    }
    answer->symLowerWithUpper();
    return answer;
}

void EndFrameqc::calcPostDynCorrectorIteration()
{
    EndFramec::calcPostDynCorrectorIteration();
    prOeOpE = markerFrame->prOmOpE;
    pAOepE = markerFrame->pAOmpE;
}

FMatDsptr EndFrameqc::pAjOepE(size_t jj)
{
    auto answer = FullMatrix<double>::With(3, 4);
    for (size_t i = 0; i < 3; i++)
    {
        auto& answeri = answer->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto pAOepEj = pAOepE->at(j);
            auto answerij = pAOepEj->at(i)->at(jj);
            answeri->atiput(j, answerij);
        }
    }
    return answer;
}

FMatDsptr EndFrameqc::pAjOepET(size_t axis)
{
    auto answer = FullMatrix<double>::With(4, 3);
    for (size_t i = 0; i < 4; i++) {
        auto& answeri = answer->at(i);
        auto& pAOepEi = pAOepE->at(i);
        for (size_t j = 0; j < 3; j++) {
            auto& answerij = pAOepEi->at(j)->at(axis);
            answeri->at(j) = answerij;
        }
    }
    return answer;
}

FMatDsptr EndFrameqc::ppriOeOpEpE(size_t ii)
{
    auto answer = FullMatrix<double>::With(4, 4);
    for (size_t i = 0; i < 4; i++) {
        auto& answeri = answer->at(i);
        auto& pprOeOpEipE = pprOeOpEpE->at(i);
        for (size_t j = 0; j < 4; j++) {
            auto& answerij = pprOeOpEipE->at(j)->at(ii);
            answeri->at(j) = answerij;
        }
    }
    return answer;
}

size_t EndFrameqc::iqX()
{
    return markerFrame->iqX();
}

size_t EndFrameqc::iqE()
{
    return markerFrame->iqE();
}

FRowDsptr EndFrameqc::priOeOpE(size_t i)
{
    return prOeOpE->at(i);
}

FColDsptr EndFrameqc::qXdot()
{
    return markerFrame->qXdot();
}

std::shared_ptr<EulerParametersDot<double>> EndFrameqc::qEdot()
{
    return markerFrame->qEdot();
}

FColDsptr EndFrameqc::qXddot()
{
    return markerFrame->qXddot();
}

FColDsptr EndFrameqc::qEddot()
{
    return markerFrame->qEddot();
}

FColDsptr EndFrameqc::rpep()
{
    return markerFrame->rpmp;
}

FColFMatDsptr EndFrameqc::pAOppE()
{
    return markerFrame->pAOppE();
}

FMatDsptr EndFrameqc::aBOp()
{
    return markerFrame->aBOp();
}

bool EndFrameqc::isEndFrameqc()
{
    return true;
}

FMatDsptr EndFrameqc::pvOeOpE()
{
    return markerFrame->pvOmOpE();
}

FColDsptr EndFrameqc::omeOeO()
{
    return markerFrame->omeOmO();
}

FMatDsptr EndFrameqc::pomeOeOpE()
{
    return markerFrame->pomeOmOpE();
}

FMatDsptr EndFrameqc::pomeOeOpEdot()
{
    return markerFrame->pomeOmOpEdot();
}

std::shared_ptr<EndFrameqc> EndFrameqc::followEndFrame(EndFrmsptr frmi)
{
    auto endFrm = EndFrameqccq::With();
    endFrm->name = name;
    markerFrame->addEndFrame(endFrm);
    endFrm->targetFrame = frmi;
    return endFrm;
}
