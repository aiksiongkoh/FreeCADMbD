#include "ASMTSymbolicFunctionIJKi.h"
#include "MbDSymbolicFunction.h"
#include "Constant.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunctionIJKi> ASMTSymbolicFunctionIJKi::With()
{
    auto inst = std::make_shared<ASMTSymbolicFunctionIJKi>();
    inst->initialize();
    return inst;
}

void ASMTSymbolicFunctionIJKi::createMbD()
{
    auto eFrmI = std::static_pointer_cast<EndFrameqc>(geoIJ->markerI->mbdObject);
    auto eFrmJ = std::static_pointer_cast<EndFrameqc>(geoIJ->markerJ->mbdObject);
    std::shared_ptr<KinematicIJ> kineIJ;
    if (markerKSign == "O") {
        kineIJ = mbdClassNew();
        kineIJ->withFrmIFrmJaxis(eFrmI, eFrmJ, axisK);
    }
    else {
        std::shared_ptr<EndFrameqc> efrmK;
        if (markerKSign == "J") {
            efrmK = eFrmJ;
        }
        else {
            efrmK = eFrmI;
        }
        kineIJ = mbdClassNew();
        kineIJ->withFrmIFrmJFrmKaxis(eFrmI, eFrmJ, efrmK, axisK);
    }
    auto distIeJe = MbDSymbolicFunction::With(kineIJ);
    expression = Symbolic::times(distIeJe, sptrConstant(asmtUnit()));
    xx = distIeJe;
}

void ASMTSymbolicFunctionIJKi::withFrmIFrmJaxis(EndFrmsptr eFrmi, EndFrmsptr eFrmj, size_t axis)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTSymbolicFunctionIJKi::withFrmIFrmJfrmK(EndFrmsptr eFrmi, EndFrmsptr eFrmj, EndFrmsptr eFrmK)
{
    throw SimulationStoppingError("To be implemented.");
}
