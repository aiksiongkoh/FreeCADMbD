/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "MarkerFrameq.h"
#include "MarkerFrame.h"
#include "PartFrame.h"
 //#include "EndFrame.h"
#include "EndFrameqt.h"
#include "EulerParameters.h"

using namespace MbD;

std::shared_ptr<MarkerFrameq> MarkerFrameq::With(const std::string& str)
{
    auto inst = std::make_shared<MarkerFrameq>(str);
    inst->initialize();
    return inst;
}

void MarkerFrameq::initialize()
{
    endFrames = std::make_shared<std::vector<EndFrmsptr>>();
    auto endFrm = EndFrameq::With();
    addEndFrame(endFrm);
    prOmOpE = FullMatrix<double>::With(3, 4);
    pAOmpE = std::make_shared<FullColumn<FMatDsptr>>(4);
}

System* MarkerFrameq::root()
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->root();
}

void MarkerFrameq::initializeLocally()
{
    pprOmOpEpE = EulerParameters<double>::ppApEpEtimesColumn(rpmp);
    ppAOmpEpE = EulerParameters<double>::ppApEpEtimesMatrix(aApm);
    for (size_t i = 0; i < endFrames->size(); i++)
    {
        auto eFrmqc = std::dynamic_pointer_cast<EndFrameq>(endFrames->at(i));
        if (eFrmqc) {
            if (eFrmqc->endFrameqt) {
                endFrames->at(i) = eFrmqc->endFrameqt;
            }
        }
    }
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->initializeLocally(); 
        });
}
/// <summary>
/// 
/// </summary>
void MarkerFrameq::initializeGlobally()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->initializeGlobally(); 
        });
}

void MarkerFrameq::postInput()
{
    CartesianFrame::postInput();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postInput(); 
        });
}

void MarkerFrameq::simUpdateAll()
{
    //rOmO = rOpO + aAOp*rpmp
    //aAOm = aAOp*aApm
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    auto rOpO = prtFrmPtr->rOpO();
    auto aAOp = prtFrmPtr->aAOp();
    rOmO = rOpO->plusFullColumn(aAOp->timesFullColumn(rpmp));
    aAOm = aAOp->timesFullMatrix(aApm);
    auto pAOppE = prtFrmPtr->pAOppE();
    for (size_t i = 0; i < 4; i++)
    {
        auto pAOppEi = pAOppE->at(i);
        prOmOpE->atijputFullColumn(0, i, pAOppEi->timesFullColumn(rpmp));
        pAOmpE->at(i) = pAOppEi->timesFullMatrix(aApm);
    }
}

size_t MarkerFrameq::iqX() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->iqX;
}

FColDsptr MarkerFrameq::omeOmO() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->omeOpO();
}

FMatDsptr MarkerFrameq::pAdotjOmpE(size_t jj)
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    auto pAdotOppE = prtFrmPtr->pAdotOppE();
    auto aAjjpm = aApm->column(jj);
    auto answer = FullMatrix<double>::With(3, 4);
    for (size_t j = 0; j < 4; j++) {
        auto pAdotOppEj = pAdotOppE->at(j);
        auto pAdotjjpmpEj = pAdotOppEj->timesFullColumn(aAjjpm);
        answer->atijputFullColumn(0, j, pAdotjjpmpEj);
    }
    return answer;
}

FMatDsptr MarkerFrameq::pAdotjOmpET(size_t jj)
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    auto pAdotOppE = prtFrmPtr->pAdotOppE();
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

size_t MarkerFrameq::iqE() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->iqE;
}

void MarkerFrameq::fillqsu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsu(col); 
        });
}

void MarkerFrameq::fillqsuWeights(DiagMatDsptr mat)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsuWeights(mat); 
        });
}

void MarkerFrameq::fillqsuddotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsuddotlam(col); 
        });
}

void MarkerFrameq::fillqsulam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsulam(col); 
        });
}

void MarkerFrameq::fillpqsumu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillpqsumu(col); 
        });
}

void MarkerFrameq::fillpqsumudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillpqsumudot(col); 
        });
}

void MarkerFrameq::fillqsudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsudot(col); 
        });
}

void MarkerFrameq::fillqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrameq::fillqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrameq::fillqsudotWeights(DiagMatDsptr mat)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsudotWeights(mat); 
        });
}

void MarkerFrameq::setqsu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsu(col); 
        });
}

void MarkerFrameq::setqsulam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsulam(col); 
        });
}

void MarkerFrameq::setqsudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsudot(col); 
        });
}

void MarkerFrameq::setqsudotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsudotlam(col); 
        });
}

void MarkerFrameq::setqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrameq::setqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrameq::postPosICIteration()
{
    CartesianFrame::postPosICIteration();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postPosICIteration(); 
        });
}

void MarkerFrameq::postPosIC()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postPosIC(); 
        });
}

void MarkerFrameq::preDyn()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->preDyn(); 
        });
}

void MarkerFrameq::storeDynState()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->storeDynState(); 
        });
}

void MarkerFrameq::preVelIC()
{
    CartesianFrame::preVelIC();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->preVelIC(); 
        });
}

void MarkerFrameq::postVelIC()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postVelIC(); 
        });
}

void MarkerFrameq::preAccIC()
{
    CartesianFrame::preAccIC();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->preAccIC(); 
        });
}

void MarkerFrameq::preDynOutput()
{
    CartesianFrame::preDynOutput();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->preDynOutput(); 
        });
}

FColDsptr MarkerFrameq::qXdot() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qXdot;
}

FColDsptr MarkerFrameq::rmemOFrOeO(FColDsptr rOeOCol) const
{
    return aAOm->transposeTimesFullColumn(rOeOCol->minusFullColumn(rOmO));
}

FColDsptr MarkerFrameq::rOeOOFrmem(FColDsptr rmemCol) const
{
    return rOmO->plusFullColumn(aAOm->timesFullColumn(rmemCol));
}

std::shared_ptr<EulerParametersDot<double>> MarkerFrameq::qEdot() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qEdot;
}

FColDsptr MarkerFrameq::qX() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qX;
}

FColDsptr MarkerFrameq::qXddot() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qXddot;
}

FColDsptr MarkerFrameq::qEddot() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qEddot;
}

void MarkerFrameq::setqsuddotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsuddotlam(col); 
        });
}

FColFMatDsptr MarkerFrameq::pAOppE()
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->pAOppE();
}

FMatDsptr MarkerFrameq::aBOp() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->aBOp();
}

void MarkerFrameq::postDynStep()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postDynStep(); 
        });
}

void MarkerFrameq::setpqsumu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setpqsumu(col); 
        });
}

void MarkerFrameq::setpqsumudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setpqsumudot(col); 
        });
}

void MarkerFrameq::setpqsumuddot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setpqsumuddot(col); 
        });
}

void MarkerFrameq::postDynPredictor()
{
    CartesianFrame::postDynPredictor();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postDynPredictor(); 
        });
}

void MarkerFrameq::postDynOutput()
{
    CartesianFrame::postDynOutput();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postDynOutput(); 
        });
}

void MarkerFrameq::postDynCorrectorIteration()
{
    CartesianFrame::postDynCorrectorIteration();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postDynCorrectorIteration(); 
        });
}

FMatDsptr MarkerFrameq::pvOmOpE()
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    auto answer = FullMatrix<double>::With(3, 4);
    auto pAdotOppE = prtFrmPtr->pAdotOppE();
    for (size_t i = 0; i < 3; i++) {
        auto answeri = answer->at(i);
        for (size_t j = 0; j < 4; j++) {
            auto pAdotOpipEj = pAdotOppE->at(j)->at(i);
            answeri->atiput(j, pAdotOpipEj->dot(rpmp));
        }
    }
    return answer;
}

FColDsptr MarkerFrameq::vOmO() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->vOpO()->plusFullColumn(prtFrmPtr->aAdotOp()->timesFullColumn(rpmp));
}

FColDsptr MarkerFrameq::vOeO_of_rmem() const
{
    throw SimulationStoppingError("To be implemented.");
}

FColDsptr MarkerFrameq::aOmO() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->aOpO()->plusFullColumn(prtFrmPtr->aAddotOp()->timesFullColumn(rpmp));
}

void MarkerFrameq::setPartFrame(SpatialContainerFrame* partFrm)
{
    partFrame = partFrm;
}

FMatDsptr MarkerFrameq::pomeOmOpE()
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->pomeOpOpE();
}

FMatDsptr MarkerFrameq::pomeOmOpEdot()
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->pomeOpOpEdot();
}

SpatialContainerFrame* MarkerFrameq::getPartFrame() const {
    return partFrame;
}

void MarkerFrameq::setrpmp(FColDsptr x) const
{
    rpmp->copyFrom(x);
}

FColDsptr MarkerFrameq::aAdotjOm(size_t j)
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->aAdotOp()->timesFullColumn(aApm->column(j));
}

void MarkerFrameq::setaApm(FMatDsptr mat) const
{
    aApm->copyFrom(mat);
}

bool MarkerFrameq::has_qX() const
{
    return true;
}
