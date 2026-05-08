#include "ASMTOmegaIJKi.h"
#include "Units.h"
#include "OmeCompIeqJeqKeq.h"
#include "OmeCompIeJeqKe.h"

using namespace MbD;

std::shared_ptr<ASMTOmegaIJKi> ASMTOmegaIJKi::With()
{
    auto inst = std::make_shared<ASMTOmegaIJKi>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTOmegaIJKi::mbdClassNew()
{
    return OmeCompIeqJeqKeq::With();
}

std::shared_ptr<KinematicIJ> ASMTOmegaIJKi::mbdKineIqcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return OmeCompIeqJeqKeq::With(frmi, frmj, efrmK, axisK);
}

std::shared_ptr<KinematicIJ> ASMTOmegaIJKi::mbdKineIcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return OmeCompIeJeqKe::With(frmi, frmj, efrmK, axisK);
}

double ASMTOmegaIJKi::asmtUnit()
{
    return asmtUnits()->omega;
}
