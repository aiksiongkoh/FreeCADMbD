/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineIeqJeq.h"
#include "EndFrameq.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIeqJeq> DirectionCosineIeqJeq::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineIeqJeq>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineIeqJeq::initialize()
{
    DirectionCosineIeqJe::initialize();
    pAijIeJepEJ = FullRow<double>::With(4);
    ppAijIeJepEIpEJ = FullMatrix<double>::With(4, 4);
    ppAijIeJepEJpEJ = FullMatrix<double>::With(4, 4);
}

void DirectionCosineIeqJeq::initializeGlobally()
{
    DirectionCosineIeqJe::initializeGlobally();
    ppAjOJepEJpEJ = std::static_pointer_cast<EndFrameq>(eFrmJ)->ppAjOepEpE(axisJ);
}

FMatDsptr DirectionCosineIeqJeq::ppvaluepEIpEJ()
{
    return ppAijIeJepEIpEJ;
}

void DirectionCosineIeqJeq::simUpdateAll()
{
    //cos(the) = aAijIeJe = aAcoliOIe->dot(aAcoljOJe);
    DirectionCosineIeqJe::simUpdateAll();
    pAjOJepEJT = std::static_pointer_cast<EndFrameq>(eFrmJ)->pAjOepET(axisJ);
    for (size_t i = 0; i < 4; i++)
    {
        pAijIeJepEJ->at(i) = aAjOIe->dot(pAjOJepEJT->at(i));
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto ppAijIeJepEIipEJ = ppAijIeJepEIpEJ->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            ppAijIeJepEIipEJ->at(j) = pAjOIepEIT->at(i)->dot(pAjOJepEJT->at(j));
        }
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

FRowDsptr DirectionCosineIeqJeq::pvaluepEJ()
{
    return pAijIeJepEJ;
}

FMatDsptr DirectionCosineIeqJeq::ppvaluepEJpEJ()
{
    return ppAijIeJepEJpEJ;
}
