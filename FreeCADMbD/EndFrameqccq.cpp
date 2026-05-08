#include "EndFrameqccq.h"

using namespace MbD;

std::shared_ptr<EndFrameqccq> EndFrameqccq::With()
{
    auto inst = std::make_shared<EndFrameqccq>();
    inst->initialize();
    return inst;
}

void EndFrameqccq::setTargetFrame(std::shared_ptr<EndFrame> targetFrm)
{
    targetFrame = targetFrm;
}
