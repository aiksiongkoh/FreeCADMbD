/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Cosine.h"
#include "Sine.h"
#include "Negative.h"

using namespace MbD;

std::shared_ptr<Cosine> Cosine::With()
{
    auto inst = std::make_shared<Cosine>();
    inst->initialize();
    return inst;
}

std::shared_ptr<Cosine> Cosine::With(Symsptr arg)
{
    auto inst = std::make_shared<Cosine>(arg);
    inst->initialize();
    return inst;
}

double Cosine::getValue()
{
    return std::cos(xx->getValue());
}

Symsptr Cosine::differentiateWRTx()
{
    return Negative::With(std::make_shared<Sine>(xx));
}

Symsptr Cosine::copyWith(Symsptr arg)
{
    return Cosine::With(arg);
}

Symsptr Cosine::clonesptr()
{
    return std::make_shared<Cosine>(*this);
}

Symsptr Cosine::integrateWRTx()
{
    auto sine = std::make_shared<Sine>(xx);
    return Negative::With(sine);

}

std::ostream& Cosine::printOn(std::ostream& s) const
{
    s << "cos(" << *xx << ")";
    return s;
}
