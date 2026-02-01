#include "ASMTSymbolicFunctionIJKi.h"
#include "MbDSymbolicFunction.h"
#include "Constant.h"
#include "SimulationStoppingError.h"
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunctionIJKi> ASMTSymbolicFunctionIJKi::With()
{
    auto inst = std::make_shared<ASMTSymbolicFunctionIJKi>();
    inst->initialize();
    return inst;
}

void ASMTSymbolicFunctionIJKi::createMbD()
{
    auto eFrmI = std::static_pointer_cast<EndFramec>(geoIJ->markerI->mbdObject);
    auto eFrmJ = std::static_pointer_cast<EndFramec>(geoIJ->markerJ->mbdObject);
    assert(eFrmJ->has_qX());
    std::shared_ptr<KinematicIJ> kineIJ;
    if (markerKSign == "O") {
        kineIJ = mbdKineIJaxisWith(eFrmI, eFrmJ, axisK);
    }
    else {
        std::shared_ptr<EndFramec> efrmK;
        if (markerKSign == "J") {
            efrmK = eFrmJ;
        }
        else {
            efrmK = eFrmI;
        }
        kineIJ = mbdKineIJKaxisKWith(eFrmI, eFrmJ, efrmK, axisK);
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

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIJaxisWith(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    std::shared_ptr<KinematicIJ> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            inst = mbdKineIqctJqctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = mbdKineIqctJqcaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            inst = mbdKineIqctJctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = mbdKineIqctJcaxis(frmi, frmj, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameqc>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            inst = mbdKineIqcJqctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = mbdKineIqcJqcaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            inst = mbdKineIqcJctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = mbdKineIqcJcaxis(frmi, frmj, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            inst = mbdKineIctJqctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = mbdKineIctJqcaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            inst = mbdKineIctJctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = mbdKineIctJcaxis(frmi, frmj, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramec>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            inst = mbdKineIcJqctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = mbdKineIcJqcaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            inst = mbdKineIcJctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = mbdKineIcJcaxis(frmi, frmj, axisK);
        }
    }
    assert(inst);
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIJKaxisKWith(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    std::shared_ptr<KinematicIJ> inst;
    if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            inst = mbdKineIqctJqctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = mbdKineIqctJqcKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            inst = mbdKineIqctJctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = mbdKineIqctJcKaxisK(frmi, frmj, efrmK, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameqc>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            inst = mbdKineIqcJqctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = mbdKineIqcJqcKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            inst = mbdKineIqcJctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = mbdKineIqcJcKaxisK(frmi, frmj, efrmK, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            inst = mbdKineIctJqctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = mbdKineIctJqcKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            inst = mbdKineIctJctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = mbdKineIctJcKaxisK(frmi, frmj, efrmK, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramec>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
            inst = mbdKineIcJqctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
            inst = mbdKineIcJqcKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
            inst = mbdKineIcJctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
            inst = mbdKineIcJcKaxisK(frmi, frmj, efrmK, axisK);
        }
    }
    assert(inst);
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqctJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqctJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqctJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqctJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqcJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqcJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqcJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqcJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIctJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIctJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIctJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIctJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIcJqctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIcJqcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIcJctaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIcJcaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqctJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqctJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqctJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqctJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqcJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqcJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIqcJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIctJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIctJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIctJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIctJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIcJqctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIcJqcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIcJctKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIcJcKaxisK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    return std::shared_ptr<KinematicIJ>();
}
