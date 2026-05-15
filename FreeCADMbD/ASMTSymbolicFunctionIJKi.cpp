#include "ASMTSymbolicFunctionIJKi.h"
#include "MbDSymbolicFunction.h"
#include "Constant.h"
#include "SimulationStoppingError.h"
#include "EndFrame.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunctionIJKi> ASMTSymbolicFunctionIJKi::With()
{
    auto inst = std::make_shared<ASMTSymbolicFunctionIJKi>();
    inst->initialize();
    return inst;
}

void ASMTSymbolicFunctionIJKi::createMbD()
{
    auto eFrmI = std::static_pointer_cast<EndFrame>(geoIJ->markerI->mbdObject);
    auto eFrmJ = std::static_pointer_cast<EndFrame>(geoIJ->markerJ->mbdObject);
    assert(eFrmJ->has_qX());
    if (markerKSign == "O") {
        throw SimulationStoppingError("To be implemented.");
    }

    auto eFrmK = markerKSign == "J" ? eFrmJ : eFrmI;
    auto kineIJ = kinematicWith(eFrmI, eFrmJ, eFrmK, axisK);
    auto distIeJe = MbDSymbolicFunction::With(kineIJ);
    expression = Symbolic::times(distIeJe, sptrConstant(asmtUnit()));
    xx = distIeJe;
}

std::shared_ptr<KinematicIeJe> ASMTSymbolicFunctionIJKi::kinematicWith(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    throw SimulationStoppingError("To be implemented.");
}
