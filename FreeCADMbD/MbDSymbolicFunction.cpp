#include <memory>

#include "MbDSymbolicFunction.h"
#include "Constant.h"
#include "KinematicDotIJ.h"
#include "DispCompIecJecKec.h"
#include "KinematicIJ.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MbDSymbolicFunction> MbDSymbolicFunction::With(std::shared_ptr<KinematicIJ> kineIJ)
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

void MbDSymbolicFunction::simUpdateAll()
{
    mbdObject->simUpdateAll();
}

void MbDSymbolicFunction::useEquationNumbers()
{
    mbdObject->useEquationNumbers();
}

FRowDsptr MbDSymbolicFunction::pvaluepEI()
{
    return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepEI();
}

FRowDsptr MbDSymbolicFunction::pvaluepXI()
{
    return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepXI();
}

FRowDsptr MbDSymbolicFunction::pvaluepEJ()
{
    return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepEJ();
}

FRowDsptr MbDSymbolicFunction::pvaluepXJ()
{
    return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepXJ();
}

FRowDsptr MbDSymbolicFunction::pvaluepEK()
{
    return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepEK();
}

FRowDsptr MbDSymbolicFunction::pvaluepXK()
{
    return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepXK();
}

FRowDsptr MbDSymbolicFunction::pvaluepEdotI()
{
    return std::static_pointer_cast<KinematicDotIJ>(mbdObject)->pvaluepEdotI();
}

FRowDsptr MbDSymbolicFunction::pvaluepXdotI()
{
    return std::static_pointer_cast<KinematicDotIJ>(mbdObject)->pvaluepXdotI();
}

FRowDsptr MbDSymbolicFunction::pvaluepEdotJ()
{
    return std::static_pointer_cast<KinematicDotIJ>(mbdObject)->pvaluepEdotJ();
}

FRowDsptr MbDSymbolicFunction::pvaluepXdotJ()
{
    return std::static_pointer_cast<KinematicDotIJ>(mbdObject)->pvaluepXdotJ();
}

FRowDsptr MbDSymbolicFunction::pvaluepEdotK()
{
    return std::static_pointer_cast<KinematicDotIJ>(mbdObject)->pvaluepEdotK();
}

FRowDsptr MbDSymbolicFunction::pvaluepXdotK()
{
    return std::static_pointer_cast<KinematicDotIJ>(mbdObject)->pvaluepXdotK();
}

SpRowDsptr MbDSymbolicFunction::pvalueplam()
{
    throw SimulationStoppingError("To be implemented.");
    return SpRowDsptr();
}

PartFrame* MbDSymbolicFunction::partFrameI()
{
    return std::static_pointer_cast<KinematicIJ>(mbdObject)->partFrameI();
}

PartFrame* MbDSymbolicFunction::partFrameJ()
{
    return std::static_pointer_cast<KinematicIJ>(mbdObject)->partFrameJ();
}

PartFrame* MbDSymbolicFunction::partFrameK()
{
    auto frmIqc = std::dynamic_pointer_cast<DispCompIecJecKec>(mbdObject);
    if (frmIqc) {
        return frmIqc->partFrameK();
    }
    return nullptr;
}
