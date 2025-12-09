/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineIeqcJec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIeqcJec> DirectionCosineIeqcJec::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
    auto inst = std::make_shared<DirectionCosineIeqcJec>(frmi, frmj, axisi, axisj);
    inst->initialize();
    return inst;
}

void DirectionCosineIeqcJec::initialize()
{
    DirectionCosineIecJec::initialize();
    pAijIeJepEI = FullRow<double>::With(4);
    ppAijIeJepEIpEI = FullMatrix<double>::With(4, 4);
}

void DirectionCosineIeqcJec::initializeGlobally()
{
    ppAjOIepEIpEI = std::static_pointer_cast<EndFrameqc>(eFrmI)->ppAjOepEpE(axisI);
}

FMatDsptr DirectionCosineIeqcJec::ppvaluepEIpEI()
{
    return ppAijIeJepEIpEI;
}

FRowDsptr DirectionCosineIeqcJec::pvaluepEI()
{
    return pAijIeJepEI;
}

void DirectionCosineIeqcJec::calcPostDynCorrectorIteration()
{
    DirectionCosineIecJec::calcPostDynCorrectorIteration();
    pAjOIepEIT = std::static_pointer_cast<EndFrameqc>(eFrmI)->pAjOepET(axisI);
    for (size_t i = 0; i < 4; i++)
    {
        pAijIeJepEI->at(i) = pAjOIepEIT->at(i)->dot(aAjOJe);
    }
    for (size_t i = 0; i < 4; i++)
    {
        auto& ppAijIeJepEIipEI = ppAijIeJepEIpEI->at(i);
        auto& ppAjOIepEIipEI = ppAjOIepEIpEI->at(i);
        for (size_t j = 0; j < 4; j++)
        {
            ppAijIeJepEIipEI->at(j) = ppAjOIepEIipEI->at(j)->dot(aAjOJe);
        }
    }    
    ppAijIeJepEIpEI->symLowerWithUpper();
}
