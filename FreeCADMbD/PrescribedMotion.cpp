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
#include "EndFrameqct.h"
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
    phiBlk = std::make_shared<Constant>(0.0);
    theBlk = std::make_shared<Constant>(0.0);
    psiBlk = std::make_shared<Constant>(0.0);
}

void PrescribedMotion::initMotions()
{
    auto xyzBlkList = std::initializer_list<Symsptr>{ xBlk, yBlk, zBlk };
    std::static_pointer_cast<EndFrameqct>(eFrmI)->rmemBlks = (std::make_shared<FullColumn<Symsptr>>(xyzBlkList));
    auto xyzRotBlkList = std::initializer_list<Symsptr>{ phiBlk, theBlk, psiBlk };
    std::static_pointer_cast<EndFrameqct>(eFrmI)->phiThePsiBlks = (std::make_shared<FullColumn<Symsptr>>(xyzRotBlkList));
}

void PrescribedMotion::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
    ConstraintSet::connectsItoJ(frmi, frmj);
    std::static_pointer_cast<EndFrameqc>(eFrmI)->initEndFrameqct();
}
