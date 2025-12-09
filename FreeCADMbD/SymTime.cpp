/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

 //Use SymTime instead of Time since Time.h is too common.
 
#include "SymTime.h"

using namespace MbD;

SymTime::SymTime()
{
	std::string str = "t";
	this->setName(str);
}

void SymTime::initialize()
{
}
