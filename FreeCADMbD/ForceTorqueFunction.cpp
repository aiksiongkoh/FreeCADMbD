#include "ForceTorqueFunction.h"
#include <algorithm>

using namespace MbD;

std::shared_ptr<ForceTorqueFunction> ForceTorqueFunction::With()
{

    auto inst = std::make_shared<ForceTorqueFunction>();
    inst->initialize();
    return inst;
}

void ForceTorqueFunction::initialize()
{
    ForceTorqueItem::initialize();
    kineIJs = std::make_shared<std::vector<std::shared_ptr<MbDSymbolicFunction>>>();
    kinedotIJs = std::make_shared<std::vector<std::shared_ptr<MbDSymbolicFunction>>>();
    jointActions = std::make_shared<std::vector<std::shared_ptr<MbDSymbolicFunction>>>();
}

void ForceTorqueFunction::calcPostDynCorrectorIteration()
{
    //Do nothing.
}

Symsptr ForceTorqueFunction::getformula()
{
    return forTorFunc;
}

void ForceTorqueFunction::setformula(Symsptr function)
{
    forTorFunc = function;
}

void ForceTorqueFunction::postDynPredictor()
{
    for (const auto kineIJ : *kineIJs) kineIJ->postDynPredictor();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->postDynPredictor();
    for (const auto jointAction : *jointActions) jointAction->postDynPredictor();
    ForceTorqueItem::postDynPredictor();
}

void ForceTorqueFunction::postInput()
{
    for (const auto kineIJ : *kineIJs) kineIJ->postInput();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->postInput();
    for (const auto jointAction : *jointActions) jointAction->postInput();
    ForceTorqueItem::postInput();
}

void ForceTorqueFunction::postStaticIteration()
{
    for (const auto kineIJ : *kineIJs) kineIJ->postStaticIteration();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->postStaticIteration();
    for (const auto jointAction : *jointActions) jointAction->postStaticIteration();
    ForceTorqueItem::postStaticIteration();
}

void ForceTorqueFunction::preAccIC()
{
    for (const auto kineIJ : *kineIJs) kineIJ->preAccIC();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->preAccIC();
    for (const auto jointAction : *jointActions) jointAction->preAccIC();
    ForceTorqueItem::preAccIC();
}

void ForceTorqueFunction::preDynOutput()
{
    for (const auto kineIJ : *kineIJs) kineIJ->preDynOutput();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->preDynOutput();
    for (const auto jointAction : *jointActions) jointAction->preDynOutput();
    ForceTorqueItem::preDynOutput();
}

void ForceTorqueFunction::preStatic()
{
    for (const auto kineIJ : *kineIJs) kineIJ->preStatic();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->preStatic();
    for (const auto jointAction : *jointActions) jointAction->preStatic();
    ForceTorqueItem::preStatic();
}

void ForceTorqueFunction::simUpdateAll()
{
    for (const auto kineIJ : *kineIJs) kineIJ->simUpdateAll();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->simUpdateAll();
    for (const auto jointAction : *jointActions) jointAction->simUpdateAll();
    ForceTorqueItem::simUpdateAll();
}

FColDsptr ForceTorqueFunction::pFTpkineIJs()
{
    auto pFTpkineIJs = std::make_shared<FullColumn<double>>(pFTpkineIJFuncs->size());
    std::transform(pFTpkineIJFuncs->begin(),
        pFTpkineIJFuncs->end(),
        pFTpkineIJs->begin(),
        [&](auto pFTpkineIJFunc) { return pFTpkineIJFunc->getValue(); }
    );
    return pFTpkineIJs;
}

FColDsptr ForceTorqueFunction::pFTpkinedotIJs()
{
    auto pFTpkinedotIJs = std::make_shared<FullColumn<double>>(pFTpkinedotIJFuncs->size());
    std::transform(pFTpkinedotIJFuncs->begin(),
        pFTpkinedotIJFuncs->end(),
        pFTpkinedotIJs->begin(),
        [&](auto pFTpkinedotIJFunc) { return pFTpkinedotIJFunc->getValue(); }
    );
    return pFTpkinedotIJs;
}

FColDsptr ForceTorqueFunction::pFTpJtActs()
{
    auto pFTpJtActs = std::make_shared<FullColumn<double>>(pFTpJtActFuncs->size());
    std::transform(pFTpJtActFuncs->begin(),
        pFTpJtActFuncs->end(),
        pFTpJtActs->begin(),
        [&](auto pFTpJtActFunc) { return pFTpJtActFunc->getValue(); }
    );
    return pFTpJtActs;
}

double ForceTorqueFunction::forTor()
{
    return forTorFunc->getValue();
}

double ForceTorqueFunction::value()
{
    return forTorFunc->getValue();
}

FRowDsptr MbD::ForceTorqueFunction::pvaluepX(SpatialContainerFrame* partFrame)
{
    auto answer = FullRow<double>::With(3, 0.0);
    for (size_t i = 0; i < kineIJs->size(); i++) {
        auto kineIJ = kineIJs->at(i);
        auto pfpkineIJ = pFTpkineIJFuncs->at(i)->getValue();
        auto pkineIJpX = kineIJ->pvaluepX(partFrame);
        if (pkineIJpX) {
            answer->equalSelfPlusFullRowtimes(pkineIJpX, pfpkineIJ);
        }
    }
    //Must not return an empty std::shared_ptr
    return answer;
}

FRowDsptr MbD::ForceTorqueFunction::pvaluepE(SpatialContainerFrame* partFrame)
{
    auto answer = FullRow<double>::With(4, 0.0);
    for (size_t i = 0; i < kineIJs->size(); i++) {
        auto kineIJ = kineIJs->at(i);
        auto pfpkineIJ = pFTpkineIJFuncs->at(i)->getValue();
        auto pkineIJpE = kineIJ->pvaluepE(partFrame);
        if (pkineIJpE) {
            answer->equalSelfPlusFullRowtimes(pkineIJpE, pfpkineIJ);
        }
    }
    //Must not return an empty std::shared_ptr
    return answer;
}

FRowDsptr MbD::ForceTorqueFunction::pvaluepXdot(SpatialContainerFrame* partFrame)
{
    auto answer = FullRow<double>::With(3, 0.0);
    for (size_t i = 0; i < kinedotIJs->size(); i++) {
        auto kinedotIJ = kinedotIJs->at(i);
        auto pfpkinedotIJ = pFTpkinedotIJFuncs->at(i)->getValue();
        auto pkinedotIJpXdot = kinedotIJ->pvaluepXdot(partFrame);
        if (pkinedotIJpXdot) {
            answer->equalSelfPlusFullRowtimes(pkinedotIJpXdot, pfpkinedotIJ);
        }
    }
    //Must not return an empty std::shared_ptr
    return answer;
}

FRowDsptr MbD::ForceTorqueFunction::pvaluepEdot(SpatialContainerFrame* partFrame)
{
    auto answer = FullRow<double>::With(4, 0.0);
    for (size_t i = 0; i < kinedotIJs->size(); i++) {
        auto kinedotIJ = kinedotIJs->at(i);
        auto pfpkinedotIJ = pFTpkinedotIJFuncs->at(i)->getValue();
        auto pkinedotIJpEdot = kinedotIJ->pvaluepEdot(partFrame);
        if (pkinedotIJpEdot) {
            answer->equalSelfPlusFullRowtimes(pkinedotIJpEdot, pfpkinedotIJ);
        }
    }
    //Must not return an empty std::shared_ptr
    return answer;
}

void ForceTorqueFunction::initializeGlobally()
{
    for (const auto kineIJ : *kineIJs) kineIJ->initializeGlobally();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->initializeGlobally();
    for (const auto jointAction : *jointActions) jointAction->initializeGlobally();
    pFTpkineIJFuncs = std::make_shared<std::vector<Symsptr>>(kineIJs->size());
    std::transform(kineIJs->begin(),
        kineIJs->end(),
        pFTpkineIJFuncs->begin(),
        [&](auto kineIJ) { return forTorFunc->differentiateWRT(kineIJ)->simplified(); }
    );
    pFTpkinedotIJFuncs = std::make_shared<std::vector<Symsptr>>(kinedotIJs->size());
    std::transform(kinedotIJs->begin(),
        kinedotIJs->end(),
        pFTpkinedotIJFuncs->begin(),
        [&](auto kinedotIJ) { return forTorFunc->differentiateWRT(kinedotIJ)->simplified(); }
    );
    pFTpJtActFuncs = std::make_shared<std::vector<Symsptr>>(jointActions->size());
    std::transform(jointActions->begin(),
        jointActions->end(),
        pFTpJtActFuncs->begin(),
        [&](auto jointAction) { return forTorFunc->differentiateWRT(jointAction)->simplified(); }
    );
}

void ForceTorqueFunction::initializeLocally()
{
    //std::cout << *forTorFunc << std::endl;
    forTorFunc->fillKineIJs(kineIJs);
    forTorFunc->fillKinedotIJs(kinedotIJs);
    forTorFunc->fillJointForces(jointActions);
    forTorFunc->fillJointTorques(jointActions);
    for (const auto kineIJ : *kineIJs) kineIJ->initializeLocally();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->initializeLocally();
    for (const auto jointAction : *jointActions) jointAction->initializeLocally();
}

void ForceTorqueFunction::postAccICIteration()
{
    for (const auto kineIJ : *kineIJs) kineIJ->postAccICIteration();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->postAccICIteration();
    for (const auto jointAction : *jointActions) jointAction->postAccICIteration();
    ForceTorqueItem::postAccICIteration();
}

void ForceTorqueFunction::postCollisionCorrectorIteration()
{
    for (const auto kineIJ : *kineIJs) kineIJ->postCollisionCorrectorIteration();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->postCollisionCorrectorIteration();
    for (const auto jointAction : *jointActions) jointAction->postCollisionCorrectorIteration();
    ForceTorqueItem::postCollisionCorrectorIteration();
}

void ForceTorqueFunction::postCollisionPredictor()
{
    for (const auto kineIJ : *kineIJs) kineIJ->postCollisionPredictor();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->postCollisionPredictor();
    for (const auto jointAction : *jointActions) jointAction->postCollisionPredictor();
    ForceTorqueItem::postCollisionPredictor();
}

void ForceTorqueFunction::postDynCorrectorIteration()
{
    for (const auto kineIJ : *kineIJs) kineIJ->postDynCorrectorIteration();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->postDynCorrectorIteration();
    for (const auto jointAction : *jointActions) jointAction->postDynCorrectorIteration();
    ForceTorqueItem::postDynCorrectorIteration();
}

void ForceTorqueFunction::postDynOutput()
{
    for (const auto kineIJ : *kineIJs) kineIJ->postDynOutput();
    for (const auto kinedotIJ : *kinedotIJs) kinedotIJ->postDynOutput();
    for (const auto jointAction : *jointActions) jointAction->postDynOutput();
    ForceTorqueItem::postDynOutput();
}
