#include "MBDynBlock.h"

using namespace MbD;

std::shared_ptr<MBDynBlock> MBDynBlock::With()
{
    auto inst = std::make_shared<MBDynBlock>();
    inst->initialize();
    return inst;
}
