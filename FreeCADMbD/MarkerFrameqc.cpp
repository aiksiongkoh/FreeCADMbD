/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "MarkerFrameqc.h"
#include "MarkerFramec.h"
#include "PartFrame.h"
 //#include "EndFramec.h"
#include "EndFrameqct.h"
#include "EulerParameters.h"

using namespace MbD;

std::shared_ptr<MarkerFrameqc> MarkerFrameqc::With(const std::string& str)
{
    auto inst = std::make_shared<MarkerFrameqc>(str);
    inst->initialize();
    return inst;
}

void MarkerFrameqc::initialize()
{
    endFrames = std::make_shared<std::vector<EndFrmsptr>>();
    auto endFrm = EndFrameqc::With();
    addEndFrame(endFrm);
    prOmOpE = FullMatrix<double>::With(3, 4);
    pAOmpE = std::make_shared<FullColumn<FMatDsptr>>(4);
}

System* MarkerFrameqc::root()
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->root();
}

void MarkerFrameqc::initializeLocally()
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
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->initializeLocally(); 
        });
}
/// <summary>
/// 
/// </summary>
void MarkerFrameqc::initializeGlobally()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->initializeGlobally(); 
        });
}

void MarkerFrameqc::postInput()
{
    CartesianFrame::postInput();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postInput(); 
        });
}

void MarkerFrameqc::simUpdateAll()
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

void MarkerFrameqc::preStatic()
{
    throw SimulationStoppingError("To be implemented.");
}

size_t MarkerFrameqc::iqX() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->iqX;
}

FColDsptr MarkerFrameqc::omeOmO() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->omeOpO();
}

FMatDsptr MarkerFrameqc::pAdotjOmpE(size_t jj)
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

FMatDsptr MarkerFrameqc::pAdotjOmpET(size_t jj)
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

size_t MarkerFrameqc::iqE() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->iqE;
}

void MarkerFrameqc::fillqsu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsu(col); 
        });
}

void MarkerFrameqc::fillqsuWeights(DiagMatDsptr mat)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsuWeights(mat); 
        });
}

void MarkerFrameqc::fillqsuddotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsuddotlam(col); 
        });
}

void MarkerFrameqc::fillqsulam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsulam(col); 
        });
}

void MarkerFrameqc::fillpqsumu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillpqsumu(col); 
        });
}

void MarkerFrameqc::fillpqsumudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillpqsumudot(col); 
        });
}

void MarkerFrameqc::fillqsudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsudot(col); 
        });
}

void MarkerFrameqc::fillqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrameqc::fillqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrameqc::fillqsudotWeights(DiagMatDsptr mat)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->fillqsudotWeights(mat); 
        });
}

void MarkerFrameqc::setqsu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsu(col); 
        });
}

void MarkerFrameqc::setqsulam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsulam(col); 
        });
}

void MarkerFrameqc::setqsudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsudot(col); 
        });
}

void MarkerFrameqc::setqsudotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsudotlam(col); 
        });
}

void MarkerFrameqc::setqsudotPlam(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrameqc::setqsudotPlamDeriv(FColDsptr col)
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrameqc::postPosICIteration()
{
    CartesianFrame::postPosICIteration();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postPosICIteration(); 
        });
}

void MarkerFrameqc::postStaticIteration()
{
    throw SimulationStoppingError("To be implemented.");
}

void MarkerFrameqc::postPosIC()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postPosIC(); 
        });
}

void MarkerFrameqc::preDyn()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->preDyn(); 
        });
}

void MarkerFrameqc::storeDynState()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->storeDynState(); 
        });
}

void MarkerFrameqc::preVelIC()
{
    CartesianFrame::preVelIC();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->preVelIC(); 
        });
}

void MarkerFrameqc::postVelIC()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postVelIC(); 
        });
}

void MarkerFrameqc::preAccIC()
{
    CartesianFrame::preAccIC();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->preAccIC(); 
        });
}

void MarkerFrameqc::preDynOutput()
{
    CartesianFrame::preDynOutput();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->preDynOutput(); 
        });
}

FColDsptr MarkerFrameqc::qXdot() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qXdot;
}

FColDsptr MarkerFrameqc::rmemOFrOeO(FColDsptr rOeOCol) const
{
    return aAOm->transposeTimesFullColumn(rOeOCol->minusFullColumn(rOmO));
}

FColDsptr MarkerFrameqc::rOeOOFrmem(FColDsptr rmemCol) const
{
    return rOmO->plusFullColumn(aAOm->timesFullColumn(rmemCol));
}

std::shared_ptr<EulerParametersDot<double>> MarkerFrameqc::qEdot() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qEdot;
}

FColDsptr MarkerFrameqc::qX() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qX;
}

FColDsptr MarkerFrameqc::qXddot() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qXddot;
}

FColDsptr MarkerFrameqc::qEddot() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->qEddot;
}

void MarkerFrameqc::setqsuddotlam(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setqsuddotlam(col); 
        });
}

FColFMatDsptr MarkerFrameqc::pAOppE()
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->pAOppE();
}

FMatDsptr MarkerFrameqc::aBOp() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->aBOp();
}

void MarkerFrameqc::postDynStep()
{
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postDynStep(); 
        });
}

void MarkerFrameqc::setpqsumu(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setpqsumu(col); 
        });
}

void MarkerFrameqc::setpqsumudot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setpqsumudot(col); 
        });
}

void MarkerFrameqc::setpqsumuddot(FColDsptr col)
{
    endFramesDo([&](const EndFrmsptr& endFrame) { 
        endFrame->setpqsumuddot(col); 
        });
}

void MarkerFrameqc::postDynPredictor()
{
    CartesianFrame::postDynPredictor();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postDynPredictor(); 
        });
}

void MarkerFrameqc::postDynOutput()
{
    CartesianFrame::postDynOutput();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postDynOutput(); 
        });
}

void MarkerFrameqc::postDynCorrectorIteration()
{
    CartesianFrame::postDynCorrectorIteration();
    endFramesDo([&](EndFrmsptr endFrame) { 
        endFrame->postDynCorrectorIteration(); 
        });
}

FMatDsptr MarkerFrameqc::pvOmOpE()
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

FColDsptr MarkerFrameqc::vOmO() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->vOpO()->plusFullColumn(prtFrmPtr->aAdotOp()->timesFullColumn(rpmp));
}

FColDsptr MarkerFrameqc::vOeO_of_rmem() const
{
    throw SimulationStoppingError("To be implemented.");
    return FColDsptr();
}

FColDsptr MarkerFrameqc::aOmO() const
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->aOpO()->plusFullColumn(prtFrmPtr->aAddotOp()->timesFullColumn(rpmp));
}

void MarkerFrameqc::setPartFrame(SpatialContainerFrame* partFrm)
{
    partFrame = partFrm;
}

FMatDsptr MarkerFrameqc::pomeOmOpE()
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->pomeOpOpE();
}

FMatDsptr MarkerFrameqc::pomeOmOpEdot()
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->pomeOpOpEdot();
}

SpatialContainerFrame* MarkerFrameqc::getPartFrame() const {
    return partFrame;
}

void MarkerFrameqc::setrpmp(FColDsptr x) const
{
    rpmp->copyFrom(x);
}

FColDsptr MarkerFrameqc::aAdotjOm(size_t j)
{
    auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
    return prtFrmPtr->aAdotOp()->timesFullColumn(aApm->column(j));
}

void MarkerFrameqc::setaApm(FMatDsptr mat) const
{
    aApm->copyFrom(mat);
}

bool MarkerFrameqc::has_qX() const
{
    return true;
}
