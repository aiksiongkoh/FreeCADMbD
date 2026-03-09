/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

/*********************************************************************
 * @file  MbDCode.cpp
 *
 * @brief Program to assemble a piston crank system.
 *********************************************************************/

#include "../FreeCADMbD/ASMTAssembly.h"
#include "../FreeCADMbD/MBDynSystem.h"

using namespace MbD;
namespace
{
bool hasExtension(const std::string& filePath, const std::string& extension)
{
    return filePath.find(extension) != std::string::npos;
}
void runDefaultLocalScenario()
{
    ASMTAssembly::readWriteReadDynFile(std::string(TEST_DATA_PATH) + "/ASMT/pistonAllowZRotation.asmt");
}
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        runDefaultLocalScenario();
        return 0;
    }

    const std::string inputFile = argv[1];
    if (argc > 2 && hasExtension(inputFile, ".asmt"))
    {
        const std::string outputFile = argv[2];
        ASMTAssembly::readWriteDynFile2(inputFile, outputFile);
        return 0;
    }

    if (hasExtension(inputFile, ".asmt"))
    {
        ASMTAssembly::readWriteDynFile(inputFile);
    }
    else if (hasExtension(inputFile, ".mbd"))
    {
        MBDynSystem::runDynFile(inputFile);
    }
    return 0;
}
