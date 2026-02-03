/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineIecJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIecJeqc> DirectionCosineIecJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineIecJeqc>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineIecJeqc::initialize()
{
    DirectionCosineIecJec::initialize();
    pAijIeJepEJ = FullRow<double>::With(4);
    ppAijIeJepEJpEJ = FullMatrix<double>::With(4, 4);
}

void DirectionCosineIecJeqc::initializeGlobally()
{
    DirectionCosineIecJec::initializeGlobally();
    ppAjOJepEJpEJ = std::static_pointer_cast<EndFrameqc>(eFrmJ)->ppAjOepEpE(axisJ);
}

void DirectionCosineIecJeqc::simUpdateAll()
{
    //cos(the) = aAijIeJe = aAcoliOIe->dot(aAcoljOJe);
    DirectionCosineIecJec::simUpdateAll();
    pAjOJepEJT = std::static_pointer_cast<EndFrameqc>(eFrmJ)->pAjOepET(axisJ);
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

FRowDsptr DirectionCosineIecJeqc::pvaluepEJ()
{
    return pAijIeJepEJ;
}

FMatDsptr DirectionCosineIecJeqc::ppvaluepEJpEJ()
{
    return ppAijIeJepEJpEJ;
}
