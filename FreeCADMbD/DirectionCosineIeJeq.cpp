/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineIeJeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIeJeq> DirectionCosineIeJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineIeJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineIeJeq::initialize()
{
    DirectionCosineIeJe::initialize();
    pAijIeJepEJ = FullRow<double>::With(4);
    ppAijIeJepEJpEJ = FullMatrix<double>::With(4, 4);
}

void DirectionCosineIeJeq::initializeGlobally()
{
    DirectionCosineIeJe::initializeGlobally();
    ppAjOJepEJpEJ = std::static_pointer_cast<EndFrameq>(eFrmJ)->ppAjOepEpE(axisJ);
}

void DirectionCosineIeJeq::simUpdateAll()
{
    //cos(the) = aAijIeJe = aAcoliOIe->dot(aAcoljOJe);
    DirectionCosineIeJe::simUpdateAll();
    pAjOJepEJT = std::static_pointer_cast<EndFrameq>(eFrmJ)->pAjOepET(axisJ);
    for (size_t i = 0; i < 4; i++)
    {
        pAijIeJepEJ->at(i) = aAjOIe->dot(pAjOJepEJT->at(i));
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto ppAijIeJepEJipEJ = ppAijIeJepEJpEJ->at(i);
        auto ppAjOJepEJipEJ = ppAjOJepEJpEJ->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            ppAijIeJepEJipEJ->at(j) = aAjOIe->dot(ppAjOJepEJipEJ->at(j));
        }
    }
    ppAijIeJepEJpEJ->symLowerWithUpper();
}

FRowDsptr DirectionCosineIeJeq::pvaluepEJ()
{
    return pAijIeJepEJ;
}

FMatDsptr DirectionCosineIeJeq::ppvaluepEJpEJ()
{
    return ppAijIeJepEJpEJ;
}
