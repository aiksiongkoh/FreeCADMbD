/***************************************************************************
 *   Copyright (c) 2026 ASKOH.COM LLC.                                     *
 *                                                                         *
 *   This file is part of FreeCADMbD.                                      *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "KinematicCompiIeJe.h"
#include "KinematicVectorIeJe.h"
#include "SpatialContainerFrame.h"

using namespace MbD;

void KinematicCompiIeJe::useUniqueDispIeJeO()
{
    kineVector()->useUniqueDispIeJeO();
}

void KinematicCompiIeJe::simUpdateAll()
{
    // Do nothing.
    // dispIeJeO, dispIeJeKe are already updated by Assembly.
}

FRowDsptr KinematicCompiIeJe::pvaluepXI()
{
    return componentRowFrom(kineVector()->getpVectorpXI());
}

FRowDsptr KinematicCompiIeJe::pvaluepEI()
{
    return componentRowFrom(kineVector()->getpVectorpEI());
}

FMatDsptr KinematicCompiIeJe::ppvaluepXIpXI()
{
    return componentMatrixFrom(kineVector()->getppVectorpXIpXI());
}

FMatDsptr KinematicCompiIeJe::ppvaluepXIpEI()
{
    return componentMatrixFrom(kineVector()->getppVectorpXIpEI());
}

FMatDsptr KinematicCompiIeJe::ppvaluepEIpEI()
{
    return componentMatrixFrom(kineVector()->getppVectorpEIpEI());
}

FRowDsptr KinematicCompiIeJe::pvaluepXJ()
{
    return componentRowFrom(kineVector()->getpVectorpXJ());
}

FRowDsptr KinematicCompiIeJe::pvaluepEJ()
{
    return componentRowFrom(kineVector()->getpVectorpEJ());
}

FMatDsptr KinematicCompiIeJe::ppvaluepXIpXJ()
{
    return componentMatrixFrom(kineVector()->getppVectorpXIpXJ());
}

FMatDsptr KinematicCompiIeJe::ppvaluepXIpEJ()
{
    return componentMatrixFrom(kineVector()->getppVectorpXIpEJ());
}

FMatDsptr KinematicCompiIeJe::ppvaluepEIpXJ()
{
    return componentMatrixFrom(kineVector()->getppVectorpEIpXJ());
}

FMatDsptr KinematicCompiIeJe::ppvaluepEIpEJ()
{
    return componentMatrixFrom(kineVector()->getppVectorpEIpEJ());
}

FMatDsptr KinematicCompiIeJe::ppvaluepXJpXJ()
{
    return componentMatrixFrom(kineVector()->getppVectorpXJpXJ());
}

FMatDsptr KinematicCompiIeJe::ppvaluepXJpEJ()
{
    return componentMatrixFrom(kineVector()->getppVectorpXJpEJ());
}

FMatDsptr KinematicCompiIeJe::ppvaluepEJpEJ()
{
    return componentMatrixFrom(kineVector()->getppVectorpEJpEJ());
}

FRowDsptr KinematicCompiIeJe::pvaluepEK()
{
    return componentRowFrom(kineVector()->getpVectorpEK());
}

FMatDsptr KinematicCompiIeJe::ppvaluepXIpEK()
{
    return componentMatrixFrom(kineVector()->getppVectorpXIpEK());
}

FMatDsptr KinematicCompiIeJe::ppvaluepEIpEK()
{
    return componentMatrixFrom(kineVector()->getppVectorpEIpEK());
}

FMatDsptr KinematicCompiIeJe::ppvaluepXJpEK()
{
    return componentMatrixFrom(kineVector()->getppVectorpXJpEK());
}

FMatDsptr KinematicCompiIeJe::ppvaluepEJpEK()
{
    return componentMatrixFrom(kineVector()->getppVectorpEJpEK());
}

FMatDsptr KinematicCompiIeJe::ppvaluepEKpEK()
{
    return componentMatrixFrom(kineVector()->getppVectorpEKpEK());
}

double KinematicCompiIeJe::pvaluept()
{
    return componentFrom(kineVector()->getpVectorpt());
}

double KinematicCompiIeJe::ppvalueptpt()
{
    return componentFrom(kineVector()->getppVectorptpt());
}

FRowDsptr KinematicCompiIeJe::ppvaluepXIpt()
{
    return componentRowFrom(kineVector()->getppVectorpXIpt());
}

FRowDsptr KinematicCompiIeJe::ppvaluepEIpt()
{
    return componentRowFrom(kineVector()->getppVectorpEIpt());
}

FRowDsptr KinematicCompiIeJe::ppvaluepXJpt()
{
    return componentRowFrom(kineVector()->getppVectorpXJpt());
}

FRowDsptr KinematicCompiIeJe::ppvaluepEJpt()
{
    return componentRowFrom(kineVector()->getppVectorpEJpt());
}

FRowDsptr KinematicCompiIeJe::ppvaluepEKpt()
{
    return componentRowFrom(kineVector()->getppVectorpEKpt());
}

double KinematicCompiIeJe::value()
{
    return componentFrom(currentVector());
}

double KinematicCompiIeJe::componentFrom(FColDsptr col) const
{
    return col->at(axis);
}

FRowDsptr KinematicCompiIeJe::componentRowFrom(FMatDsptr mat) const
{
    return mat->at(axis)->copy();
}

FMatDsptr KinematicCompiIeJe::componentMatrixFrom(FMatFColDsptr mat) const
{
    auto m = mat->nrow();
    auto n = mat->ncol();
    auto answer = FullMatrix<double>::With(m, n);
    for (size_t i = 0; i < m; i++)
    {
        auto answeri = answer->at(i);
        auto mati = mat->at(i);
        for (size_t j = 0; j < n; j++)
        {
            answeri->at(j) = mati->at(j)->at(axis);
        }
    }
    return answer;
}
