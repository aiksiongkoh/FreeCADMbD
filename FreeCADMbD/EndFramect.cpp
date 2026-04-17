/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "EndFramect.h"
#include "MarkerFramec.h"
#include "System.h"
#include "Symbolic.h"
#include "SymTime.h"
#include "EulerAngles.h"
#include "EulerAnglesDot.h"
#include "EulerAnglesDDot.h"

using namespace MbD;

std::shared_ptr<EndFramect> EndFramect::With(const std::string& str)
{
    auto inst = std::make_shared<EndFramect>(str);
    inst->initialize();
    return inst;
}

void EndFramect::initialize()
{
    EndFramec::initialize();
    rmem = std::make_shared<FullColumn<double>>(3);
    prmempt = std::make_shared<FullColumn<double>>(3);
    pprmemptpt = std::make_shared<FullColumn<double>>(3);
    aAme = FullMatrix<double>::identitysptr(3);
    pAmept = FullMatrix<double>::With(3, 3);
    ppAmeptpt = FullMatrix<double>::With(3, 3);
    pprOeOptpt = std::make_shared<FullColumn<double>>(3);
    ppAOeptpt = FullMatrix<double>::With(3, 3);
}

void EndFramect::initializeLocally()
{
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

void EndFramect::initializeGlobally()
{
    if (rmemBlks) {
        initprmemptBlks();
        initpprmemptptBlks();
    }
    if (the1x2y3zBlks) {
        initpthe1x2y3zptBlks();
        initppthe1x2y3zptptBlks();
    }
}

void EndFramect::initprmemptBlks()
{
    auto mbdTime = root()->time;
    prmemptBlks = std::make_shared< FullColumn<Symsptr>>(3);
    for (size_t i = 0; i < 3; i++) {
        auto disp = rmemBlks->at(i);
        auto var = disp->differentiateWRT(std::static_pointer_cast<Symbolic>(mbdTime));
        auto vel = var->simplified(var);
        prmemptBlks->at(i) = vel;
    }
}

void EndFramect::initpprmemptptBlks()
{
    auto mbdTime = root()->time;
    pprmemptptBlks = std::make_shared< FullColumn<Symsptr>>(3);
    for (size_t i = 0; i < 3; i++) {
        auto vel = prmemptBlks->at(i);
        auto var = vel->differentiateWRT(std::static_pointer_cast<Symbolic>(mbdTime));
        auto acc = var->simplified(var);
        pprmemptptBlks->at(i) = acc;
    }
}

void EndFramect::initpthe1x2y3zptBlks()
{
    auto mbdTime = root()->time;
    pthe1x2y3zptBlks = std::make_shared< FullColumn<Symsptr>>(3);
    for (size_t i = 0; i < 3; i++) {
        auto angle = the1x2y3zBlks->at(i);
        auto var = angle->differentiateWRT(std::static_pointer_cast<Symbolic>(mbdTime));
        auto vel = var->simplified(var);
        pthe1x2y3zptBlks->at(i) = vel;
    }
}

void EndFramect::initppthe1x2y3zptptBlks()
{
    auto mbdTime = root()->time;
    ppthe1x2y3zptptBlks = std::make_shared< FullColumn<Symsptr>>(3);
    for (size_t i = 0; i < 3; i++) {
        auto angleVel = pthe1x2y3zptBlks->at(i);
        auto var = angleVel->differentiateWRT(std::static_pointer_cast<Symbolic>(mbdTime));
        auto angleAcc = var->simplified(var);
        ppthe1x2y3zptptBlks->at(i) = angleAcc;
    }
}

void EndFramect::postInput()
{
    evalrmem();
    evalAme();
    Item::postInput();
}

void EndFramect::prePosIC()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    EndFramec::prePosIC();
}

void EndFramect::evalrmem() const
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

void EndFramect::evalAme()
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

void EndFramect::preVelIC()
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

FColDsptr EndFramect::pAjOept(size_t j) const
{
    return pAOept->column(j);
}

FColDsptr EndFramect::ppAjOeptpt(size_t j) const
{
    return ppAOeptpt->column(j);
}

double EndFramect::priOeOpt(size_t i) const
{
    return prOeOpt->at(i);
}

double EndFramect::ppriOeOptpt(size_t i) const
{
    return pprOeOptpt->at(i);
}

void EndFramect::evalprmempt() const
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

void EndFramect::evalpAmept()
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

void EndFramect::evalpprmemptpt() const
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

void EndFramect::evalppAmeptpt()
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

//FColDsptr EndFramect::rpep()
//{
//    return FColDsptr();
//}

void EndFramect::preAccIC()
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

void EndFramect::postDynPredictor()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    EndFramec::postDynPredictor();
}

void EndFramect::preDynOutput()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    EndFramec::preDynOutput();
}

void EndFramect::postDynOutput()
{
    time = root()->mbdTimeValue();
    evalrmem();
    evalAme();
    EndFramec::postDynOutput();
}

void EndFramect::simUpdateAll()
{
    //rOeO = rOmO + aAOm*rmem(t)
    //aAOe = aAOm*aAme(t);
    EndFramec::simUpdateAll();
    auto mkrFrmqc = static_cast<MarkerFramec*>(markerFrame);
    auto rOmO = markerFrame->rOmO;
    auto aAOm = markerFrame->aAOm;
    rOeO = rOmO->plusFullColumn(aAOm->timesFullColumn(rmem));
    aAOe = aAOm->timesFullMatrix(aAme);
}

FColDsptr MbD::EndFramect::getprOeOpt() const
{
    return prOeOpt;
}

FColDsptr MbD::EndFramect::getpprOeOptpt() const
{
    return pprOeOptpt;
}

FMatDsptr MbD::EndFramect::getpAOept() const
{
    return pAOept;
}

FMatDsptr MbD::EndFramect::getppAOeptpt() const
{
    return ppAOeptpt;
}
