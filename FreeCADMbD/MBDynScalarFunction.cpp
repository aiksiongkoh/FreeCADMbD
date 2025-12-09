#include <regex>

#include "MBDynScalarFunction.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<MBDynScalarFunction> MBDynScalarFunction::With()
{
    auto inst = std::make_shared<MBDynScalarFunction>();
    inst->initialize();
    return inst;
}

void MBDynScalarFunction::parseMBDyn(std::string line)
{
    scalarFunctionString = line;
    arguments = collectArgumentsFor("scalar function", line);
    scalarFunctionName = readStringNoSpacesOffTop(arguments);
    scalarFunctionName = std::regex_replace(scalarFunctionName, std::regex("\""), "");
    readFunction(arguments);
}

void MBDynScalarFunction::readFunction(std::vector<std::string>& args)
{
    if (args.empty()) return;
    std::string str = readStringNoSpacesOffTop(args);
    if (str == "cubicspline") {
        if (args[0].find("do not extrapolate") != std::string::npos) {
            args.erase(args.begin());
        }
        auto ss = std::stringstream();
        ss << "spline(time, 3";
        while (!args.empty())
        {
            ss << ", " << readDoubleOffTop(args);
        }
        ss << ")";
        formula = ss.str();
        return;
    }
    throw SimulationStoppingError("To be implemented.");
}

void MBDynScalarFunction::createASMT()
{
    throw SimulationStoppingError("To be implemented.");
}
