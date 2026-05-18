#include <memory>

#include "MbDSymbolicFunction.h"
#include "Constant.h"
#include "KinematicDotIeJe.h"
#include "KinematicIeJe.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MbDSymbolicFunction> MbDSymbolicFunction::With(std::shared_ptr<KinematicIeJe> kineIJ)
{
    auto inst = std::make_shared<MbDSymbolicFunction>(kineIJ);
    inst->initialize();
    return inst;
}

void MbDSymbolicFunction::initialize()
{
    mbdObject->initialize();
}

double MbDSymbolicFunction::getValue()
{
    return mbdObject->value();
}

Symsptr MbDSymbolicFunction::differentiateWRT(Symsptr var)
{
    if (this == var.get()) {
        return Constant::With(1.0);
    }
    else {
        return Constant::With(0.0);
    }
}

void MbDSymbolicFunction::fillKineIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs)
{
    if (!mbdObject->isKineIJ()) return;
    auto it = std::find_if(kineIJs->begin(), kineIJs->end(), [&](auto funcPtr) {return funcPtr.get() == this; });
    if (it == kineIJs->end()) kineIJs->push_back(std::static_pointer_cast<MbDSymbolicFunction>(shared_from_this()));
}

void MbDSymbolicFunction::fillKinedotIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kinedotIJs)
{
    if (!mbdObject->isKinedotIJ()) return;
    auto it = std::find_if(kinedotIJs->begin(), kinedotIJs->end(), [&](auto funcPtr) {return funcPtr.get() == this; });
    if (it == kinedotIJs->end()) kinedotIJs->push_back(std::static_pointer_cast<MbDSymbolicFunction>(shared_from_this()));
}

void MbDSymbolicFunction::fillJointForces(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions)
{
    if (!mbdObject->isJointForce()) return;
    auto it = std::find_if(jointActions->begin(), jointActions->end(), [&](auto funcPtr) {return funcPtr.get() == this; });
    if (it == jointActions->end()) jointActions->push_back(std::static_pointer_cast<MbDSymbolicFunction>(shared_from_this()));
}

void MbDSymbolicFunction::fillJointTorques(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions)
{
    if (!mbdObject->isJointTorque()) return;
    auto it = std::find_if(jointActions->begin(), jointActions->end(), [&](auto funcPtr) {return funcPtr.get() == this; });
    if (it == jointActions->end()) jointActions->push_back(std::static_pointer_cast<MbDSymbolicFunction>(shared_from_this()));
}

void MbDSymbolicFunction::initializeGlobally()
{
    mbdObject->initializeGlobally();
}

void MbDSymbolicFunction::initializeLocally()
{
    mbdObject->initializeLocally();
}

void MbDSymbolicFunction::postAccICIteration()
{
    mbdObject->postAccICIteration();
}

void MbDSymbolicFunction::postCollisionCorrectorIteration()
{
    mbdObject->postCollisionCorrectorIteration();
}

void MbDSymbolicFunction::postCollisionPredictor()
{
    mbdObject->postCollisionPredictor();
}

void MbDSymbolicFunction::postDynCorrectorIteration()
{
    mbdObject->postDynCorrectorIteration();
}

void MbDSymbolicFunction::postDynOutput()
{
    mbdObject->postDynOutput();
}

void MbDSymbolicFunction::postDynPredictor()
{
    mbdObject->postDynPredictor();
}

void MbDSymbolicFunction::postInput()
{
    mbdObject->postInput();
}

void MbDSymbolicFunction::postStaticIteration()
{
    mbdObject->postStaticIteration();
}

void MbDSymbolicFunction::preAccIC()
{
    mbdObject->preAccIC();
}

void MbDSymbolicFunction::preDynOutput()
{
    mbdObject->preDynOutput();
}

void MbDSymbolicFunction::preStatic()
{
    mbdObject->preStatic();
}

void MbDSymbolicFunction::useEquationNumbers()
{
    mbdObject->useEquationNumbers();
}

FRowDsptr MbDSymbolicFunction::pvaluepE(SpatialContainerFrame* partFrame)
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->pvaluepE(partFrame);
}

FRowDsptr MbDSymbolicFunction::pvaluepX(SpatialContainerFrame* partFrame)
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->pvaluepX(partFrame);
}

FRowDsptr MbDSymbolicFunction::pvaluepXdot(SpatialContainerFrame* partFrame)
{
    return std::dynamic_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepXdot(partFrame);
}

FRowDsptr MbDSymbolicFunction::pvaluepEdot(SpatialContainerFrame* partFrame)
{
    return std::dynamic_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepEdot(partFrame);
}

FRowDsptr MbDSymbolicFunction::pvaluepEI()
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->pvaluepEI();
}

FRowDsptr MbDSymbolicFunction::pvaluepXI()
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->pvaluepXI();
}

FRowDsptr MbDSymbolicFunction::pvaluepEJ()
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->pvaluepEJ();
}

FRowDsptr MbDSymbolicFunction::pvaluepXJ()
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->pvaluepXJ();
}

FRowDsptr MbDSymbolicFunction::pvaluepEK()
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->pvaluepEK();
}

FRowDsptr MbDSymbolicFunction::pvaluepXK()
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->pvaluepXK();
}

FRowDsptr MbDSymbolicFunction::pvaluepEdotI()
{
    return std::dynamic_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepEdotI();
}

FRowDsptr MbDSymbolicFunction::pvaluepXdotI()
{
    return std::dynamic_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepXdotI();
}

FRowDsptr MbDSymbolicFunction::pvaluepEdotJ()
{
    return std::dynamic_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepEdotJ();
}

FRowDsptr MbDSymbolicFunction::pvaluepXdotJ()
{
    return std::dynamic_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepXdotJ();
}

FRowDsptr MbDSymbolicFunction::pvaluepEdotK()
{
    return std::dynamic_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepEdotK();
}

FRowDsptr MbDSymbolicFunction::pvaluepXdotK()
{
    return std::dynamic_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepXdotK();
}

SpRowDsptr MbDSymbolicFunction::pvalueplam()
{
    throw SimulationStoppingError("To be implemented.");
    return SpRowDsptr();
}

SpatialContainerFrame* MbDSymbolicFunction::partFrameI()
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->partFrameI();
}

SpatialContainerFrame* MbDSymbolicFunction::partFrameJ()
{
    return std::dynamic_pointer_cast<KinematicIeJe>(mbdObject)->partFrameJ();
}

SpatialContainerFrame* MbDSymbolicFunction::partFrameK()
{
    return nullptr;
}

void MbD::MbDSymbolicFunction::useUniqueDispIeJeO()
{
    mbdObject->useUniqueDispIeJeO();
}

void MbD::MbDSymbolicFunction::useUniqueDispIeJeKe()
{
    mbdObject->useUniqueDispIeJeKe();
}
