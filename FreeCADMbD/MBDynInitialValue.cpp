#include "MBDynInitialValue.h"
#include "ASMTSimulationParameters.h"
#include "ASMTAssembly.h"
#include "MBDynSystem.h"
#include "MBDynControlData.h"
#include "MBDynOutputMeter.h"

using namespace MbD;

std::shared_ptr<MBDynInitialValue> MBDynInitialValue::With()
{
    auto inst = std::make_shared<MBDynInitialValue>();
    inst->initialize();
    return inst;
}

void MBDynInitialValue::initialize()
{
    //Do nothing.
}

void MBDynInitialValue::parseMBDyn(std::vector<std::string>& lines)
{
    readInitialTime(lines);
    readFinalTime(lines);
    readTimeStep(lines);
    readMaxIterations(lines);
    readTolerance(lines);
    readDerivativesTolerance(lines);
    readDerivativesMaxIterations(lines);
    readDerivativesCoefficient(lines);
    assert(lines.size() == 2);
}

void MBDynInitialValue::readInitialTime(std::vector<std::string>& lines)
{
    //initial time:   0.;
    std::vector<std::string> tokens{ "initial", "time:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> initialTime;
    lines.erase(it);
}

void MBDynInitialValue::readFinalTime(std::vector<std::string>& lines)
{
    //final time:     5.;
    std::vector<std::string> tokens{ "final", "time:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> finalTime;
    lines.erase(it);
}

void MBDynInitialValue::readTimeStep(std::vector<std::string>& lines)
{
    //time step:      1.e-2;
    std::vector<std::string> tokens{ "time", "step:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> timeStep;
    lines.erase(it);
}

void MBDynInitialValue::readMaxIterations(std::vector<std::string>& lines)
{
    //max iterations: 10;
    std::vector<std::string> tokens{ "max", "iterations:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> maxIterations;
    lines.erase(it);
}

void MBDynInitialValue::readTolerance(std::vector<std::string>& lines)
{
    //tolerance:      1.e-6;
    std::vector<std::string> tokens{ "tolerance:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> tolerance;
    lines.erase(it);
}

void MBDynInitialValue::readDerivativesTolerance(std::vector<std::string>& lines)
{
    //derivatives tolerance: 0.0001;
    std::vector<std::string> tokens{ "derivatives", "tolerance:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> derivativesTolerance;
    lines.erase(it);
}

void MBDynInitialValue::readDerivativesMaxIterations(std::vector<std::string>& lines)
{
    //derivatives max iterations: 100;
    std::vector<std::string> tokens{ "derivatives", "max", "iterations:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> str;
    iss >> derivativesMaxIterations;
    lines.erase(it);
}

void MBDynInitialValue::readDerivativesCoefficient(std::vector<std::string>& lines)
{
    //derivatives coefficient: auto;
    std::vector<std::string> tokens{ "derivatives", "coefficient:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> derivativesCoefficient;
    lines.erase(it);
}

void MBDynInitialValue::createASMT()
{
    auto simulationParameters = ASMTSimulationParameters::With();
    asmtItem = simulationParameters;
    simulationParameters->settstart(initialTime);
    simulationParameters->settend(finalTime);    //tstart == tend Initial Conditions only.
    simulationParameters->sethmin(1.0e-9);
    simulationParameters->sethmax(1.0);
    auto outputMeter = root()->controlData->outputMeter;
    if (outputMeter) {
        size_t nstep = stoi(outputMeter->asmtFormula(outputMeter->formula));
        timeStep *= nstep;
    }
    simulationParameters->sethout(timeStep);
    simulationParameters->seterrorTol(std::min(1.0e-8, tolerance));    //FreeCADMbD needs a tighter tolerance
    simulationParameters->setmaxIter(maxIterations);
    asmtAssembly()->setSimulationParameters(simulationParameters);
}
