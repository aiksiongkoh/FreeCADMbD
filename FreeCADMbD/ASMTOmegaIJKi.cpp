#include "ASMTOmegaIJKi.h"
#include "Units.h"
#include "OmeCompIeqJeqKeq.h"
#include "OmeCompIeJeKe.h"

using namespace MbD;

std::shared_ptr<ASMTOmegaIJKi> ASMTOmegaIJKi::With()
{
    auto inst = std::make_shared<ASMTOmegaIJKi>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIeJe> ASMTOmegaIJKi::mbdClassNew()
{
    return OmeCompIeqJeqKeq::With();
}

std::shared_ptr<KinematicIeJe> ASMTOmegaIJKi::kinematicWith(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    return OmeCompIeJeKe::With(frmi, frmj, frmk, axisk);
}

double ASMTOmegaIJKi::asmtUnit()
{
    return asmtUnits()->omega;
}
