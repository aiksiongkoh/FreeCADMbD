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
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->postDynPredictor(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->postDynPredictor(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->postDynPredictor(); });
    ForceTorqueItem::postDynPredictor();
}

void ForceTorqueFunction::postInput()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->postInput(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->postInput(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->postInput(); });
    ForceTorqueItem::postInput();
}

void ForceTorqueFunction::postStaticIteration()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->postStaticIteration(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->postStaticIteration(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->postStaticIteration(); });
    ForceTorqueItem::postStaticIteration();
}

void ForceTorqueFunction::preAccIC()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->preAccIC(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->preAccIC(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->preAccIC(); });
    ForceTorqueItem::preAccIC();
}

void ForceTorqueFunction::preDynOutput()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->preDynOutput(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->preDynOutput(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->preDynOutput(); });
    ForceTorqueItem::preDynOutput();
}

void ForceTorqueFunction::preStatic()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->preStatic(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->preStatic(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->preStatic(); });
    ForceTorqueItem::preStatic();
}

void ForceTorqueFunction::simUpdateAll()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->simUpdateAll(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->simUpdateAll(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->simUpdateAll(); });
    ForceTorqueItem::simUpdateAll();
}

FColDsptr ForceTorqueFunction::pFTpkineIJs()
{
    auto pFTpkineIJs = std::make_shared<FullColumn<double>>(pFTpkineIJFuncs->size());
    std::transform(pFTpkineIJFuncs->begin(),
        pFTpkineIJFuncs->end(),
        pFTpkineIJs->begin(),
        [&](auto& pFTpkineIJFunc) { return pFTpkineIJFunc->getValue(); }
    );
    return pFTpkineIJs;
}

FColDsptr ForceTorqueFunction::pFTpkinedotIJs()
{
    auto pFTpkinedotIJs = std::make_shared<FullColumn<double>>(pFTpkinedotIJFuncs->size());
    std::transform(pFTpkinedotIJFuncs->begin(),
        pFTpkinedotIJFuncs->end(),
        pFTpkinedotIJs->begin(),
        [&](auto& pFTpkinedotIJFunc) { return pFTpkinedotIJFunc->getValue(); }
    );
    return pFTpkinedotIJs;
}

FColDsptr ForceTorqueFunction::pFTpJtActs()
{
    auto pFTpJtActs = std::make_shared<FullColumn<double>>(pFTpJtActFuncs->size());
    std::transform(pFTpJtActFuncs->begin(),
        pFTpJtActFuncs->end(),
        pFTpJtActs->begin(),
        [&](auto& pFTpJtActFunc) { return pFTpJtActFunc->getValue(); }
    );
    return pFTpJtActs;
}

double ForceTorqueFunction::forTor()
{
    return forTorFunc->getValue();
}

void ForceTorqueFunction::initializeGlobally()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->initializeGlobally(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->initializeGlobally(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->initializeGlobally(); });
    pFTpkineIJFuncs = std::make_shared<std::vector<Symsptr>>(kineIJs->size());
    std::transform(kineIJs->begin(),
        kineIJs->end(),
        pFTpkineIJFuncs->begin(),
        [&](auto& kineIJ) { return forTorFunc->differentiateWRT(kineIJ)->simplified(); }
    );
    pFTpkinedotIJFuncs = std::make_shared<std::vector<Symsptr>>(kinedotIJs->size());
    std::transform(kinedotIJs->begin(),
        kinedotIJs->end(),
        pFTpkinedotIJFuncs->begin(),
        [&](auto& kinedotIJ) { return forTorFunc->differentiateWRT(kinedotIJ)->simplified(); }
    );
    pFTpJtActFuncs = std::make_shared<std::vector<Symsptr>>(jointActions->size());
    std::transform(jointActions->begin(),
        jointActions->end(),
        pFTpJtActFuncs->begin(),
        [&](auto& jointAction) { return forTorFunc->differentiateWRT(jointAction)->simplified(); }
    );
}

void ForceTorqueFunction::initializeLocally()
{
    //std::cout << *forTorFunc << std::endl;
    forTorFunc->fillKineIJs(kineIJs);
    forTorFunc->fillKinedotIJs(kinedotIJs);
    forTorFunc->fillJointForces(jointActions);
    forTorFunc->fillJointTorques(jointActions);
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->initializeLocally(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->initializeLocally(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->initializeLocally(); });
}

void ForceTorqueFunction::postAccICIteration()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->postAccICIteration(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->postAccICIteration(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->postAccICIteration(); });
    ForceTorqueItem::postAccICIteration();
}

void ForceTorqueFunction::postCollisionCorrectorIteration()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->postCollisionCorrectorIteration(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->postCollisionCorrectorIteration(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->postCollisionCorrectorIteration(); });
    ForceTorqueItem::postCollisionCorrectorIteration();
}

void ForceTorqueFunction::postCollisionPredictor()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->postCollisionPredictor(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->postCollisionPredictor(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->postCollisionPredictor(); });
    ForceTorqueItem::postCollisionPredictor();
}

void ForceTorqueFunction::postDynCorrectorIteration()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->postDynCorrectorIteration(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->postDynCorrectorIteration(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->postDynCorrectorIteration(); });
    ForceTorqueItem::postDynCorrectorIteration();
}

void ForceTorqueFunction::postDynOutput()
{
    std::for_each(kineIJs->begin(), kineIJs->end(), [&](auto kineIJ) { kineIJ->postDynOutput(); });
    std::for_each(kinedotIJs->begin(), kinedotIJs->end(), [&](auto kinedotIJ) { kinedotIJ->postDynOutput(); });
    std::for_each(jointActions->begin(), jointActions->end(), [&](auto jointAction) { jointAction->postDynOutput(); });
    ForceTorqueItem::postDynOutput();
}
