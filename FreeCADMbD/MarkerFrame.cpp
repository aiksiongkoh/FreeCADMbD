/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "PartFrame.h"
#include "MarkerFrame.h"
 //#include "EndFramec.h"
#include "EndFrameqct.h"
#include "EulerParameters.h"
#include "SimulationStoppingError.h"

using namespace MbD;

MarkerFrame::MarkerFrame(const std::string& str) : CartesianFrame(str)
{
    //Do nothing.
}

std::shared_ptr<MarkerFrame> MarkerFrame::With(const std::string& str)
{
    auto inst = std::make_shared<MarkerFrame>(str);
    inst->initialize();
    return inst;
}

void MarkerFrame::initialize()
{
    prOmOpE = FullMatrix<double>::With(3, 4);
    pAOmpE = std::make_shared<FullColumn<FMatDsptr>>(4);
    endFrames = std::make_shared<std::vector<EndFrmsptr>>();
    auto endFrm = EndFrameqc::With();
    addEndFrame(endFrm);
}

System* MarkerFrame::root()
{
    return partFrame->root();
}

void MarkerFrame::initializeLocally()
{
    pprOmOpEpE = EulerParameters<double>::ppApEpEtimesColumn(rpmp);
    ppAOmpEpE = EulerParameters<double>::ppApEpEtimesMatrix(aApm);
    for (size_t i = 0; i < endFrames->size(); i++)
    {
        auto eFrmqc = std::dynamic_pointer_cast<EndFrameqc>(endFrames->at(i));
        if (eFrmqc) {
            if (eFrmqc->endFrameqct) {
                endFrames->at(i) = eFrmqc->endFrameqct;
            }
        }
    }
    endFramesDo([](EndFrmsptr endFrame) { endFrame->initializeLocally(); });
}
/// <summary>
/// 
/// </summary>
void MarkerFrame::initializeGlobally()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->initializeGlobally(); });
}

void MarkerFrame::postInput()
{
    CartesianFrame::postInput();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postInput(); });
}

void MarkerFrame::calcPostDynCorrectorIteration()
{
    auto rOpO = partFrame->rOpO();
    auto aAOp = partFrame->aAOp();
    rOmO = rOpO->plusFullColumn(aAOp->timesFullColumn(rpmp));
    aAOm = aAOp->timesFullMatrix(aApm);
    auto pAOppE = partFrame->pAOppE();
    for (size_t i = 0; i < 4; i++)
    {
        auto& pAOppEi = pAOppE->at(i);
        prOmOpE->atijputFullColumn(0, i, pAOppEi->timesFullColumn(rpmp));
        pAOmpE->at(i) = pAOppEi->timesFullMatrix(aApm);
    }
}

void MarkerFrame::prePosIC()
{
    CartesianFrame::prePosIC();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->prePosIC(); });
}

void MarkerFrame::preStatic()
{
    throw SimulationStoppingError("To be implemented.");
}

size_t MarkerFrame::iqX() const
{
    return partFrame->iqX;
}

FColDsptr MarkerFrame::omeOmO() const
{
    return partFrame->omeOpO();
}

FMatDsptr MarkerFrame::pAdotjOmpE(size_t jj)
{
    auto pAdotOppE = partFrame->pAdotOppE();
    auto aAjjpm = aApm->column(jj);
    auto answer = FullMatrix<double>::With(3, 4);
    for (size_t j = 0; j < 4; j++) {
        auto pAdotOppEj = pAdotOppE->at(j);
        auto pAdotjjpmpEj = pAdotOppEj->timesFullColumn(aAjjpm);
        answer->atijputFullColumn(0, j, pAdotjjpmpEj);
    }
    return answer;
}

FMatDsptr MarkerFrame::pAdotjOmpET(size_t jj)
{
    auto pAdotOppE = partFrame->pAdotOppE();
    auto aAjjpm = aApm->column(jj);
    auto answer = FullMatrix<double>::With(4, 3);
    for (size_t i = 0; i < 4; i++) {
        auto answeri = answer->at(i);
        auto pAdotOppEi = pAdotOppE->at(i);
        auto pAdotjjpmpEi = pAdotOppEi->timesFullColumn(aAjjpm);
        for (size_t j = 0; j < 3; j++) {
            answeri->atiput(j, (pAdotjjpmpEi->at(j)));
        }
    }
    return answer;
}

size_t MarkerFrame::iqE() const
{
    return partFrame->iqE;
}

void MarkerFrame::endFramesDo(const std::function<void(EndFrmsptr)>& f) const
{
    std::for_each(endFrames->begin(), endFrames->end(), f);
}

void MarkerFrame::fillqsu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsu(col); });
}

void MarkerFrame::fillqsuWeights(DiagMatDsptr diagMat)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuWeights(diagMat); });
}

void MarkerFrame::fillqsuddotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuddotlam(col); });
}

void MarkerFrame::fillqsulam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsulam(col); });
}

void MarkerFrame::fillpqsumu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumu(col); });
}

void MarkerFrame::fillpqsumudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumudot(col); });
}

void MarkerFrame::fillqsudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudot(col); });
}

void MarkerFrame::fillqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrame::fillqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrame::fillqsudotWeights(DiagMatDsptr diagMat)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudotWeights(diagMat); });
}

void MarkerFrame::setqsu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsu(col); });
}

void MarkerFrame::setqsulam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsulam(col); });
}

void MarkerFrame::simUpdateAll()
{
    CartesianFrame::simUpdateAll();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->simUpdateAll(); });
}

void MarkerFrame::setqsudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudot(col); });
}

void MarkerFrame::setqsudotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudotlam(col); });
}

void MarkerFrame::setqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrame::setqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrame::postPosICIteration()
{
    CartesianFrame::postPosICIteration();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosICIteration(); });
}

void MarkerFrame::postStaticIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrame::postPosIC()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosIC(); });
}

void MarkerFrame::preDyn()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->preDyn(); });
}

void MarkerFrame::storeDynState()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->storeDynState(); });
}

void MarkerFrame::preVelIC()
{
    CartesianFrame::preVelIC();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->preVelIC(); });
}

void MarkerFrame::postVelIC()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postVelIC(); });
}

void MarkerFrame::preAccIC()
{
    CartesianFrame::preAccIC();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->preAccIC(); });
}

void MarkerFrame::preDynOutput()
{
    CartesianFrame::preDynOutput();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->preDynOutput(); });
}

FColDsptr MarkerFrame::qXdot() const
{
    return partFrame->qXdot;
}

FColDsptr MarkerFrame::rmemOFrOeO(FColDsptr rOeOCol) const
{
    return aAOm->transposeTimesFullColumn(rOeOCol->minusFullColumn(rOmO));
}

FColDsptr MarkerFrame::rOeOOFrmem(FColDsptr rmemCol) const
{
    return rOmO->plusFullColumn(aAOm->timesFullColumn(rmemCol));
}

std::shared_ptr<EulerParametersDot<double>> MarkerFrame::qEdot() const
{
    return partFrame->qEdot;
}

FColDsptr MarkerFrame::qX() const
{
    return partFrame->qX;
}

FColDsptr MarkerFrame::qXddot() const
{
    return partFrame->qXddot;
}

FColDsptr MarkerFrame::qEddot() const
{
    return partFrame->qEddot;
}

void MarkerFrame::setqsuddotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsuddotlam(col); });
}

FColFMatDsptr MarkerFrame::pAOppE()
{
    return partFrame->pAOppE();
}

FMatDsptr MarkerFrame::aBOp()
{
    return partFrame->aBOp();
}

void MarkerFrame::postDynStep()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynStep(); });
}

void MarkerFrame::setpqsumu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumu(col); });
}

void MarkerFrame::setpqsumudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumudot(col); });
}

void MarkerFrame::setpqsumuddot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumuddot(col); });
}

void MarkerFrame::postDynPredictor()
{
    CartesianFrame::postDynPredictor();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynPredictor(); });
}

void MarkerFrame::postDynOutput()
{
    CartesianFrame::postDynOutput();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynOutput(); });
}

void MarkerFrame::postDynCorrectorIteration()
{
    CartesianFrame::postDynCorrectorIteration();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynCorrectorIteration(); });
}

FMatDsptr MarkerFrame::pvOmOpE()
{
    auto answer = FullMatrix<double>::With(3, 4);
    auto pAdotOppE = partFrame->pAdotOppE();
    for (size_t i = 0; i < 3; i++) {
        auto answeri = answer->at(i);
        for (size_t j = 0; j < 4; j++) {
            auto pAdotOpipEj = pAdotOppE->at(j)->at(i);
            answeri->atiput(j, pAdotOpipEj->dot(rpmp));
        }
    }
    return answer;
}

FColDsptr MarkerFrame::vOmO() const
{
    return partFrame->vOpO()->plusFullColumn(partFrame->aAdotOp()->timesFullColumn(rpmp));
}

FColDsptr MarkerFrame::vOeO_of_rmem() const
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

FColDsptr MarkerFrame::aOmO() const
{
    return partFrame->aOpO()->plusFullColumn(partFrame->aAddotOp()->timesFullColumn(rpmp));
}

void MarkerFrame::setPartFrame(PartFrame* partFrm)
{
    partFrame = partFrm;
}

FMatDsptr MarkerFrame::pomeOmOpE()
{
    return partFrame->pomeOpOpE();
}

FMatDsptr MarkerFrame::pomeOmOpEdot()
{
    return partFrame->pomeOpOpEdot();
}

PartFrame* MarkerFrame::getPartFrame() const {
    return partFrame;
}

void MarkerFrame::setrpmp(FColDsptr x) const
{
    rpmp->copyFrom(x);
}

FColDsptr MarkerFrame::aAdotjOm(size_t j)
{
    return partFrame->aAdotOp()->timesFullColumn(aApm->column(j));
}

void MarkerFrame::setaApm(FMatDsptr mat) const
{
    aApm->copyFrom(mat);
}

void MarkerFrame::addEndFrame(EndFrmsptr endFrm)
{
    endFrm->setMarkerFrame(this);
    endFrames->push_back(endFrm);
}
