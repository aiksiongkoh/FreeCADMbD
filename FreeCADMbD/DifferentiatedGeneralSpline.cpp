/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DifferentiatedGeneralSpline.h"
#include "GeneralSpline.h"
#include "SimulationStoppingError.h"

using namespace MbD;

DifferentiatedGeneralSpline::DifferentiatedGeneralSpline(Symsptr arg, Symsptr spline, size_t derivOrder) : AnyGeneralSpline(arg), generalSpline(spline), derivativeOrder(derivOrder)
{
}

DifferentiatedGeneralSpline::DifferentiatedGeneralSpline(Symsptr arg) : AnyGeneralSpline(arg)
{
}

std::shared_ptr<DifferentiatedGeneralSpline> DifferentiatedGeneralSpline::With()
{
    auto inst = std::make_shared<DifferentiatedGeneralSpline>();
    inst->initialize();
    return inst;
}

std::shared_ptr<DifferentiatedGeneralSpline> MbD::DifferentiatedGeneralSpline::With(Symsptr arg)
{
    auto inst = std::make_shared<DifferentiatedGeneralSpline>(arg);
    inst->initialize();
    return inst;
}

std::shared_ptr<DifferentiatedGeneralSpline> MbD::DifferentiatedGeneralSpline::With(Symsptr arg, Symsptr spline, size_t derivOrder)
{
    auto inst = std::make_shared<DifferentiatedGeneralSpline>(arg, spline, derivOrder);
    inst->initialize();
    return inst;
}

double DifferentiatedGeneralSpline::getValue()
{
    return std::static_pointer_cast<GeneralSpline>(generalSpline)->derivativeAt(derivativeOrder, xx->getValue());
}

Symsptr DifferentiatedGeneralSpline::differentiateWRTx()
{
    auto arg = std::static_pointer_cast<GeneralSpline>(generalSpline)->xx;
    auto deriv = std::make_shared<DifferentiatedGeneralSpline>(arg, generalSpline, derivativeOrder + 1);
    return deriv;
}

Symsptr DifferentiatedGeneralSpline::clonesptr()
{
    return std::make_shared<DifferentiatedGeneralSpline>(*this);
}

std::ostream& DifferentiatedGeneralSpline::printOn(std::ostream& s) const
{
    s << "deriv(" << *generalSpline << ", " << derivativeOrder << ")";
    return s;
}

Symsptr DifferentiatedGeneralSpline::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
    return sptr;
}

Symsptr DifferentiatedGeneralSpline::simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
    return sptr;
}
