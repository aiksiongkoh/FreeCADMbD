/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <iostream>    
#include <memory>
#include <typeinfo>
#include <assert.h>

#include "PrescribedMotion.h"
#include "EndFramet.h"
#include "EndFrameqt.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<PrescribedMotion> PrescribedMotion::With(const std::string& str)
{
    auto inst = std::make_shared<PrescribedMotion>(str);
    inst->initialize();
    return inst;
}

void PrescribedMotion::initialize()
{
    ConstraintSet::initialize();
    xBlk = std::make_shared<Constant>(0.0);
    yBlk = std::make_shared<Constant>(0.0);
    zBlk = std::make_shared<Constant>(0.0);
    the1xBlk = std::make_shared<Constant>(0.0);
    the2yBlk = std::make_shared<Constant>(0.0);
    the3zBlk = std::make_shared<Constant>(0.0);
}

void PrescribedMotion::initMotions()
{
    auto xyzBlkList = std::initializer_list<Symsptr>{ xBlk, yBlk, zBlk };
    auto xyzRotBlkList = std::initializer_list<Symsptr>{ the1xBlk, the2yBlk, the3zBlk };

    auto eFrmIet = std::dynamic_pointer_cast<EndFramet>(eFrmI);
    auto eFrmIeqt = std::dynamic_pointer_cast<EndFrameqt>(eFrmI);
    if (eFrmIet && !eFrmIeqt) {
        eFrmIet->rmemBlks = (std::make_shared<FullColumn<Symsptr>>(xyzBlkList));
        eFrmIet->the1x2y3zBlks = (std::make_shared<FullColumn<Symsptr>>(xyzRotBlkList));
    }
    else if (!eFrmIet && eFrmIeqt) {
        eFrmIeqt->rmemBlks = (std::make_shared<FullColumn<Symsptr>>(xyzBlkList));
        eFrmIeqt->the1x2y3zBlks = (std::make_shared<FullColumn<Symsptr>>(xyzRotBlkList));
    }
}

void PrescribedMotion::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    ConstraintSet::connectsItoJ(frmi, frmj);
    eFrmI->initEndFrameqt();
}
