#include "ASMTSymbolicFunctionIJKi.h"
#include "MbDSymbolicFunction.h"
#include "Constant.h"
#include "SimulationStoppingError.h"
#include "EndFrameqt.h"
#include "EndFrameq.h"
#include "EndFramet.h"
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
    std::shared_ptr<KinematicIJ> kineIJ;
    if (markerKSign == "O") {
        kineIJ = mbdKineIJaxisWith(eFrmI, eFrmJ, axisK);
    }
    else {
        std::shared_ptr<EndFrame> efrmK;
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
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            inst = mbdKineIqctJqctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = mbdKineIqctJqcaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            inst = mbdKineIqctJctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = mbdKineIqctJcaxis(frmi, frmj, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameq>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            inst = mbdKineIqcJqctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = mbdKineIqcJqcaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            inst = mbdKineIqcJctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = mbdKineIqcJcaxis(frmi, frmj, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            inst = mbdKineIctJqctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = mbdKineIctJqcaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            inst = mbdKineIctJctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = mbdKineIctJcaxis(frmi, frmj, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrame>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            inst = mbdKineIcJqctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = mbdKineIcJqcaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            inst = mbdKineIcJctaxis(frmi, frmj, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = mbdKineIcJcaxis(frmi, frmj, axisK);
        }
    }
    assert(inst);
    return inst;
}

std::shared_ptr<KinematicIJ> ASMTSymbolicFunctionIJKi::mbdKineIJKaxisKWith(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr efrmK, size_t axisK)
{
    std::shared_ptr<KinematicIJ> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            inst = mbdKineIqctJqctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = mbdKineIqctJqcKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            inst = mbdKineIqctJctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = mbdKineIqctJcKaxisK(frmi, frmj, efrmK, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrameq>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            inst = mbdKineIqcJqctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = mbdKineIqcJqcKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            inst = mbdKineIqcJctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = mbdKineIqcJcKaxisK(frmi, frmj, efrmK, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            inst = mbdKineIctJqctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = mbdKineIctJqcKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            inst = mbdKineIctJctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            inst = mbdKineIctJcKaxisK(frmi, frmj, efrmK, axisK);
        }
    }
    else if (std::dynamic_pointer_cast<EndFrame>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            inst = mbdKineIcJqctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            inst = mbdKineIcJqcKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            inst = mbdKineIcJctKaxisK(frmi, frmj, efrmK, axisK);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
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
