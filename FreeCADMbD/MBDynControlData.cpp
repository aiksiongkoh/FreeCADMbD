#include "MBDynControlData.h"
#include "MBDynOutputMeter.h"

using namespace MbD;

std::shared_ptr<MBDynControlData> MBDynControlData::With()
{
    auto inst = std::make_shared<MBDynControlData>();
    inst->initialize();
    return inst;
}

void MBDynControlData::initialize()
{
    //Do nothing.
}

void MBDynControlData::parseMBDyn(std::vector<std::string>& lines)
{
    readMaxIterations(lines);
    readDefaultOrientation(lines);
    readOmegaRotates(lines);
    readPrint(lines);
    readInitialStiffness(lines);
    readOutputMeter(lines);
    readStructuralNodes(lines);
    readRigidBodies(lines);
    readAbstractNodes(lines);
    readJoints(lines);
    readForces(lines);
    readGravity(lines);
    readGenels(lines);
    assert(lines.size() == 2);
}

void MBDynControlData::readMaxIterations(std::vector<std::string>& lines)
{
    //max iterations: 1000;
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

void MBDynControlData::readDefaultOrientation(std::vector<std::string>& lines)
{
    //default orientation: euler321;
    std::vector<std::string> tokens{ "default", "orientation:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> defaultOrientation;
    lines.erase(it);
}

void MBDynControlData::readOmegaRotates(std::vector<std::string>& lines)
{
    //omega rotates: no;
    std::vector<std::string> tokens{ "omega", "rotates:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> omegaRotates;
    lines.erase(it);
}

void MBDynControlData::readPrint(std::vector<std::string>& lines)
{
    //print: none;
    std::vector<std::string> tokens{ "print:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> print;
    lines.erase(it);
}

void MBDynControlData::readInitialStiffness(std::vector<std::string>& lines)
{
    //initial stiffness: 1.0, 1.0;
    std::vector<std::string> tokens{ "initial", "stiffness:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> initialStiffness;
    iss >> str;
    initialStiffness.append(str);
    lines.erase(it);
}

void MBDynControlData::readOutputMeter(std::vector<std::string>& lines)
{
    std::vector<std::string> tokens{ "output", "meter:" };
    auto it = findLineWith(lines, tokens);
    if (it != lines.end()) {
        outputMeter = MBDynOutputMeter::With();
        outputMeter->owner = this;
        outputMeter->parseMBDyn(*it);
        lines.erase(it);
    }
}

void MBDynControlData::readStructuralNodes(std::vector<std::string>& lines)
{
    //structural nodes: 4;
    std::vector<std::string> tokens{ "structural", "nodes:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> structuralNodes;
    lines.erase(it);
}

void MBDynControlData::readRigidBodies(std::vector<std::string>& lines)
{
    //rigid bodies:     3;
    std::vector<std::string> tokens{ "rigid", "bodies:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> rigidBodies;
    lines.erase(it);
}

void MBDynControlData::readAbstractNodes(std::vector<std::string>& lines)
{
    //abstract nodes:     3;
    std::vector<std::string> tokens{ "abstract", "nodes:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> str;
    iss >> abstractnodes;
    lines.erase(it);
}

void MBDynControlData::readJoints(std::vector<std::string>& lines)
{
    //joints:           6;
    std::vector<std::string> tokens{ "joints:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> joints;
    lines.erase(it);
}

void MBDynControlData::readForces(std::vector<std::string>& lines)
{
    //forces:           6;
    std::vector<std::string> tokens{ "forces:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> forces;
    lines.erase(it);
}

void MBDynControlData::readGravity(std::vector<std::string>& lines)
{
    //gravity;
    std::vector<std::string> tokens{ "gravity" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    lines.erase(it);
}

void MBDynControlData::readGenels(std::vector<std::string>& lines)
{
    //genels:           6;
    std::vector<std::string> tokens{ "genels:" };
    auto it = findLineWith(lines, tokens);
    if (it == lines.end()) return;
    std::istringstream iss(*it);
    std::string str;
    iss >> str;
    iss >> genels;
    lines.erase(it);
}
