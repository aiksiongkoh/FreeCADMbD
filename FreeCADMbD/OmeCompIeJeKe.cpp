#include "OmeCompIeJeKe.h"
#include "OmeCompIeqJeqKeq.h"
#include "OmeCompIeqJeKeq.h"
#include "OmeCompIeJeqKe.h"
#include "EndFrameqt.h"
#include "EndFrameq.h"
#include "EndFramet.h"
#include "EndFrame.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<OmeCompIeJeKe> OmeCompIeJeKe::With()
{
    auto inst = std::make_shared<OmeCompIeJeKe>();
    inst->initialize();
    return inst;
}

std::shared_ptr<OmeCompIeJeKe> OmeCompIeJeKe::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
    const auto factoryName = "OmeCompIeJeKe::With";
    std::shared_ptr<OmeCompIeJeKe> inst;
    if (std::dynamic_pointer_cast<EndFrameqt>(frmi)) {
        throwUnsupportedFrameCombination(factoryName);
    }
    else if (std::dynamic_pointer_cast<EndFrameq>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            if (std::dynamic_pointer_cast<EndFrameq>(frmk)) {
                inst = std::make_shared<OmeCompIeqJeqKeq>(frmi, frmj, frmk, axisk);
            }
            else {
                throwUnsupportedFrameCombination(factoryName);
            }
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            if (std::dynamic_pointer_cast<EndFrameq>(frmk)) {
                inst = std::make_shared<OmeCompIeqJeKeq>(frmi, frmj, frmk, axisk);
            }
            else {
                throwUnsupportedFrameCombination(factoryName);
            }
        }
    }
    else if (std::dynamic_pointer_cast<EndFramet>(frmi)) {
        throwUnsupportedFrameCombination(factoryName);
    }
    else if (std::dynamic_pointer_cast<EndFrame>(frmi)) {
        if (std::dynamic_pointer_cast<EndFrameqt>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrameq>(frmj)) {
            if (std::dynamic_pointer_cast<EndFrameqt>(frmk)) {
                throwUnsupportedFrameCombination(factoryName);
            }
            else if (std::dynamic_pointer_cast<EndFrameq>(frmk)) {
                throwUnsupportedFrameCombination(factoryName);
            }
            else if (std::dynamic_pointer_cast<EndFramet>(frmk)) {
                throwUnsupportedFrameCombination(factoryName);
            }
            else if (std::dynamic_pointer_cast<EndFrame>(frmk)) {
                inst = std::make_shared<OmeCompIeJeqKe>(frmi, frmj, frmk, axisk);
            }
            else {
                throwUnsupportedFrameCombination(factoryName);
            }
        }
        else if (std::dynamic_pointer_cast<EndFramet>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
        else if (std::dynamic_pointer_cast<EndFrame>(frmj)) {
            throwUnsupportedFrameCombination(factoryName);
        }
    }
    assert(inst);
    inst->initialize();
    return inst;
}

double OmeCompIeJeKe::value()
{
    return omeiIeJeKe;
}

void OmeCompIeJeKe::simUpdateAll()
{
    //omeIeJeO = omeOJeO - omeOIeO
    //omeIeJeKe = AKeO * omeIeJeO
    //omeiIeJeKe = ArowiKeO dot omeIeJeO = AcoljOKe dot omeIeJeO
    throw SimulationStoppingError("Should not implemented.");
}
