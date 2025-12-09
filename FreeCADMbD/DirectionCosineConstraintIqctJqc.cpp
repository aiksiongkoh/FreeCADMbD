/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIqctJqc.h"
#include "DirectionCosineIeqctJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIqctJqc> DirectionCosineConstraintIqctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineConstraintIqctJqc>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineConstraintIqctJqc::initaAijIeJe()
{
    aAijIeJe = DirectionCosineIeqctJeqc::With(eFrmI, eFrmJ, axisI, axisJ);
}

ConstraintType DirectionCosineConstraintIqctJqc::type()
{
    return essential;
}

void DirectionCosineConstraintIqctJqc::preVelIC()
{
    DirectionCosineConstraintIJ::preVelIC();
    pGpt = std::static_pointer_cast<DirectionCosineIeqctJeqc>(aAijIeJe)->pAijIeJept;
}

void DirectionCosineConstraintIqctJqc::fillVelICError(FColDsptr col)
{
    col->atiminusNumber(iG, pGpt);
}

void DirectionCosineConstraintIqctJqc::preAccIC()
{
    DirectionCosineConstraintIJ::preAccIC();
    ppGpEIpt = std::static_pointer_cast<DirectionCosineIeqctJeqc>(aAijIeJe)->ppAijIeJepEIpt;
    ppGpEJpt = std::static_pointer_cast<DirectionCosineIeqctJeqc>(aAijIeJe)->ppAijIeJepEJpt;
    ppGptpt = std::static_pointer_cast<DirectionCosineIeqctJeqc>(aAijIeJe)->ppAijIeJeptpt;
}

void DirectionCosineConstraintIqctJqc::fillAccICIterError(FColDsptr col)
{
    DirectionCosineConstraintIqcJqc::fillAccICIterError(col);
    auto eFrmIqc = std::static_pointer_cast<EndFrameqc>(eFrmI);
    auto eFrmJqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto qEdotI = eFrmIqc->qEdot();
    auto qEdotJ = eFrmJqc->qEdot();
    double sum = (ppGpEIpt->timesFullColumn(qEdotI)) * 2.0;
    sum += (ppGpEJpt->timesFullColumn(qEdotJ)) * 2.0;
    sum += ppGptpt;
    col->atiplusNumber(iG, sum);
}
