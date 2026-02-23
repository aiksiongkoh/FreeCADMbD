/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIeqtJeq.h"
#include "DirectionCosineIeqctJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIeqtJeq> DirectionCosineConstraintIeqtJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIeqtJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void MbD::DirectionCosineConstraintIeqtJeq::preAccIC()
{
    DirectionCosineConstraintIeqJeq::preAccIC();
    ppGpEIpt = std::static_pointer_cast<DirectionCosineIeqctJeqc>(aAijIeJe)->ppAijIeJepEIpt;
    ppGpEJpt = std::static_pointer_cast<DirectionCosineIeqctJeqc>(aAijIeJe)->ppAijIeJepEJpt;
    ppGptpt = std::static_pointer_cast<DirectionCosineIeqctJeqc>(aAijIeJe)->ppAijIeJeptpt;
}

void MbD::DirectionCosineConstraintIeqtJeq::preVelIC()
{
    DirectionCosineConstraintIeqJeq::preVelIC();
    pGpt = std::static_pointer_cast<DirectionCosineIeqctJeqc>(aAijIeJe)->pAijIeJept;
}

void DirectionCosineConstraintIeqtJeq::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqctJeqc::With(frmIe, frmJe, axisI, axisJ);
}

void MbD::DirectionCosineConstraintIeqtJeq::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

ConstraintType MbD::DirectionCosineConstraintIeqtJeq::type()
{
    return essential;
}

