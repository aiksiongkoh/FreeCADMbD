#include "ASMTvrIJ.h"
#include "Units.h"
#include "VelRadIeqtJeq.h"
#include "VelRadIeqJeq.h"
#include "VelRadIetJeq.h"
#include "VelRadIeJeq.h"

using namespace MbD;

std::shared_ptr<ASMTvrIJ> ASMTvrIJ::With()
{
    auto inst = std::make_shared<ASMTvrIJ>();
    inst->initialize();
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTvrIJ::mbdClassNew()
{
    return VelRadIeqJeq::With();
}

std::shared_ptr<KinematicIJ> ASMTvrIJ::mbdKineIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    return VelRadIeqtJeq::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> ASMTvrIJ::mbdKineIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    return VelRadIeqJeq::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> ASMTvrIJ::mbdKineIctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    return VelRadIetJeq::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> ASMTvrIJ::mbdKineIcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    return VelRadIeJeq::With(frmi, frmj);
}

double ASMTvrIJ::asmtUnit()
{
    return asmtUnits()->velocity;
}
