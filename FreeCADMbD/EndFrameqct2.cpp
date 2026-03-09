/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "EndFrameqct2.h"
#include "MarkerFramec.h"
#include "System.h"
#include "Symbolic.h"
#include "SymTime.h"
#include "EulerParameters.h"
#include "EulerAngles.h"
#include "EulerAnglesDot.h"
#include "EulerAnglesDDot.h"

using namespace MbD;

std::shared_ptr<EndFrameqct2> EndFrameqct2::With(const std::string& str)
{
    auto inst = std::make_shared<EndFrameqct2>(str);
    inst->initialize();
    return inst;
}

void EndFrameqct2::initpthe1x2y3zptBlks()
{
    auto mbdTime = root()->time;
    auto eulerAngles = std::static_pointer_cast<EulerAngles<Symsptr>>(the1x2y3zBlks);
    pthe1x2y3zptBlks = eulerAngles->differentiateWRT(mbdTime);
}

void EndFrameqct2::initppthe1x2y3zptptBlks()
{
    auto mbdTime = root()->time;
    auto eulerAnglesDot = std::static_pointer_cast<EulerAnglesDot<Symsptr>>(pthe1x2y3zptBlks);
    ppthe1x2y3zptptBlks = eulerAnglesDot->differentiateWRT(mbdTime);
}

void EndFrameqct2::evalAme()
{
    auto eulerAngles = std::static_pointer_cast<EulerAngles<Symsptr>>(the1x2y3zBlks);
    eulerAngles->calc();
    aAme = eulerAngles->aA;
}

void EndFrameqct2::evalpAmept()
{
    auto eulerAnglesDot = std::static_pointer_cast<EulerAnglesDot<Symsptr>>(pthe1x2y3zptBlks);
    eulerAnglesDot->calc();
    pAmept = eulerAnglesDot->aAdot;

}

void EndFrameqct2::evalppAmeptpt()
{
    auto eulerAnglesDDot = std::static_pointer_cast<EulerAnglesDDot<Symsptr>>(ppthe1x2y3zptptBlks);
    eulerAnglesDDot->calc();
    ppAmeptpt = eulerAnglesDDot->aAddot;
}
