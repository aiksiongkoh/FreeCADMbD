#include "ASMTSymbolicFunctionIJ.h"
#include "MbDSymbolicFunction.h"
#include "Units.h"
#include "Constant.h"
#include "SimulationStoppingError.h"
#include "EndFrameqt.h"
#include "EndFrameq.h"
#include "EndFramet.h"
#include "EndFrame.h"

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

std::shared_ptr<KinematicIeJe> ASMTSymbolicFunctionIJ::mbdClassNew()
{
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
}

std::shared_ptr<KinematicIeJe> MbD::ASMTSymbolicFunctionIJ::mbdKineIeJeWith(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
}

void ASMTSymbolicFunctionIJ::createMbD()
{
    auto eFrmI = std::static_pointer_cast<EndFrame>(geoIJ->markerI->mbdObject);
    auto eFrmJ = std::static_pointer_cast<EndFrame>(geoIJ->markerJ->mbdObject);
    assert(eFrmJ->has_qX());
    auto kineIJ = mbdKineIeJeWith(eFrmI, eFrmJ);
    auto symKineIJ = MbDSymbolicFunction::With(kineIJ);
    expression = Symbolic::times(symKineIJ, sptrConstant(asmtUnit()));
    xx = symKineIJ;
}

double ASMTSymbolicFunctionIJ::asmtUnit()
{
    throw SimulationStoppingError("To be implemented.");
}

void MbD::ASMTSymbolicFunctionIJ::useUniqueDispIeJeO()
{
    xx->useUniqueDispIeJeO();
}

void MbD::ASMTSymbolicFunctionIJ::useUniqueDispIeJeKe()
{
    xx->useUniqueDispIeJeKe();
}
