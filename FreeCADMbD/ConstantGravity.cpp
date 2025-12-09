/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ConstantGravity.h"
#include "System.h"
#include "Part.h"

using namespace MbD;

std::shared_ptr<ConstantGravity> ConstantGravity::With()
{
    auto inst = std::make_shared<ConstantGravity>();
    inst->initialize();
    return inst;
}

void ConstantGravity::fillAccICIterError(FColDsptr col)
{
    fillDynError(col);
}

void ConstantGravity::fillDynError(FColDsptr col)
{
    for (auto& part : *(root()->parts)) {
        col->atiplusFullColumntimes(part->iqX(), gXYZ, part->m);
    }
}

void ConstantGravity::fillStaticError(FColDsptr col)
{
    fillDynError(col);
}

void ConstantGravity::postAccICIteration()
{
    //Do nothing.
}

void ConstantGravity::postDynCorrectorIteration()
{
    //Do nothing.
}

void ConstantGravity::preDynOutput()
{
    //Do nothing.
}

void ConstantGravity::postDynPredictor()
{
    //Do nothing.
}

void ConstantGravity::postInput()
{
    //Do nothing.
}

void ConstantGravity::postStaticIteration()
{
    //Do nothing.
}

void ConstantGravity::preAccIC()
{
    //Do nothing.
}

void ConstantGravity::postDynOutput()
{
    //Do nothing.
}

void ConstantGravity::preStatic()
{
    //Do nothing.
}

void ConstantGravity::simUpdateAll()
{
    //Do nothing.
}
