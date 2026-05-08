/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AtPointConstraintIeqtJeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIeqtJeq> AtPointConstraintIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIeqtJeq>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIeqtJeq::simUpdateAll()
{
    AtPointConstraintIeqJeq::simUpdateAll();
    calcppGpEIpEI(); //Now an explicit function of time
}

void AtPointConstraintIeqtJeq::initializeGlobally()
{
    AtPointConstraintIeqJeq::initializeGlobally();
}

ConstraintType AtPointConstraintIeqtJeq::type()
{
    return essential;
}

void AtPointConstraintIeqtJeq::preVelIC()
{
    AtPointConstraintIeqJeq::preVelIC();
    pGpt = dispIeJeO->getpVectorpt()->at(axis);
}

void AtPointConstraintIeqtJeq::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

void AtPointConstraintIeqtJeq::fillAccICIterError(FColDsptr col)
{
    AtPointConstraintIeqJeq::fillAccICIterError(col);
    auto frmIeq = std::static_pointer_cast<EndFrameq>(eFrmI);
    auto qEdotI = frmIeq->qEdot();
    double sum = (ppGpEIpt->timesFullColumn(qEdotI)) * 2.0;
    sum += ppGptpt;
    col->atiplusNumber(iG, sum);
}

void AtPointConstraintIeqtJeq::preAccIC()
{
    AtPointConstraintIeqJeq::preAccIC();
    ppGpEIpt = dispIeJeO->getppVectorpEIpt()->at(axis);
    ppGptpt = dispIeJeO->getppVectorptpt()->at(axis);
}

