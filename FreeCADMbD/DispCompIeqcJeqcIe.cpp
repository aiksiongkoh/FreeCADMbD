/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIeqcJeqcIe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIeqcJeqcIe> DispCompIeqcJeqcIe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
    auto inst = std::make_shared<DispCompIeqcJeqcIe>(frmi, frmj, axis);
    inst->initialize();
    return inst;
}

void DispCompIeqcJeqcIe::initialize()
{
    DispCompIeqcJecIe::initialize();
    priIeJeIepXJ = FullRow<double>::With(3);
    priIeJeIepEJ = FullRow<double>::With(4);
    ppriIeJeIepEIpXJ = FullMatrix<double>::With(4, 3);
    ppriIeJeIepEIpEJ = FullMatrix<double>::With(4, 4);
    ppriIeJeIepEJpEJ = FullMatrix<double>::With(4, 4);
}

void DispCompIeqcJeqcIe::calc_ppvaluepEIpEJ()
{
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto& prIeJeOpEJ = frmJeqc->prOeOpE;
    ppriIeJeIepEIpEJ = pAjOIepEIT->timesFullMatrix(prIeJeOpEJ);
}

void DispCompIeqcJeqcIe::calc_ppvaluepEIpXJ()
{
    ppriIeJeIepEIpXJ = pAjOIepEIT;
}

void DispCompIeqcJeqcIe::calc_ppvaluepEJpEJ()
{
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto pprIeJeOpEJpEJ = frmJeqc->pprOeOpEpE;
    for (size_t i = 0; i < 4; i++)
    {
        auto pprIeJeOpEJipEJ = pprIeJeOpEJpEJ->at(i);
        auto ppriIeJeIepEJipEJ = ppriIeJeIepEJpEJ->at(i);
        for (size_t j = i; j < 4; j++)
        {
            auto term1 = aAjOIe->dot(pprIeJeOpEJipEJ->at(j));
            ppriIeJeIepEJipEJ->atiput(j, term1);
        }
    }
    ppriIeJeIepEJpEJ->symLowerWithUpper();
}

void DispCompIeqcJeqcIe::calc_pvaluepEJ()
{
    auto frmJeqc = std::static_pointer_cast<EndFrameqc>(eFrmJ);
    auto prIeJeOpEJT = frmJeqc->prOeOpE->transpose();
    for (size_t i = 0; i < 4; i++)
    {
        priIeJeIepEJ->atiput(i, aAjOIe->dot(prIeJeOpEJT->at(i)));
    }
}

void DispCompIeqcJeqcIe::calc_pvaluepXJ()
{
    for (size_t i = 0; i < 3; i++)
    {
        priIeJeIepXJ->atiput(i, aAjOIe->at(i));
    }
}

void DispCompIeqcJeqcIe::calcPostDynCorrectorIteration()
{
    //Must maintain order of calc_xxx.
    DispCompIeqcJecIe::calcPostDynCorrectorIteration();
    calc_pvaluepXJ();
    calc_pvaluepEJ();
    calc_ppvaluepEIpXJ();
    calc_ppvaluepEIpEJ();
    calc_ppvaluepEJpEJ();

}

FMatDsptr DispCompIeqcJeqcIe::ppvaluepEIpEJ()
{
    return ppriIeJeIepEIpEJ;
}

FMatDsptr DispCompIeqcJeqcIe::ppvaluepEIpXJ()
{
    return ppriIeJeIepEIpXJ;
}

FMatDsptr DispCompIeqcJeqcIe::ppvaluepEJpEJ()
{
    return ppriIeJeIepEJpEJ;
}

FRowDsptr DispCompIeqcJeqcIe::pvaluepEJ()
{
    return priIeJeIepEJ;
}

FRowDsptr DispCompIeqcJeqcIe::pvaluepXJ()
{
    return priIeJeIepXJ;
}
