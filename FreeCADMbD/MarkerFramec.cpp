/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "MarkerFramec.h"
#include "SpatialContainerFrame.h"
#include "PartFrame.h"
#include "AssemblyFrame.h"
 //#include "EndFramec.h"
#include "EndFramect.h"
#include "EulerParameters.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MarkerFramec> MarkerFramec::With(const std::string& str)
{
    auto inst = std::make_shared<MarkerFramec>(str);
    inst->initialize();
    return inst;
}

void MarkerFramec::initialize()
{
    endFrames = std::make_shared<std::vector<EndFrmsptr>>();
    auto endFrm = EndFramec::With();
    addEndFrame(endFrm);
}

System* MarkerFramec::root()
{
    return partFrame->root();
}

void MarkerFramec::initializeLocally()
{
    for (size_t i = 0; i < endFrames->size(); i++)
    {
        auto eFrmc = std::dynamic_pointer_cast<EndFramec>(endFrames->at(i));
        if (eFrmc) {
            if (eFrmc->endFramect) {
                endFrames->at(i) = eFrmc->endFramect;
            }
        }
    }
    endFramesDo([](EndFrmsptr endFrame) { endFrame->initializeLocally(); });
}

void MarkerFramec::initializeGlobally()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->initializeGlobally(); });
}

void MarkerFramec::postInput()
{
    CartesianFrame::postInput();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postInput(); });
}

void MarkerFramec::simUpdateAll()
{
    //rOmO = rOpO + aAOp*rpmp
    //aAOm = aAOp*aApm
    rOmO = rpmp;
    aAOm = aApm;
}

void MarkerFramec::prePosIC()
{
    CartesianFrame::prePosIC();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->prePosIC(); });
}

void MarkerFramec::prePosKine()
{
    CartesianFrame::prePosKine();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->prePosKine(); });
}

void MarkerFramec::preStatic()
{
    throw SimulationStoppingError("To be implemented.");
}

size_t MarkerFramec::iqX() const
{
    return partFrame->iqX();
}

FColDsptr MarkerFramec::omeOmO() const
{
    return partFrame->omeOpO();
}

FMatDsptr MarkerFramec::pAdotjOmpE(size_t jj)
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

FMatDsptr MarkerFramec::pAdotjOmpET(size_t jj)
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

size_t MarkerFramec::iqE() const
{
    return partFrame->iqE();
}

void MarkerFramec::endFramesDo(const std::function<void(EndFrmsptr)>& f) const
{
    for (const auto endFrame : *endFrames) f(endFrame);
}

void MarkerFramec::fillqsu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsu(col); });
}

void MarkerFramec::fillqsuWeights(DiagMatDsptr diagMat)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuWeights(diagMat); });
}

void MarkerFramec::fillqsuddotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuddotlam(col); });
}

void MarkerFramec::fillqsulam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsulam(col); });
}

void MarkerFramec::fillpqsumu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumu(col); });
}

void MarkerFramec::fillpqsumudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumudot(col); });
}

void MarkerFramec::fillqsudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudot(col); });
}

void MarkerFramec::fillqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFramec::fillqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFramec::fillqsudotWeights(DiagMatDsptr diagMat)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudotWeights(diagMat); });
}

void MarkerFramec::setqsu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsu(col); });
}

void MarkerFramec::setqsulam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsulam(col); });
}

void MarkerFramec::setqsudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudot(col); });
}

void MarkerFramec::setqsudotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudotlam(col); });
}

void MarkerFramec::setqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFramec::setqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFramec::postPosICIteration()
{
    CartesianFrame::postPosICIteration();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosICIteration(); });
}

void MarkerFramec::postStaticIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFramec::postPosIC()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosIC(); });
}

void MarkerFramec::preDyn()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->preDyn(); });
}

void MarkerFramec::storeDynState()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->storeDynState(); });
}

void MarkerFramec::preVelIC()
{
    CartesianFrame::preVelIC();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->preVelIC(); });
}

void MarkerFramec::postVelIC()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postVelIC(); });
}

void MarkerFramec::preAccIC()
{
    CartesianFrame::preAccIC();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->preAccIC(); });
}

void MarkerFramec::preDynOutput()
{
    CartesianFrame::preDynOutput();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->preDynOutput(); });
}

FColDsptr MarkerFramec::qXdot() const
{
    return partFrame->qXdot();
}

FColDsptr MarkerFramec::rmemOFrOeO(FColDsptr rOeOCol) const
{
    return aAOm->transposeTimesFullColumn(rOeOCol->minusFullColumn(rOmO));
}

FColDsptr MarkerFramec::rOeOOFrmem(FColDsptr rmemCol) const
{
    return rOmO->plusFullColumn(aAOm->timesFullColumn(rmemCol));
}

std::shared_ptr<EulerParametersDot<double>> MarkerFramec::qEdot() const
{
    return partFrame->qEdot();
}

FColDsptr MarkerFramec::qX() const
{
    return partFrame->qX();
}

FColDsptr MarkerFramec::qXddot() const
{
    return partFrame->qXddot();
}

FColDsptr MarkerFramec::qEddot() const
{
    return partFrame->qEddot();
}

void MarkerFramec::setqsuddotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsuddotlam(col); });
}

FColFMatDsptr MarkerFramec::pAOppE()
{
    return partFrame->pAOppE();
}

FMatDsptr MarkerFramec::aBOp() const
{
    return partFrame->aBOp();
}

void MarkerFramec::postDynStep()
{
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynStep(); });
}

void MarkerFramec::setpqsumu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumu(col); });
}

void MarkerFramec::setpqsumudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumudot(col); });
}

void MarkerFramec::setpqsumuddot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumuddot(col); });
}

void MarkerFramec::postDynPredictor()
{
    CartesianFrame::postDynPredictor();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynPredictor(); });
}

void MarkerFramec::postDynOutput()
{
    CartesianFrame::postDynOutput();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynOutput(); });
}

void MarkerFramec::postDynCorrectorIteration()
{
    CartesianFrame::postDynCorrectorIteration();
    endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynCorrectorIteration(); });
}

FMatDsptr MarkerFramec::pvOmOpE()
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

FColDsptr MarkerFramec::vOmO() const
{
    return FullColumn<double>::With(3, 0.0);
}

FColDsptr MarkerFramec::vOeO_of_rmem() const
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

FMatDsptr MarkerFramec::prOmOpE() const
{
    auto prOmOpE = FullMatrix<double>::With(3, 4);
    auto asmFrmPtr = static_cast<AssemblyFrame*>(partFrame);
    auto pAOppE = asmFrmPtr->pAOppE();
    for (size_t i = 0; i < 4; i++)
    {
        auto pAOppEi = pAOppE->at(i);
        prOmOpE->atijputFullColumn(0, i, pAOppEi->timesFullColumn(rpmp));
    }
    return prOmOpE;
}

FColFMatDsptr MarkerFramec::pAOmpE() const
{
    auto pAOmpE = std::make_shared<FullColumn<FMatDsptr>>(4);
    auto asmFrmPtr = static_cast<AssemblyFrame*>(partFrame);
    auto pAOppE = asmFrmPtr->pAOppE();
    for (size_t i = 0; i < 4; i++)
    {
        auto pAOppEi = pAOppE->at(i);
        pAOmpE->at(i) = pAOppEi->timesFullMatrix(aApm);
    }
    return pAOmpE;
}

FColDsptr MarkerFramec::aOmO() const
{
    return partFrame->aOpO()->plusFullColumn(partFrame->aAddotOp()->timesFullColumn(rpmp));
}

void MarkerFramec::setPartFrame(SpatialContainerFrame* partFrm)
{
    partFrame = partFrm;
}

FMatDsptr MarkerFramec::pomeOmOpE()
{
    return partFrame->pomeOpOpE();
}

FMatDsptr MarkerFramec::pomeOmOpEdot()
{
    return partFrame->pomeOpOpEdot();
}

SpatialContainerFrame* MarkerFramec::getPartFrame() const {
    return partFrame;
}

void MarkerFramec::setrpmp(FColDsptr x) const
{
    rpmp->copyFrom(x);
}

FColDsptr MarkerFramec::aAdotjOm(size_t j)
{
    return partFrame->aAdotOp()->timesFullColumn(aApm->column(j));
}

void MarkerFramec::setaApm(FMatDsptr mat) const
{
    aApm->copyFrom(mat);
}

void MarkerFramec::addEndFrame(EndFrmsptr endFrm)
{
    endFrm->setMarkerFrame(this);
    endFrames->push_back(endFrm);
}
