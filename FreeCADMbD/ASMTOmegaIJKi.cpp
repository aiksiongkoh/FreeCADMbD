#include "ASMTOmegaIJKi.h"
#include "Units.h"
#include "OmeCompIeqcJeqcKeqc.h"
#include "OmeCompIecJeqcKec.h"

using namespace MbD;

std::shared_ptr<ASMTOmegaIJKi> ASMTOmegaIJKi::With()
{
    auto inst = std::make_shared<ASMTOmegaIJKi>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTOmegaIJKi::mbdClassNew()
{
    return OmeCompIeqcJeqcKeqc::With();
}

std::shared_ptr<KinematicIJ> ASMTOmegaIJKi::mbdKineIqcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return OmeCompIeqcJeqcKeqc::With(frmi, frmj, efrmK, axisK);
}

std::shared_ptr<KinematicIJ> ASMTOmegaIJKi::mbdKineIcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return OmeCompIecJeqcKec::With(frmi, frmj, efrmK, axisK);
}

double ASMTOmegaIJKi::asmtUnit()
{
    return asmtUnits()->omega;
}
