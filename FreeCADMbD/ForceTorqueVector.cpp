#include <algorithm>

#include "ForceTorqueVector.h"
#include "ForceTorqueFunction.h"

using namespace MbD;

std::shared_ptr<ForceTorqueVector> ForceTorqueVector::With()
{
    auto inst = std::make_shared<ForceTorqueVector>();
    inst->initialize();
    return inst;
}

FColDsptr ForceTorqueVector::getFTIeO() const
{
    auto aFTIeO = FullColumn<double>::With();
    for (size_t i = 0; i < 3; i++)
    {
        auto compi = components->at(i);
        aFTIeO->equalSelfPlusFullColumnAt(compi->getFTIeO(), i);
    }
    return aFTIeO;
}

void ForceTorqueVector::fillAccICIterError(FColDsptr col)
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->fillAccICIterError(col); });
}

void ForceTorqueVector::fillAccICIterJacob(SpMatDsptr mat)
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->fillAccICIterJacob(mat); });
}

void ForceTorqueVector::fillDynError(FColDsptr col)
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->fillDynError(col); });
}

void ForceTorqueVector::fillpFpy(SpMatDsptr mat)
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->fillpFpy(mat); });
}

void ForceTorqueVector::fillpFpydot(SpMatDsptr mat)
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->fillpFpydot(mat); });
}

void ForceTorqueVector::functions(FColsptr<Symsptr> col)
{
    auto comps = FullColumn<std::shared_ptr<ForceTorqueActReactComp>>::With();
    for (size_t i = 0; i < 3; i++)
    {
        auto compi = components->at(i);
        //compi forTorFunction formula isNil ifFalse : [self error : #'StM: ForceTorque function can only be initialized once.'] .
        auto funci = col->at(i);
        compi->getforTorFunction()->setformula(funci);
        comps->push_back(compi);
    }
    components = comps;
}

void ForceTorqueVector::initializeGlobally()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->initializeGlobally(); });
}

void ForceTorqueVector::initializeLocally()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->initializeLocally(); });
}

void ForceTorqueVector::postAccICIteration()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->postAccICIteration(); });
}

void ForceTorqueVector::postCollisionCorrectorIteration()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->postCollisionCorrectorIteration(); });
}

void ForceTorqueVector::postCollisionPredictor()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->postCollisionPredictor(); });
}

void ForceTorqueVector::postDynCorrectorIteration()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->postDynCorrectorIteration(); });
}

void ForceTorqueVector::postDynOutput()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->postDynOutput(); });
}

void ForceTorqueVector::preAccIC()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->preAccIC(); });
}

void ForceTorqueVector::preDynOutput()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->preDynOutput(); });
}

void ForceTorqueVector::postDynPredictor()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->postDynPredictor(); });
}

void ForceTorqueVector::postInput()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->postInput(); });
}

void ForceTorqueVector::preStatic()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->preStatic(); });
}

void ForceTorqueVector::simUpdateAll()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->simUpdateAll(); });
}

void ForceTorqueVector::useEquationNumbers()
{
    std::for_each(components->begin(), components->end(), [&](auto component) { component->useEquationNumbers(); });
}
