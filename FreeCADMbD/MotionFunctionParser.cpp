#include "MotionFunctionParser.h"

using namespace MbD;

std::shared_ptr<MotionFunctionParser> MotionFunctionParser::With()
{
    auto inst = std::make_shared<MotionFunctionParser>();
    inst->initialize();
    return inst;
}
