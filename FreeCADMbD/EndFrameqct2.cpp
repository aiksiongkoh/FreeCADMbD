/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "EndFrameqct2.h"
#include "MarkerFrame.h"
#include "System.h"
#include "Symbolic.h"
#include "SymTime.h"
#include "EulerParameters.h"
#include "EulerAngleszxz.h"
#include "EulerAngleszxzDot.h"
#include "EulerAngleszxzDDot.h"

using namespace MbD;

std::shared_ptr<EndFrameqct2> EndFrameqct2::With(const std::string& str)
{
    auto inst = std::make_shared<EndFrameqct2>(str);
    inst->initialize();
    return inst;
}

void EndFrameqct2::initpPhiThePsiptBlks()
{
    auto& mbdTime = root()->time;
    auto eulerAngles = std::static_pointer_cast<EulerAngles<Symsptr>>(phiThePsiBlks);
    pPhiThePsiptBlks = eulerAngles->differentiateWRT(mbdTime);
}

void EndFrameqct2::initppPhiThePsiptptBlks()
{
    auto& mbdTime = root()->time;
    auto eulerAnglesDot = std::static_pointer_cast<EulerAnglesDot<Symsptr>>(pPhiThePsiptBlks);
    ppPhiThePsiptptBlks = eulerAnglesDot->differentiateWRT(mbdTime);
}

void EndFrameqct2::evalAme()
{
    auto eulerAngles = std::static_pointer_cast<EulerAngles<Symsptr>>(phiThePsiBlks);
    eulerAngles->calc();
    aAme = eulerAngles->aA;
}

void EndFrameqct2::evalpAmept()
{
    auto eulerAnglesDot = std::static_pointer_cast<EulerAnglesDot<Symsptr>>(pPhiThePsiptBlks);
    eulerAnglesDot->calc();
    pAmept = eulerAnglesDot->aAdot;

}

void EndFrameqct2::evalppAmeptpt()
{
    auto eulerAnglesDDot = std::static_pointer_cast<EulerAnglesDDot<Symsptr>>(ppPhiThePsiptptBlks);
    eulerAnglesDDot->calc();
    ppAmeptpt = eulerAnglesDDot->aAddot;
}
