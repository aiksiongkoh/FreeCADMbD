#include "ASMTrIJ.h"
#include "Units.h"
#include "DistIeJe.h"

using namespace MbD;

std::shared_ptr<ASMTrIJ> ASMTrIJ::With()
{
    auto inst = std::make_shared<ASMTrIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIeJe> MbD::ASMTrIJ::mbdKineIeJeWith(EndFrmsptr frmi, EndFrmsptr frmj)
{
    return DistIeJe::With(frmi, frmj);
}

double ASMTrIJ::asmtUnit()
{
    return asmtUnits()->length;
}
