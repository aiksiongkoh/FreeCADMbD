/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AtPointConstraintIetJeq.h"
#include "DispCompIectJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIetJeq> AtPointConstraintIetJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
    auto inst = std::make_shared<AtPointConstraintIetJeq>(frmi, frmj, axisO);
    inst->initialize();
    return inst;
}

void AtPointConstraintIetJeq::initializeGlobally()
{
    AtPointConstraintIeJeq::initializeGlobally();
}

ConstraintType AtPointConstraintIetJeq::type()
{
    return essential;
}

void AtPointConstraintIetJeq::preVelIC()
{
    AtPointConstraintIeJeq::preVelIC();
    pGpt = dispIeJeO->getprIeJeOpt()->at(axis);
}

void AtPointConstraintIetJeq::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

void AtPointConstraintIetJeq::fillAccICIterError(FColDsptr col)
{
    AtPointConstraintIeJeq::fillAccICIterError(col);
    double sum = ppGptpt;
    col->atiplusNumber(iG, sum);
}

void AtPointConstraintIetJeq::preAccIC()
{
    AtPointConstraintIeJeq::preAccIC();
    ppGptpt = dispIeJeO->getpprIeJeOptpt()->at(axis);
}
