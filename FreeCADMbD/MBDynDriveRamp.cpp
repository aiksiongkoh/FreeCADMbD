#include "MBDynDriveRamp.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynDriveRamp> MBDynDriveRamp::With()
{
    auto inst = std::make_shared<MBDynDriveRamp>();
    inst->initialize();
    return inst;
}

void MBDynDriveRamp::readFunction(std::vector<std::string>& args)
{
    assert(readStringNoSpacesOffTop(args) == "ramp");
    std::string slope, initValue, initTime, finalTime;
    slope = popOffTop(args);
    initTime = popOffTop(args);
    finalTime = popOffTop(args);
    initValue = popOffTop(args);
    slope.erase(remove_if(slope.begin(), slope.end(), isspace), slope.end());
    initTime.erase(remove_if(initTime.begin(), initTime.end(), isspace), initTime.end());
    finalTime.erase(remove_if(finalTime.begin(), finalTime.end(), isspace), finalTime.end());
    initValue.erase(remove_if(initValue.begin(), initValue.end(), isspace), initValue.end());

    //f = slope*(time - t0) + f0
    //rampstep(time, t0, f0, t1, f1)
    //t0 = initTime
    //f0 = initValue
    //t1 = finalTime
    //f1 = initValue + slope * (finalTime - initTime)
    auto ss = std::stringstream();
    ss << "rampstep(time, " << initTime << ", " << initValue << ", " << finalTime << ", "
        << initValue << " + " << slope << "*(" << finalTime << " - " << initTime << "))";
    formula = ss.str();
}

void MBDynDriveRamp::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}

