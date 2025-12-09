#include "ASMTSymbolicFunctionIJ.h"
#include "MbDSymbolicFunction.h"
#include "Units.h"
#include "Constant.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunctionIJ> ASMTSymbolicFunctionIJ::With()
{
    auto inst = std::make_shared<ASMTSymbolicFunctionIJ>();
    inst->initialize();
    return inst;
}

ASMTSymbolicFunctionIJ::ASMTSymbolicFunctionIJ(std::shared_ptr<ASMTItemIJ> itemIJ) : geoIJ(itemIJ)
{
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdClassNew()
{
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

void ASMTSymbolicFunctionIJ::withFrmIFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTSymbolicFunctionIJ::createMbD()
{
    auto eFrmI = std::static_pointer_cast<EndFrameqc>(geoIJ->markerI->mbdObject);
    auto eFrmJ = std::static_pointer_cast<EndFrameqc>(geoIJ->markerJ->mbdObject);
    auto kineIJ = mbdClassNew();
    kineIJ->withFrmIFrmJ(eFrmI, eFrmJ);
    auto distIeJe = MbDSymbolicFunction::With(kineIJ);
    expression = Symbolic::times(distIeJe, sptrConstant(asmtUnit()));
    xx = distIeJe;
}

double ASMTSymbolicFunctionIJ::asmtUnit()
{
    throw SimulationStoppingError("To be implemented.");
    return 0.0;
}
