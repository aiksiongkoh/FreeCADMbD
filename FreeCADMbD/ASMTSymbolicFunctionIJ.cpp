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

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdClassNew()
{
    //Should not create abstract class.
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIeJeWith(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIqctJqct(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIqctJct(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIqctJc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIqcJqct(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIqcJct(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIqcJc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIctJqct(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIctJct(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIctJc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIcJqct(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIcJct(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJ::mbdKineIcJc(EndFrmsptr frmi, EndFrmsptr frmj)
{
    throw SimulationStoppingError("To be implemented.");
    return std::shared_ptr<KinematicIJ>();
}

void ASMTSymbolicFunctionIJ::withFrmIFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
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
    return 0.0;
}
