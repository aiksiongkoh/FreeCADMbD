/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <algorithm>

#include "AssemblyFrame.h"
#include "Part.h"
#include "EulerConstraint.h"
#include "MarkerFrame.h"
#include "EulerParameters.h"
#include "EulerParametersDot.h"
#include "RedundantConstraint.h"
#include "System.h"

using namespace MbD;

AssemblyFrame::AssemblyFrame(const std::string &str) : SpatialContainerFrame(str)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<AssemblyFrame> AssemblyFrame::With()
{
    auto inst = std::make_shared<AssemblyFrame>();
    inst->initialize();
    return inst;
}

std::shared_ptr<AssemblyFrame> AssemblyFrame::With(const std::string &str)
{
    auto inst = std::make_shared<AssemblyFrame>(str);
    inst->initialize();
    return inst;
}

MkrFrmsptr AssemblyFrame::createMarkerFrame(const std::string &str)
{
    return MarkerFrame::With(str);
}

System *AssemblyFrame::root()
{
    return assembly->root();
}

void AssemblyFrame::setAssembly(System *x)
{
    assembly = x;
}

System *AssemblyFrame::getAssembly() const
{
    return assembly;
}

void AssemblyFrame::setPart(Part *x)
{
    // Do nothing.
}

FColFMatDsptr AssemblyFrame::pAOppE()
{
    auto eulerParameters = EulerParameters<double>::With(ListD{0.0, 0.0, 0.0, 1.0});
    eulerParameters->calcpApE();
    return eulerParameters->pApE;
}

void AssemblyFrame::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos)
{
    // Do nothing.
}

void AssemblyFrame::reactivateRedundantConstraints()
{
    // Do nothing.
}

void AssemblyFrame::constraintsReport()
{
    // Do nothing.
}

void AssemblyFrame::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
    // Do nothing.
}

void AssemblyFrame::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
    // Do nothing.
}

void AssemblyFrame::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints)
{
    // Do nothing.
}

void AssemblyFrame::simUpdateAll()
{
    // Do nothing.
}
