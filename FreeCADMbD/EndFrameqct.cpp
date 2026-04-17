/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "EndFrameqct.h"
#include "Variable.h"
#include "MarkerFrameqc.h"
#include "EndFrameqct2.h"
#include "EndFrameqccq.h"
#include "EndFrameqct.h"
#include "MarkerFrameqc.h"
#include "System.h"
#include "Symbolic.h"
#include "SymTime.h"
#include "EulerParameters.h"
#include "EulerAngles.h"
#include "EulerAnglesDot.h"
#include "EulerAnglesDDot.h"

using namespace MbD;

std::shared_ptr<EndFrameqct> EndFrameqct::With()
{
    auto inst = std::make_shared<EndFrameqct>();
    inst->initialize();
    return inst;
}

std::shared_ptr<EndFrameqct> EndFrameqct::With(const std::string& str)
{
    auto inst = std::make_shared<EndFrameqct>(str);
    inst->initialize();
    return inst;
}

void EndFrameqct::initialize()
{
    EndFrameqc::initialize();
    rmem = std::make_shared<FullColumn<double>>(3);
    prmempt = std::make_shared<FullColumn<double>>(3);
    pprmemptpt = std::make_shared<FullColumn<double>>(3);
    aAme = FullMatrix<double>::identitysptr(3);
    pAmept = FullMatrix<double>::With(3, 3);
    ppAmeptpt = FullMatrix<double>::With(3, 3);
    pprOeOpEpt = FullMatrix<double>::With(3, 4);
    pprOeOptpt = std::make_shared<FullColumn<double>>(3);
    ppAOepEpt = std::make_shared<FullColumn<FMatDsptr>>(4);
    ppAOeptpt = FullMatrix<double>::With(3, 3);
}

void EndFrameqct::initializeLocally()
{
    EndFrameqc::initializeLocally();
    if (!rmemBlks) {
        rmem->zeroSelf();
        prmempt->zeroSelf();
        pprmemptpt->zeroSelf();
    }
    if (!the1x2y3zBlks) {
        aAme->identity();
        pAmept->zeroSelf();
        ppAmeptpt->zeroSelf();
    }
}

void EndFrameqct::initializeGlobally()
{
    EndFrameqc::initializeGlobally();
    if (rmemBlks) {
        initprmemptBlks();
        initpprmemptptBlks();
    }
    if (the1x2y3zBlks) {
        initpthe1x2y3zptBlks();
        initppthe1x2y3zptptBlks();
    }
}

void EndFrameqct::initprmemptBlks()
{
    auto mbdTime = root()->time;
    prmemptBlks = std::make_shared< FullColumn<Symsptr>>(3);
    for (size_t i = 0; i < 3; i++) {
        auto disp = rmemBlks->at(i);
        auto var = disp->differentiateWRT(mbdTime);
        auto vel = var->simplified(var);
        prmemptBlks->at(i) = vel;
    }
}

void EndFrameqct::initpprmemptptBlks()
{
    auto mbdTime = root()->time;
    pprmemptptBlks = std::make_shared< FullColumn<Symsptr>>(3);
    for (size_t i = 0; i < 3; i++) {
        auto vel = prmemptBlks->at(i);
        auto var = vel->differentiateWRT(mbdTime);
        auto acc = var->simplified(var);
        pprmemptptBlks->at(i) = acc;
    }
}

void EndFrameqct::initpthe1x2y3zptBlks()
{
    auto mbdTime = root()->time;
    pthe1x2y3zptBlks = std::make_shared< FullColumn<Symsptr>>(3);
    for (size_t i = 0; i < 3; i++) {
        auto angle = the1x2y3zBlks->at(i);
        auto var = angle->differentiateWRT(mbdTime);
        //std::cout << "var " << *var << std::endl;
        auto vel = var->simplified(var);
        //std::cout << "vel " << *vel << std::endl;
        pthe1x2y3zptBlks->at(i) = vel;
        //std::cout << *angle << std::endl;
        //std::cout << *vel << std::endl;
    }
}

void EndFrameqct::initppthe1x2y3zptptBlks()
{
    auto mbdTime = root()->time;
    ppthe1x2y3zptptBlks = std::make_shared< FullColumn<Symsptr>>(3);
    for (size_t i = 0; i < 3; i++) {
        auto angleVel = pthe1x2y3zptBlks->at(i);
        auto var = angleVel->differentiateWRT(mbdTime);
        auto angleAcc = var->simplified(var);
        ppthe1x2y3zptptBlks->at(i) = angleAcc;
        //std::cout << *angleVel << std::endl;
        //std::cout << *angleAcc << std::endl;
    }
}

void EndFrameqct::postInput()
{
    evalrmem();
    evalAme();
    Item::postInput();
}

void EndFrameqct::simUpdateAll()
{
    //rOeO = rOmO + aAOm*rmem(t)
    //aAOe = aAOm*aAme(t);
    EndFrameqc::simUpdateAll();
    auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
    auto rOmO = markerFrame->rOmO;
    auto aAOm = markerFrame->aAOm;
    rOeO = rOmO->plusFullColumn(aAOm->timesFullColumn(rmem));
    auto prOmOpE = mkrFrmqc->prOmOpE;
    auto pAOmpE = mkrFrmqc->pAOmpE;
    for (size_t i = 0; i < 3; i++)
    {
        auto prOmOpEi = prOmOpE->at(i);
        auto prOeOpEi = prOeOpE->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto prOeOpEij = prOmOpEi->at(j) + pAOmpE->at(j)->at(i)->timesFullColumn(rmem);
            prOeOpEi->at(j) = prOeOpEij;
        }
    }
    auto rpep = markerFrame->rpmp->plusFullColumn(markerFrame->aApm->timesFullColumn(rmem));
    pprOeOpEpE = EulerParameters<double>::ppApEpEtimesColumn(rpep);
    aAOe = aAOm->timesFullMatrix(aAme);
    for (size_t i = 0; i < 4; i++)
    {
        pAOepE->at(i) = pAOmpE->at(i)->timesFullMatrix(aAme);
    }
    auto aApe = markerFrame->aApm->timesFullMatrix(aAme);
    ppAOepEpE = EulerParameters<double>::ppApEpEtimesMatrix(aApe);
}

FRowDsptr EndFrameqct::ppriOeOpEpt(size_t i) const
{
    return pprOeOpEpt->at(i);
}

FMatDsptr EndFrameqct::ppAjOepETpt(size_t jj) const
{
    auto answer = FullMatrix<double>::With(4, 3);
    for (size_t i = 0; i < 4; i++)
    {
        auto answeri = answer->at(i);
        auto ppAOepEipt = ppAOepEpt->at(i);
        for (size_t j = 0; j < 3; j++)
        {
            auto answerij = ppAOepEipt->at(j)->at(jj);
            answeri->atiput(j, answerij);
        }
    }
    return answer;
}

void EndFrameqct::prePosIC()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    EndFrameqc::prePosIC();
}

void EndFrameqct::evalrmem() const
{
    if (rmemBlks) {
        for (size_t i = 0; i < 3; i++)
        {
            auto expression = rmemBlks->at(i);
            double value = expression->getValue();
            rmem->at(i) = value;
        }
    }
}

void EndFrameqct::evalAme()
{
    if (the1x2y3zBlks) {
        auto the1x2y3z = EulerAngles<double>::With();
        for (size_t i = 0; i < 3; i++)
        {
            auto expression = the1x2y3zBlks->at(i);
            auto value = expression->getValue();
            the1x2y3z->at(i) = value;
        }
        the1x2y3z->calc();
        aAme = the1x2y3z->aA;
    }
}

void EndFrameqct::preVelIC()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    Item::preVelIC();
    evalprmempt();
    evalpAmept();
    auto aAOm = markerFrame->aAOm;
    prOeOpt = aAOm->timesFullColumn(prmempt);
    pAOept = aAOm->timesFullMatrix(pAmept);
}

void EndFrameqct::postVelIC()
{
    auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
    auto pAOmpE = mkrFrmqc->pAOmpE;
    for (size_t i = 0; i < 3; i++)
    {
        auto pprOeOpEpti = pprOeOpEpt->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            auto pprOeOpEptij = pAOmpE->at(j)->at(i)->dot(prmempt);
            pprOeOpEpti->atiput(j, pprOeOpEptij);
        }
    }
    for (size_t i = 0; i < 4; i++)
    {
        ppAOepEpt->atiput(i, pAOmpE->at(i)->timesFullMatrix(pAmept));
    }
}

FColDsptr EndFrameqct::pAjOept(size_t j) const
{
    return pAOept->column(j);
}

FMatDsptr EndFrameqct::ppAjOepETpt(size_t jj)
{
    auto answer = FullMatrix<double>::With(4, 3);
    for (size_t i = 0; i < 4; i++)
    {
        auto answeri = answer->at(i);
        auto ppAOepEipt = ppAOepEpt->at(i);
        for (size_t j = 0; j < 3; j++)
        {
            auto answerij = ppAOepEipt->at(j)->at(jj);
            answeri->atiput(j, answerij);
        }
    }
    return answer;
}

FColDsptr EndFrameqct::ppAjOeptpt(size_t j) const
{
    return ppAOeptpt->column(j);
}

double EndFrameqct::priOeOpt(size_t i) const
{
    return prOeOpt->at(i);
}

FRowDsptr EndFrameqct::ppriOeOpEpt(size_t i)
{
    return pprOeOpEpt->at(i);
}

double EndFrameqct::ppriOeOptpt(size_t i) const
{
    return pprOeOptpt->at(i);
}

void EndFrameqct::evalprmempt() const
{
    if (rmemBlks) {
        for (size_t i = 0; i < 3; i++)
        {
            auto derivative = prmemptBlks->at(i);
            auto value = derivative->getValue();
            prmempt->at(i) = value;
        }
    }
}

void EndFrameqct::evalpAmept()
{
    if (the1x2y3zBlks) {
        auto the1x2y3z = EulerAngles<double>::With();
        auto the1x2y3zDot = EulerAnglesDot<double>::With();
        the1x2y3zDot->aEulerAngles = the1x2y3z.get();
        for (size_t i = 0; i < 3; i++)
        {
            auto expression = the1x2y3zBlks->at(i);
            auto derivative = pthe1x2y3zptBlks->at(i);
            auto value = expression->getValue();
            auto valueDot = derivative->getValue();
            the1x2y3z->at(i) = value;
            the1x2y3zDot->at(i) = valueDot;
        }
        the1x2y3z->calc();
        the1x2y3zDot->calc();
        pAmept = the1x2y3zDot->aAdot;
    }
}

void EndFrameqct::evalpprmemptpt() const
{
    if (rmemBlks) {
        for (size_t i = 0; i < 3; i++)
        {
            auto secondDerivative = pprmemptptBlks->at(i);
            auto value = secondDerivative->getValue();
            pprmemptpt->atiput(i, value);
        }
    }
}

void EndFrameqct::evalppAmeptpt()
{
    if (the1x2y3zBlks) {
        auto the1x2y3z = EulerAngles<double>::With();
        auto the1x2y3zDot = EulerAnglesDot<double>::With();
        the1x2y3zDot->aEulerAngles = the1x2y3z.get();
        auto the1x2y3zDDot = EulerAnglesDDot<double>::With();
        the1x2y3zDDot->aEulerAnglesDot = the1x2y3zDot.get();
        for (size_t i = 0; i < 3; i++)
        {
            auto expression = the1x2y3zBlks->at(i);
            auto derivative = pthe1x2y3zptBlks->at(i);
            auto secondDerivative = ppthe1x2y3zptptBlks->at(i);
            auto value = expression->getValue();
            auto valueDot = derivative->getValue();
            auto valueDDot = secondDerivative->getValue();
            the1x2y3z->atiput(i, value);
            the1x2y3zDot->atiput(i, valueDot);
            the1x2y3zDDot->atiput(i, valueDDot);
        }
        the1x2y3z->calc();
        the1x2y3zDot->calc();
        the1x2y3zDDot->calc();
        ppAmeptpt = the1x2y3zDDot->aAddot;
    }
}

FColDsptr EndFrameqct::rmeO()
{
    return markerFrame->aAOm->timesFullColumn(rmem);
}

FColDsptr EndFrameqct::rpep()
{
    auto rpmp = markerFrame->rpmp;
    auto aApm = markerFrame->aApm;
    auto rpep = rpmp->plusFullColumn(aApm->timesFullColumn(rmem));
    return rpep;
}

void EndFrameqct::preAccIC()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    Item::preVelIC();
    evalprmempt();
    evalpAmept();
    auto aAOm = markerFrame->aAOm;
    prOeOpt = aAOm->timesFullColumn(prmempt);
    pAOept = aAOm->timesFullMatrix(pAmept);
    Item::preAccIC();
    evalpprmemptpt();
    evalppAmeptpt();
    aAOm = markerFrame->aAOm;
    pprOeOptpt = aAOm->timesFullColumn(pprmemptpt);
    ppAOeptpt = aAOm->timesFullMatrix(ppAmeptpt);
}

bool EndFrameqct::isEndFrameqc()
{
    return false;
}

void EndFrameqct::postDynPredictor()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    EndFrameqc::postDynPredictor();
}

void EndFrameqct::preDynOutput()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    EndFrameqc::preDynOutput();
}

void EndFrameqct::postDynOutput()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    EndFrameqc::postDynOutput();
}

FColDsptr MbD::EndFrameqct::getprOeOpt() const
{
    return prOeOpt;
}

FMatDsptr MbD::EndFrameqct::getpprOeOpEpt() const
{
    return pprOeOpEpt;
}

FColDsptr MbD::EndFrameqct::getpprOeOptpt() const
{
    return pprOeOptpt;
}

FMatDsptr MbD::EndFrameqct::getpAOept() const
{
    return pAOept;
}

FColFMatDsptr MbD::EndFrameqct::getppAOepEpt() const
{
    return ppAOepEpt;
}

FMatDsptr MbD::EndFrameqct::getppAOeptpt() const
{
    return ppAOeptpt;
}

FMatDsptr MbD::EndFrameqct::ppAOeTpEpttimesFullColumn(FColDsptr col) const
{
    auto answer = FullMatrix<double>::With(3, 4);
    for (size_t j = 0; j < 4; j++)
    {
        auto ppAOepEjpt = ppAOepEpt->at(j);
        auto answerCol = ppAOepEjpt->transposeTimesFullColumn(col);
        answer->atijputFullColumn(0, j, answerCol);
    }
    return answer;
}
